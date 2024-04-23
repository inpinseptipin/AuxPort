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
			reset(overlapSize);
		}

		void reset(size_t overlapSize)
		{
			_prevInputs.resize(overlapSize);
		}

		std::vector<sampleType> getOverlappedBuffer(const std::vector<sampleType>& inputBuffer)
		{
			AuxAssert(inputBuffer.size() >= _prevInputs.size(), "Input size is less than save size. Please adjust save size!");

			// Creating Overlapped Buffer
			std::vector<sampleType> overlappedBuffer;
			overlappedBuffer.reserve(_prevInputs.size() + inputBuffer.size());
			overlappedBuffer.insert(overlappedBuffer.end(), _prevInputs.begin(), _prevInputs.end());
			overlappedBuffer.insert(overlappedBuffer.end(), inputBuffer.begin(), inputBuffer.end());

			// Saving the current inputs into _prevInputs
			for (int i = _prevInputs.size() - 1, j = inputBuffer.size() - 1; i > -1; i--, j--)
			{
				_prevInputs[i] = inputBuffer[j];
			}

			return overlappedBuffer;
		}

	private:
		std::vector<sampleType> _prevInputs;
	};

	template <class sampleType>
	class Spectrogram : protected OverlapSaveProcessor<sampleType>
	{
	public:
		Spectrogram(size_t windowSize, AuxPort::Audio::Window::Type windowType, size_t overlapSize, size_t bufferSize) : _fft(windowSize), OverlapSaveProcessor<sampleType>(overlapSize)
		{
			AuxAssert(bufferSize + overlapSize == windowSize, "(Overlap Size + Buffer Size) should be equal to window size!");
			_window = AuxPort::Audio::Window::generate<sampleType>(windowSize, windowType);
			_overlapSize = overlapSize;
			_bufferSize = bufferSize;
		}

		std::vector<std::complex<float>> processBuffer(const std::vector<sampleType>& inputBuffer)
		{
			AuxAssert(inputBuffer.size() == _bufferSize, "Input Buffer should have specified Size!");
			std::vector<sampleType> overlappedBuffer = getOverlappedBuffer(inputBuffer);

			//Applying window
			AuxPort::Utility::multiply(overlappedBuffer, _window);

			// Computing FFT
			std::vector<sampleType> temp(overlappedBuffer.size());
			_fft.computeTransform(overlappedBuffer, temp);
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
		AuxPort::Audio::FourierTransform _fft;
		std::vector<sampleType> _window;
		size_t _overlapSize;
		size_t _bufferSize;
	};
}
}
}

#endif