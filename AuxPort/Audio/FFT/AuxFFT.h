#pragma once
#ifndef AUXPORT_AUDIO_FFT_H
#define AUXPORT_AUDIO_FFT_H
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
#include "../Buffer/AuxBuffer.h"
#include <complex>
#include <valarray>

namespace AuxPort
{
	namespace Audio
	{


		///////////////////////////////////////////////////////////////////////////////////////
		///	[Class] Implementation of Fast Fourier Transform based on optimized Cooley-Tukey Algorithm
		///////////////////////////////////////////////////////////////////////////////////////
		class FourierTransform
		{
		public:
			~FourierTransform() = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Constructor] Provide FFT Size, (Note should be a power of 2).
			///////////////////////////////////////////////////////////////////////////////////////
			FourierTransform(size_t fftSize);
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs FFT on the AudioBuffer passed in the argument and returns an AudioBuffer with FFT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			void computeTransform(const std::vector<float>& inputBuffer, std::vector<float>& output);
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs in place IFFT
			///////////////////////////////////////////////////////////////////////////////////////
			void computeInverseTransform(std::vector<float>& outputBuffer);
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs in-place FFT
			///////////////////////////////////////////////////////////////////////////////////////
			std::complex<float> get(size_t index) const;
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Returns the pointer to the Fourier Transform Vector
			///////////////////////////////////////////////////////////////////////////////////////
			std::vector<std::complex<float>>* getFourierTransformFrame();
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Returns the size
			///////////////////////////////////////////////////////////////////////////////////////
			size_t size() const;
		private:

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs in-place FFT
			///////////////////////////////////////////////////////////////////////////////////////
			void compute();
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Reverse Bits
			///////////////////////////////////////////////////////////////////////////////////////
			uint32 reverseBits(uint32 b);

			std::vector<std::complex<float>> _fftValues;
			uint32 _log2N = 0;
		};


	}
}
#endif