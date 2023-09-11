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
		template<class sample>
		class Window
		{
		public:
			enum Type
			{
				HannWin, HammWin
			};
			static void generate(AuxPort::Audio::Buffer<sample>& windowBuffer, const size_t& windowSize, const Type& window = Type::Hann)
			{
				if (windowSize == 0)
					return;
				else
				{
					switch (window)
					{
					case Type::HannWin:
						Hann(windowBuffer, windowSize);
						break;
					case Type::HammWin:
						Hamming(windowBuffer, windowSize);
						break;
					default:
						return;
					}
				}
			}
		private:
			static void Hann(AuxPort::Audio::Buffer<sample>& windowBuffer, const size_t& windowSize)
			{
				windowBuffer.resize(windowSize);
				sample val;
				for (size_t i = 0; i < windowSize; i++)
				{
					val = static_cast<sample>(0.5 * (1 - cos(2 * pi * i / windowSize)));
					windowBuffer.set(val, i);
				}
			}

			static void Hamming(AuxPort::Audio::Buffer<sample>& windowBuffer, const size_t& windowSize)
			{
				windowBuffer.resize(windowSize);
				sample val;
				for (size_t i = 0; i < windowSize; i++)
				{
					val = static_cast<sample>(0.54 - 0.46 * cos(2 * pi * i / windowSize));
					windowBuffer.set(val, i);
				}
			}


		};
	}
}



#endif