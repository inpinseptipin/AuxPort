#ifndef AUXBENCH_H
#define AUXBENCH_H
/*
*			AuxTest
			"Test Test Test" - inpinseptipin

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

#include "../../../AuxPort/AuxPort.h"

///////////////////////////////////////////////////////////////////////////////////////
/// @brief This namespace contains testing modules for the AuxPort Library
///////////////////////////////////////////////////////////////////////////////////////
namespace AuxPort
{
	namespace Benchmarks
	{
		class Oscillator : protected AuxPort::Timer, AuxPort::ILog
		{
		public:
			Oscillator() = default;
			~Oscillator() = default;
			Oscillator(const Oscillator& oscillators) = default;
			void attachOscillator(AuxPort::Audio::Oscillator* oscillator);
			void benchmark(size_t bufferSize = 1024, size_t numberOfIterations = 1000);
			void Log() override;
		protected:
			AuxPort::Audio::Oscillator* oscillator;
			size_t bufferSize;
			size_t numberOfIterations;
			float benchmarkTime;
		};
	}

}

#endif