#pragma once
#ifndef AUXPORT_AUDIO_WINDOW_H
#define AUXPORT_AUDIO_WINDOW_H
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

#include "../../Core/Env/AuxEnv.h"
#include "../Buffer/AuxBuffer.h"
#include "../../Core/Log/AuxLog.h"


namespace AuxPort
{
	namespace Audio
	{
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Class] Computes Window functions such as Hann,Hamming,Kaiser.
		///////////////////////////////////////////////////////////////////////////////////////		
		class Window
		{
		public:
			enum Type
			{
				HannWin, HammWin, BlackmanWin,BarlettWin
			};
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Samples a Window function and fills it in a memory allocated std::vector
			///////////////////////////////////////////////////////////////////////////////////////
			template<class sample>
			static void generate(std::vector<sample>& windowBuffer, const Type& windowType = Type::HannWin)
			{
				AuxAssert(windowBuffer.size() > 0, "Cannot generate a Window of Size <= 0");
				switch (windowType)
				{
				case Type::HannWin:
					Hann<sample>(windowBuffer);
					break;
				case Type::HammWin:
					Hamming<sample>(windowBuffer);
					break;
				case Type::BlackmanWin:
					Blackman<sample>(windowBuffer);
					break;
				case Type::BarlettWin:
					Bartlett<sample>(windowBuffer);
					break;
				default:
					return;
				}
				
			}
			///////////////////////////////////////////////////////////////////////////////////////
			/// [Function] Returns a std::vector with a Sampled Window Function
			///////////////////////////////////////////////////////////////////////////////////////
			template<class sample>
			static std::vector<sample> generate(size_t windowSize, Type windowType = Type::HannWin)
			{
				AuxAssert(windowSize > 0,"Cannot generate a Window of Size <= 0");
				std::vector<sample> windowBuffer;
				windowBuffer.resize(windowSize);
				switch (windowType)
				{
				case Type::HannWin:
					Hann<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::HammWin:
					Hamming<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::BlackmanWin:
					Blackman<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::BarlettWin:
					Bartlett<sample>(windowBuffer);
					return windowBuffer;
					break;
				default:
					return windowBuffer;
				}
			}

		private:
			template<class sample>
			static void Hann(std::vector<sample>& windowBuffer)
			{
				sample val;
				auto N = windowBuffer.size() - 1;
				for (size_t i = 0; i < windowBuffer.size(); i++)
				{
					val = static_cast<sample>(0.5 * (1 - cos(2 * pi * i / N)));
					windowBuffer[i] = val;
				}
			}
			template<class sample>
			static void Hamming(std::vector<sample>& windowBuffer)
			{
				sample val;
				auto N = windowBuffer.size() - 1;

				for (size_t i = 0; i < windowBuffer.size(); i++)
				{
					val = static_cast<sample>(0.54 - 0.46 * cos(2 * pi * i / N));
					windowBuffer[i] = val;
				}
			}

			template<class sample>
			static void Blackman(std::vector<sample>& windowBuffer)
			{
				sample val;
				auto N = windowBuffer.size() - 1;

				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					val = static_cast<sample>(0.42 - 0.5 * (cos(2 * pi * i / N)) + 0.08 * cos(4 * pi * i / N));
					windowBuffer[i] = val;
				}
			}

			template<class sample>
			static void Bartlett(std::vector<sample>& windowBuffer)
			{
				sample val;
				float N = windowBuffer.size() - 1;
				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					if (i >= 0 && i <= windowBuffer.size() / 2)
						val = static_cast<sample>(2 * i / N);
					if (i >= windowBuffer.size() / 2 && i < windowBuffer.size())
						val = static_cast<sample>(2 - 2 * i / N);
					windowBuffer[i] = val;
				}
			}


		};
	}
}



#endif