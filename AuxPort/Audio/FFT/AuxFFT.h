#pragma once
#ifndef AUXPORT_AUDIO_FFT_H
#define AUXPORT_AUDIO_FFT_H
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2025, Satyarth Arora
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
#include "../../Core/Env/AuxEnv.h"
#include "../Windows/AuxWindow.h"
#include <vector>
#include <complex>
#include <valarray>
#include "../../Core/Utility/AuxCircularBuffer.h"
#include <memory>

namespace AuxPort
{
	namespace Audio
	{
		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Implementation of Fast Fourier Transform based on optimized Cooley-Tukey Algorithm
		///////////////////////////////////////////////////////////////////////////////////////
		class FourierTransform
		{
		public:
			~FourierTransform() = default;
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Provide FFT Size, (Note should be a power of 2).
			///////////////////////////////////////////////////////////////////////////////////////
			FourierTransform(size_t fftSize);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs FFT on the AudioBuffer passed in the argument and returns a complex vector with raw FFT values
			///////////////////////////////////////////////////////////////////////////////////////
			void computeTransform(const std::vector<float>& inputBuffer, std::vector<std::complex<float>>& complexVector);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs FFT on the AudioBuffer passed in the argument and returns an AudioBuffer with FFT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			void computeMagnitudeTransform(const std::vector<float>& inputBuffer, std::vector<float>& outputBuffer,bool normalized = true);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs FFT on the AudioBuffer passed in the argument and returns an AudioBuffer with FFT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			void computeMagnitudeTransform(const float* inputBuffer, float* outputBuffer, uint32_t numberOfSamples, bool normalized = true);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs an inverse fourier transform and stores the real audio signal into the output buffer
			///////////////////////////////////////////////////////////////////////////////////////
			void computeInverseTransform(std::vector<float>& outputBuffer);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs an inverse fourier transform and stores the real audio signal into the output buffer
			///////////////////////////////////////////////////////////////////////////////////////
			void computeInverseTransform(float* outputBuffer, uint32_t numberOfSamples);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs in-place FFT
			///////////////////////////////////////////////////////////////////////////////////////
			std::complex<float> get(size_t index) const;
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the pointer to the Fourier Transform Vector
			///////////////////////////////////////////////////////////////////////////////////////
			std::vector<std::complex<float>>* getFourierTransformFrame();
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the size
			///////////////////////////////////////////////////////////////////////////////////////
			size_t size() const;
		private:
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs in-place FFT
			///////////////////////////////////////////////////////////////////////////////////////
			void compute();

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Reverse Bits
			///////////////////////////////////////////////////////////////////////////////////////
			uint32_t reverseBits(uint32_t b);

			std::vector<std::complex<float>> _fftValues;
			uint32_t _log2N = 0;
		};


		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Implementation of naive Discrete Fourier Transform
		///////////////////////////////////////////////////////////////////////////////////////
		class DiscreteFourierTransform
		{
		public:
			~DiscreteFourierTransform() = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Provide DFT Size
			///////////////////////////////////////////////////////////////////////////////////////
			DiscreteFourierTransform(size_t dftSize);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs DFT on the AudioBuffer passed in the argument and returns an AudioBuffer with DFT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			void computeTransform(const std::vector<float>& inputBuffer, std::vector<float>& outputBuffer);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs Inverse DFT
			///////////////////////////////////////////////////////////////////////////////////////
			void computeInverseTransform(std::vector<float>& outputBuffer);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the complex DFT value at a given index
			///////////////////////////////////////////////////////////////////////////////////////
			std::complex<float> get(size_t index) const;
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the pointer to the Fourier Transform Vector
			///////////////////////////////////////////////////////////////////////////////////////
			std::vector<std::complex<float>>* getDFTFrame();
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the size
			///////////////////////////////////////////////////////////////////////////////////////
			size_t size() const;
		private:

			std::vector<std::complex<float>> _dftValues;
		};


		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Implementation of naive Discrete Cosine Transform
		///////////////////////////////////////////////////////////////////////////////////////
		class DiscreteCosineTransform
		{
		public:
			~DiscreteCosineTransform() = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Provide DCT Size
			///////////////////////////////////////////////////////////////////////////////////////
			DiscreteCosineTransform(size_t dctSize);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs DCT on the AudioBuffer passed in the argument and returns an AudioBuffer with DCT Values.
			///////////////////////////////////////////////////////////////////////////////////////
			void computeTransform(const std::vector<float>& inputBuffer, std::vector<float>& outputBuffer);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs Inverse DCT
			///////////////////////////////////////////////////////////////////////////////////////
			void computeInverseTransform(std::vector<float>& outputBuffer);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the complex DCT value at a given index
			///////////////////////////////////////////////////////////////////////////////////////
			float get(size_t index) const;
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the pointer to the Cosine Transform Vector
			///////////////////////////////////////////////////////////////////////////////////////
			std::vector<float>* getDCTFrame();
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the size
			///////////////////////////////////////////////////////////////////////////////////////
			size_t size() const;
		private:

			std::vector<float> _dctValues;
		};

		class STFT
		{
		public:
			enum StateMachine
			{
				initial, full, end
			};
			/**
			  @brief Initializes the STFT engine (Only supports 50% overlap)
			  @param fftSize
			  @param overlapPercentage
			  @param window
			  \code{.cpp}
			  
			  \endcode 
			 */
			STFT(uint32_t fftSize, uint32_t overlapPercentage,AuxPort::Audio::Window::Type window = AuxPort::Audio::Window::HannWin);
			~STFT();
			/**
			  @brief Computes the magnitude transform and returns a real valued 1-D vector of fftSize
			  @param inputBuffer
			  @param outputBuffer
			  @param numberOfSamples
			  @param stateMachine
			  \code{.cpp}
			  
			  \endcode 
			 */
			void computeMagnitudeTransform(const float* inputBuffer, float* outputBuffer, uint32_t numberOfSamples, AuxPort::Audio::STFT::StateMachine stateMachine = AuxPort::Audio::STFT::StateMachine::full);
		protected:
			std::unique_ptr<AuxPort::Audio::FourierTransform> fourierTransform;
			uint32_t fftSize;
			uint32_t overlapPercentage;
			std::vector<float> initialHalfWindow;
			std::vector<float> lastHalfWindow;
			std::vector<float> fullWindow;
			float* inputBufferData;
			float* fftBuffer;
			AuxPort::CircularBufferEngine<float> circEngine;
			StateMachine states;
		};


	}
}
#endif