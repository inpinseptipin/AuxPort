#ifndef AUXPORT_AUDIO_SPECTRAL_H
#define AUXPORT_AUDIO_SPECTRAL_H
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2023, Satyarth Arora
			All rights reserved.

			Redistribution and use in source and binary forms, with or without
			modification, are permitted provided that the following conditions are met:

			1. Redistributions of source code must retain the above copyright notice, this
			   list of conditions and the following disclaimer.

			2. Redistributions in binary form must reproduce the above copyright notice,
			   this list of conditions and the following disclaimer in the documentation
			   and/or other materials provided with the distribution.

			3. Neither the name of the copyright holder nor the names of its
			   contributors may be used to endorse or promote products derived from
			   this software without specific prior written permission.

			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
			AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
			FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
			DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*===================================================================================*/
#include "../FFT/AuxFFT.h"
#include "../../Core/Utility/AuxUtility.h"
#include "../Windows/AuxWindow.h"

namespace AuxPort
{
namespace Audio
{
namespace Spectral
{
	template <class sampleType>
	class OverlapSaveProcessor
	{
	public:
		OverlapSaveProcessor(size_t overlapSize)
		{
			_prevInputs.resize(overlapSize);
		}

		void getOverlappedBuffer(const std::vector<sampleType>& inputBuffer, std::vector<sampleType>& overlappedBuffer)
		{
			AuxAssert(inputBuffer.size() >= _prevInputs.size(), "Input size is less than save size!");
			AuxAssert(overlappedBuffer.size() == inputBuffer.size() + _prevInputs.size(), "Size of overlappedBuffer should be equal to (inputBuffer's Size + overlapSize)!");

			// Filling Overlapped Buffer
			size_t writeIndex = 0;
			for (const sampleType& val : _prevInputs)
				overlappedBuffer[writeIndex++] = val;
			for (const sampleType& val : inputBuffer)
				overlappedBuffer[writeIndex++] = val;

			// Saving the current inputs into _prevInputs
			for (int i = _prevInputs.size() - 1, j = inputBuffer.size() - 1; i > -1; i--, j--)
			{
				_prevInputs[i] = inputBuffer[j];
			}
		}

	protected:
		std::vector<sampleType> _prevInputs;
	};

	template <class sampleType> 
	class Spectrogram : public OverlapSaveProcessor<sampleType>
	{
	public:
		Spectrogram(const size_t bufferSize, size_t windowSize = 0, size_t overlapSize = 0, const AuxPort::Audio::Window::Type windowType = AuxPort::Audio::Window::HannWin) 
			: OverlapSaveProcessor<sampleType>( (validateWindowAndOverlapSizes(bufferSize, windowSize, overlapSize), overlapSize) )
			, _fft(windowSize)
		{
			AuxAssert(bufferSize + overlapSize == windowSize, "(Overlap Size + Buffer Size) should be equal to window size!");
			
			_window = AuxPort::Audio::Window::generate<sampleType>(windowSize, windowType);
			_currOverlappedBuffer.resize(windowSize);
			_overlapSize = overlapSize;
			_bufferSize = bufferSize;
		}

		std::vector<std::complex<float>> processBuffer(const std::vector<sampleType>& inputBuffer)
		{
			AuxAssert(inputBuffer.size() == _bufferSize, "Input Buffer should have specified Size!");
			getOverlappedBuffer(inputBuffer, _currOverlappedBuffer);

			//Applying window
			AuxPort::Utility::multiply(_currOverlappedBuffer, _window);

			// Computing FFT
			std::vector<sampleType> temp(_currOverlappedBuffer.size());
			_fft.computeTransform(_currOverlappedBuffer, temp);
			return *_fft.getFourierTransformFrame();
		}

		std::vector<std::vector<std::complex<float>>> process(const std::vector<sampleType>& audioSamples)
		{
			uint32 bufferCount = ceil((float)audioSamples.size() / _bufferSize);
			std::vector<std::vector<std::complex<float>>> stftResults;
			stftResults.reserve(bufferCount);

			std::vector<sampleType> currBuffer(_bufferSize);
			for (int i = 0; i < bufferCount - 1; i++)
			{
				// Extracting Current Buffer
				for (int j = 0; j < _bufferSize; j++)
				{
					currBuffer[j] = audioSamples[i * _bufferSize + j];
				}

				// Processing Buffer and storing STFT Complex Values
				stftResults.push_back(processBuffer(currBuffer));
			}

			// Extracting and padding last buffer with zeroes (if required)
			{
				int j = 0;
				size_t currReadIndex = (bufferCount - 1) * _bufferSize;
				while (currReadIndex < audioSamples.size())
				{
					currBuffer[j] = audioSamples[currReadIndex];
					currReadIndex++;
					j++;
				}

				// Padding with zeroes (if required)
				while (j < _bufferSize)
				{
					currBuffer[j] = 0;
					j++;
				}

				// Processing Buffer and storing STFT Complex Values
				stftResults.push_back(processBuffer(currBuffer));
			}
			
			return stftResults;
		}

	private:
		static void validateWindowAndOverlapSizes(const size_t bufferSize, size_t& windowSize, size_t& overlapSize)
		{
			if (windowSize == 0)
				windowSize = AuxPort::Utility::nextPowerOfTwo(bufferSize);

			if (overlapSize == 0)
				overlapSize = windowSize - bufferSize;
		}

		size_t _bufferSize;
		size_t _overlapSize;
		AuxPort::Audio::FourierTransform _fft;
		std::vector<sampleType> _window;
		std::vector<sampleType> _currOverlappedBuffer;
	};
}
}
}

#endif