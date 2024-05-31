#ifndef AUXPORT_GAIN_H
#define AUXPORT_GAIN_H

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



#include "../../../Core/Utility/AuxUtility.h"
namespace AuxPort
{
	namespace Audio
	{
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Stereo Audio Panner
		/// @details
		/// 2 channel Panning class with 4 algorithms
		/// - Linear Pan
		/// - Sqrt Pan
		/// - Sinusoidal Pan
		/// - Constant Power Pan
		///////////////////////////////////////////////////////////////////////////////////////
		class Pan
		{
		public:
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Type of Audio Panner
			///////////////////////////////////////////////////////////////////////////////////////
			enum Type
			{
				Linear,	///< Linear Pan
				Sqrt,	///< Sqrt Pan
				Sinusoidal,	///< Sinusoidal Pan
				Constant	///< Constant Power Pan
			};

			Pan(const Type& type = Type::Linear);
			~Pan() = default;
			Pan(const Pan& gain) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Use the setPan function to update the panning Value, Specify the range of the parameter so that the internal dsp object can remap the value.
			///////////////////////////////////////////////////////////////////////////////////////
			void setPan(float pan, float panStart, float panEnd);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Use the function to apply Pan to a Stereo Frame
			///////////////////////////////////////////////////////////////////////////////////////
			void process(float& leftChannel, float& rightChannel);
		private:
			Type type;
			float pan;
		};
	}
}


#endif