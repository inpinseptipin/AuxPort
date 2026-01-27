#ifndef AUXPORT_AUDIO_EFFECTS_DISTORTION_H
#define AUXPORT_AUDIO_EFFECTS_DISTORTION_H
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2026, Satyarth Arora
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
#include "../../Buffer/AuxBuffer.h"
#include "../../../Core/Utility/AuxUtility.h"
#include "../../../Core/Utility/AuxCircularBuffer.h"
#include "../../../Core/Utility/AuxSeries.h"
namespace AuxPort
{
	namespace Audio
	{
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Consists of Static Functions with various Distortion Algorithms
		///////////////////////////////////////////////////////////////////////////////////////
		class Distortion
		{
		public:
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function adds a DC offset to your Audio
			///////////////////////////////////////////////////////////////////////////////////////
			static void DC(AuxPort::Audio::Buffer<float>& buffer, const float& offset);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function adds a DC offset to your Audio
			///////////////////////////////////////////////////////////////////////////////////////
			static float DC(float& audio, const float& offset, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs Zero Crossing on the AuxPort::Audio::Buffer
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = {
			///			0 , abs(x) < threshold
			///			x , else
			///		}
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static void zeroCrossing(AuxPort::Audio::Buffer<float>& buffer, const float& threshold);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs Zero Crossing on the given sample
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = {
			///			0 , abs(x) < threshold
			///			x , else
			///		}
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float zeroCrossing(float& audio, const float& threshold, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs ArcTan Distortion on the AuxPort::Audio::Buffer
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = atan(drive*x)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static void arcTan(AuxPort::Audio::Buffer<float>& buffer, const float& drive);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs ArcTan Distortion on the given sample
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = atan(drive*x)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float arcTan(float& audio, const float& drive, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs ArcTan2 Distortion on the AuxPort::Audio::Buffer
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = (2/pi) * atan(drive*x)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static void arcTan2(AuxPort::Audio::Buffer<float>& buffer, const float& drive);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs ArcTan2 Distortion on the  given sample
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = (2/pi) * atan(drive*x)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float arcTan2(float& audio, const float& drive, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs Tanh Distortion on the AuxPort::Audio::Buffer
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = tanh(drive*x)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static void hyperbolicTan(AuxPort::Audio::Buffer<float>& buffer, const float& drive);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs Tanh Distortion on the given sample
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = tanh(drive*x)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float hyperbolicTan(float& audio, const float& drive, const bool& preserve);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function performs Overdrive using Schetzen Soft Clipping Formula
			/// ~~~~
			/// [Mathematical Formula]
			/// Let x be the input sample
			/// Let y be the output sample
			/// y = {
			/// 		2x,	0 <= x < 0.34
			/// 		(3 - (2-3x)^2)/3 , 0.34 < x <= 0.66
			/// 		1,	0.66 <= x <= 1
			/// 	}
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float schetzenOverdrive(float& audio, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			///	@brief This functions Distorts the audio signal using an exponential function
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = sgn(x) (1 - exp(-abs(x))
			/// ~~~~
			///	*Great for Generating Odd Harmonics*
			///////////////////////////////////////////////////////////////////////////////////////
			static float exponential(float& audio, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			///	@brief This functions performs soft clipping distortion on the audio signal
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x be the input sample
			///	Let y be the output sample
			///	y = x - 0.34x^3
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float softClipper(float& audio, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			///	@brief This functions distorts the audio signal by altering the bit depth of the signal
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x = input sample
			///	Let y = output sample
			///	quantizationLevel = (2^depth) - 1
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float crush(float& audio, const float& depth, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			///	@brief This functions distorts the audio signal by shaping the signal as a sinusoidal wave
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x = input sample
			///	Let y = output sample
			///	y = sin(x);
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float sinusoidalFold(float& audio, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			///	@brief This functions distorts the audio signal by shaping the signal as a square wave
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x = input sample
			///	Let y = output sample
			///	y = {
			///			x > 0 , 1
			///			else , -1
			///	}	
			/// ~~~~	
			///////////////////////////////////////////////////////////////////////////////////////
			static float squareFold(float& audio, const bool& preserve = true);

			///////////////////////////////////////////////////////////////////////////////////////
			///	@brief This functions distorts the audio signal by passing the signal through a polynomial approximation of a tanh function
			/// ~~~~
			///	[Mathematical Formula]
			///	Let x = input sample
			///	Let y = output sample
			///	Let z be the intermediate term
			///	z = x + (0.16489087x^3) + (0.00985468fx^5)
			///		y = z / sqrt(1 + z^2)
			/// ~~~~
			///////////////////////////////////////////////////////////////////////////////////////
			static float levianTanh(float& audio, const bool& preserve = true);


			

		};

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Assymetric Saturator
		///	
		/// Tanh (Positive Phase) and Atan(Negative Phase)
		///////////////////////////////////////////////////////////////////////////////////////
		class Assymetric
		{
		public:
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Type of Assymetric Saturator
			///////////////////////////////////////////////////////////////////////////////////////
			enum Type
			{
				v1, v2
			};
			Assymetric() = default;
			~Assymetric() = default;
			Assymetric(const Assymetric& assym) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Processes a single audio sample using the asymmetric saturation algorithm.
			///////////////////////////////////////////////////////////////////////////////////////
			float process(float sample,float k,float g,Type type);
		private:
			AuxPort::CircularBuffer<float> circBuffer;
			uint32_t counter = 0;
		};

		
	}
}

#endif