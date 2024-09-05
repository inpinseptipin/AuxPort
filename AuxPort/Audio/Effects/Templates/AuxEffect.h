#ifndef AUXEFFECT_H
#define AUXEFFECT_H

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



#include "../../../Core/Env/AuxEnv.h"
#include "../../../Core/Log/AuxLog.h"
#include <vector>

namespace AuxPort
{
	namespace Audio
	{
///////////////////////////////////////////////////////////////////////////////////////
/// @brief This class can be inherited in the design,development,analysis and benchmark an audio plugin
///////////////////////////////////////////////////////////////////////////////////////
		class Effect
		{
		public:
///////////////////////////////////////////////////////////////////////////////////////
/// @brief Provides the sample rate to the audio plugin
///////////////////////////////////////////////////////////////////////////////////////
			void setSampleRate(uint32 sampleRate);
///////////////////////////////////////////////////////////////////////////////////////
/// @brief Provides the parameters to the audio plugin
///////////////////////////////////////////////////////////////////////////////////////
			void setParameters(const std::vector<float>& parameters);
///////////////////////////////////////////////////////////////////////////////////////
/// @brief This function processes a buffer
///////////////////////////////////////////////////////////////////////////////////////
			void process(std::vector<float>& buffer);
		protected:
///////////////////////////////////////////////////////////////////////////////////////
/// @brief Override this function to write your DSP for a buffer filled with audio.
///////////////////////////////////////////////////////////////////////////////////////
			virtual void processBlock(std::vector<float>& buffer) = 0;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief Override this function to benchmark the DSP code...argument provides the computational time of the latest buffer
///////////////////////////////////////////////////////////////////////////////////////
			virtual void benchmarkBlock(float time) = 0;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief Override this function to do analysis on the audio buffer
///////////////////////////////////////////////////////////////////////////////////////
			virtual void analysisBlock(const std::vector<float>& buffer) = 0;
			uint32 sampleRate;
			std::vector<float> parameters;
			AuxPort::Timer timer;
		};
	}
}


#endif