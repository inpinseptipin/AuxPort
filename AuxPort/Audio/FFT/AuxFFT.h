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
			FourierTransform(const size_t& fftSize)
			{
				uint32 isPowerOfTwo = (uint32)(fftSize & (fftSize - 1));
				if (isPowerOfTwo == 0)
				{
					_fftValues.resize(fftSize);
					_log2N = uint32(log2(fftSize));
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs FFT on the AudioBuffer passed in the argument and returns an AudioBuffer with FFT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			template<class sample>
			void computeTransform(const AuxPort::Audio::Buffer<sample>& buffer, AuxPort::Audio::Buffer<sample>& output)
			{
				if (buffer.size() == _fftValues.size())
				{
					for (uint32 i = 0; i < buffer.size(); i++)
					{
						_fftValues[i] = buffer.get(i);
					}
				}
				compute();
				if (output.size() != buffer.size())
					output.resize(buffer.size());
				std::complex<sample> temp;
				for (uint32 i = 0; i < buffer.size(); i++)
				{
					temp = _fftValues[i];
					output.set(temp.real(), i);
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs FFT on the AudioBuffer passed in the argument and returns an AudioBuffer with FFT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			template<class sample>
			void computeTransform(const AuxPort::Audio::Buffer<sample>& buffer)
			{
				if (buffer.size() == _fftValues.size())
				{
					for (uint32 i = 0; i < buffer.size(); i++)
					{
						_fftValues[i] = buffer.get(i);
					}
				}
				compute<float>();
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs in place IFFT
			///////////////////////////////////////////////////////////////////////////////////////
			template<class sample>
			void computeInverseTransform(AuxPort::Audio::Buffer<sample>& output)
			{
				for (size_t i = 0; i < _fftValues.size(); i++)
				{
					_fftValues[i] = std::conj(_fftValues[i]);
				}
				compute();
				for (size_t i = 0; i < _fftValues.size(); i++)
				{
					_fftValues[i] = std::conj(_fftValues[i]);
				}
				std::complex<sample> norm((sample)_fftValues.size(), 0);
				for (size_t i = 0; i < _fftValues.size(); i++)
				{
					_fftValues[i] /= norm;
				}
				std::complex<sample> temp;
				for (uint32 i = 0; i < _fftValues.size(); i++)
				{
					temp = _fftValues[i];
					output.set(temp.real(), i);
				}
			}


			template<class sample>
			std::complex<sample> get(const size_t& index) const
			{
				return _fftValues[index];
			}

			size_t size() const
			{
				return _fftValues.size();
			}
		private:

			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Performs in-place FFT
			///////////////////////////////////////////////////////////////////////////////////////
			template<class sample>
			void compute()
			{
				std::complex<sample> temp;
				uint32 N = (uint32)_fftValues.size();
				uint32 K = N;
				uint32 n;
				sample theta = static_cast<sample>(pi / N);
				std::complex<sample> phi = std::complex(cos(theta), -sin(theta));
				std::complex<sample> T = 1.0L;

				while (K > 0)
				{
					n = K;
					K >>= 1;
					phi = phi * phi;
					T = 1.0L;
					for (uint32 i = 0; i < K; i++)
					{
						for (uint32 j = i; j < N; j += n)
						{
							uint32 b = j + K;
							temp = _fftValues[j] - _fftValues[b];
							_fftValues[j] += _fftValues[b];
							_fftValues[b] = temp * T;
						}
						T *= phi;
					}
				}
				int noOfBits = (int)log2(N);
				for (uint32 i = 0; i < N; i++)
				{
					uint32 j = reverseBits(i);
					if (j > i)
					{
						temp = _fftValues[i];
						_fftValues[i] = _fftValues[j];
						_fftValues[j] = temp;
					}

				}
			}


			uint32 reverseBits(uint32 b)
			{
				b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
				b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
				b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
				b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
				b = ((b >> 16) | (b << 16)) >> (32 - _log2N);
				return b;
			}

			std::vector<std::complex<float>> _fftValues;

			uint32 _log2N;
		};
	}
}
#endif