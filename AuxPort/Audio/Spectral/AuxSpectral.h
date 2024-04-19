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
	class OverlapSaveDriver
	{
	public:
		OverlapSaveDriver(size_t saveSize)
		{
			reset(saveSize);
		}

		void reset(size_t saveSize)
		{
			_prevInputs.resize(saveSize);
		}

		void processOverlap(const std::vector<sampleType>& inputBuffer)
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

			// Processing the overlapped Buffer
			processorAlgorithm(overlappedBuffer);
		}

		virtual void processorAlgorithm(std::vector<sampleType>& overlappedBuffer) = 0;
	private:
		std::vector<sampleType> _prevInputs;
	};

	template <class sampleType>
	class Spectrogram : protected OverlapSaveDriver<sampleType>
	{
	public:
		Spectrogram(size_t windowSize, size_t saveSize) : fft(windowSize), OverlapSaveDriver<sampleType>(saveSize), fftOutput(windowSize)
		{
			window = AuxPort::Audio::Window::generate<sampleType>(windowSize, AuxPort::Audio::Window::HammWin);
		}

		void processorAlgorithm(std::vector<sampleType>& overlappedBuffer) override
		{
			AuxAssert(window.size() == overlappedBuffer.size(), "Incoming overlapped buffer's size should be equal to window size. Please adjust either accordingly!");

			//Applying window
			AuxPort::Utility::multiply(overlappedBuffer, window);

			// Computing FFT
			std::vector<float> temp(window.size());
			fft.computeTransform(overlappedBuffer, temp);
			
			// Use FFT output
		}

	private:
		AuxPort::Audio::FourierTransform fft;
		std::vector<sampleType> window;
		// Complex Values stored in this
		std::vector<std::complex<float>> fftOutput;
	};
}
}
}

#endif