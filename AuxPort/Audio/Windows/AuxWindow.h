#ifndef AUXPORT_AUDIO_WINDOW_H
#define AUXPORT_AUDIO_WINDOW_H
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
#include "../Buffer/AuxBuffer.h"
#include "../../Core/Log/AuxLog.h"


namespace AuxPort
{
	namespace Audio
	{
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes Window functions such as Hann,Hamming,Kaiser.
		///////////////////////////////////////////////////////////////////////////////////////		
		class Window
		{
		public:
			enum TrimType
			{
				fromStart,fromEnd
			};
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Specifies the type of window
			///////////////////////////////////////////////////////////////////////////////////////
			enum Type
			{
				HannWin, HammWin, BlackmanWin, BartlettWin, BartlettHannWin, NuttallWin, FlatWin, BlackmanHarrisWin,RectangleWin
			};

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Samples a Window function and fills it in a memory allocated std::vector
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
				case Type::BartlettWin:
					Bartlett<sample>(windowBuffer);
					break;
				case Type::BartlettHannWin:
					BartlettHanning<sample>(windowBuffer);
					break;
				case Type::NuttallWin:
					Nuttall<sample>(windowBuffer);
					break;
				case Type::BlackmanHarrisWin:
					BlackmanHarris<sample>(windowBuffer);
					break;
				case Type::FlatWin:
					Flat<sample>(windowBuffer);
					break;
				case Type::RectangleWin:
					Rectangle<sample>(windowBuffer);
					break;
				default:
					return;
				}
			}
			/**
			  @brief Trims a window from the start or end with a percent amount 
			  @param windowBuffer
			  @param trimType
			  @param trimPercent
			  \code{.cpp}
			  auto window = AuxPort::Audio::Window::generate<float>(256);
			  AuxPort::Audio::Window::trim<float>(window,AuxPort::Audio::Window::TrimType::fromStart,25);
			  \endcode 
			 */
			template<class sample>
			static void trim(std::vector<sample>& windowBuffer, TrimType trimType, float trimPercent)
			{
				AuxAssert(windowBuffer.size() > 0, "Cannot trim an empty window");
				AuxAssert(trimPercent > 0 && trimPercent < 100, "Why would you even try that?");
				trimPercent = trimType == TrimType::fromStart ? trimPercent : 100 - trimPercent;
				auto endIndex = static_cast<size_t>(0.01 * trimPercent * windowBuffer.size());
				windowBuffer.erase(windowBuffer.begin(), windowBuffer.begin() + endIndex);
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns a std::vector with a Sampled Window Function
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
				case Type::BartlettWin:
					Bartlett<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::BartlettHannWin:
					BartlettHanning<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::NuttallWin:
					Nuttall<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::FlatWin:
					Flat<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::BlackmanHarrisWin:
					BlackmanHarris<sample>(windowBuffer);
					return windowBuffer;
					break;
				case Type::RectangleWin:
					Rectangle<sample>(windowBuffer);
					return windowBuffer;
					break;
				default:
					return windowBuffer;
				}
			}
		private:
			template<class sample>
			static void Rectangle(std::vector<sample>& windowBuffer)
			{
				Utility::constantThis(windowBuffer, 1.0f);
			}

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
				float N = static_cast<float>(windowBuffer.size() - 1);
				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					if (i >= 0 && i <= windowBuffer.size() / 2)
						val = static_cast<sample>(2 * i / N);
					if (i >= windowBuffer.size() / 2 && i < windowBuffer.size())
						val = static_cast<sample>(2 - 2 * i / N);
					windowBuffer[i] = val;
				}
			}

			template<class sample>
			static void BartlettHanning(std::vector<sample>& windowBuffer)
			{
				sample val;
				float N = static_cast<float>(windowBuffer.size() - 1);
				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					val = static_cast<sample>(0.62 - 0.48 * abs((i / N) - 0.5) + 0.38 * cos(2 * pi * ((i / N) - 0.5)));
					windowBuffer[i] = val;
				}	
			}

			template<class sample>
			static void Nuttall(std::vector<sample>& windowBuffer)
			{
				sample val;
				sample a0 = static_cast<sample>(0.3635819);
				sample a1 = static_cast<sample>(0.4891775);
				sample a2 = static_cast<sample>(0.1365995);
				sample a3 = static_cast<sample>(0.0106411);
				sample N = static_cast<sample>(windowBuffer.size() - 1);
				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					val = a0 - a1 * cos(2 * pi * i / N) + a2 * cos(4 * pi * i / N) - a3 * cos(6 * pi * i / N);
					windowBuffer[i] = val;
				}
					
			}

			template<class sample>
			static void Flat(std::vector<sample>& windowBuffer)
			{
				sample val;
				sample a0 = static_cast<sample>(0.21557895);
				sample a1 = static_cast<sample>(0.41663158);
				sample a2 = static_cast<sample>(0.277263158);
				sample a3 = static_cast<sample>(0.083578947);
				sample a4 = static_cast<sample>(0.006947368);
				float N = static_cast<float>(windowBuffer.size() - 1);
				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					val = a0 - a1 * cos(2 * pi * i / N) + a2 * cos(4 * pi * i / N) - a3 * cos(6 * pi * i / N) + a4 * cos(8 * pi * i / N);
					windowBuffer[i] = val;
				}
			}

			template<class sample>
			static void BlackmanHarris(std::vector<sample>& windowBuffer)
			{
				sample val;
				sample a0 = static_cast<sample>(0.35875);
				sample a1 = static_cast<sample>(0.48829);
				sample a2 = static_cast<sample>(0.14128);
				sample a3 = static_cast<sample>(0.01168);
				float N = static_cast<float>(windowBuffer.size() - 1);
				for (uint32_t i = 0; i < windowBuffer.size(); i++)
				{
					val = a0 - a1 * cos(2 * pi * i / N) + a2 * cos(4 * pi * i / N) - a3 * cos(6 * pi * i / N);
					windowBuffer[i] = val;
				}
			}
		};
	}
}



#endif