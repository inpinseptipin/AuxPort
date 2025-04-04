#ifndef OSCILLATOR_BENCH_H
#define OSCILLATOR_BENCH_H
/*
*			AuxBench
			"Bench Bench Bench" - inpinseptipin

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
		class Oscillator : public AuxPort::Bench,AuxPort::Timer
		{
		public:
			Oscillator() = default;
			~Oscillator() = default;
			Oscillator(const Oscillator& oscillator) = default;
			/**
			  @brief Sets the vector of oscillators and their names for benchmarking and logging 
			  @param oscillators
			  @param names
			  Example Implementation
			  \code{.cpp}
			  	AuxPort::Benchmarks::Oscillator oscillatorBench;
				std::vector<AuxPort::Audio::Oscillator> oscillators;
				oscillators.push_back(AuxPort::Audio::Sine::FastSine());
				oscillatorBench.setOscillators(oscillators,{"FastSine"});
			  \endcode 
			 */
			void setOscillators(const std::vector<AuxPort::Audio::Oscillator> oscillators, const std::vector<std::string> names);
			/**
			  @brief [Pure Virtual Function] Overridable this method to write your benchmarking scheme.
			  Example Definition
			  \code{.cpp}
			   void benchmark()
			   {
					auto sample = 0.0f;
					for (uint32_t i = 0; i < oscillators.size(); i++)
					{
						for (uint32_t j = 0; j < numberOfIterations; j++)
						{
							start();
							for (uint32_t k = 0; k < bufferSize; k++)
							{
								sample = oscillators[i].process();
							}
							stop();
							benchmarkTimes[i] += getEllapsedTime(AuxPort::Timer::nano);
						}
						benchmarkTimes[i] /= numberOfIterations;
					}
			   }
			  \endcode 
			 */
			void benchmark() override;
			/**
			  @brief sets benchmark parameters 
			  @param bufferSize
			  @param numberOfIterations
			  Example Implementation
			  \code{.cpp}
				AuxPort::Benchmarks::Oscillator oscillatorBench;
				oscillatorBench.setParameters(1024,1000);
			  \endcode 
			 */
			void setParameters(size_t bufferSize = 1024, size_t numberOfIterations = 1000);
			/**
			  @brief [Virtual Function] Override the function, to log the internal oscillator state.
			 */
			void Log() override;
		protected:
			std::vector<AuxPort::Audio::Oscillator> oscillators;
			std::vector<std::string> oscillatorNames;
			size_t bufferSize = 1024;
			size_t numberOfIterations = 1000;
		};
		
	}

	namespace Benches
	{

		class OscillatorBench
		{
		public:
			static void benchmarkSines(size_t bufferSize, size_t numberOfIterations);
			static void benchmarkSawtooths(size_t bufferSize, size_t numberOfIterations);
			static void benchmarkTriangle(size_t bufferSize, size_t numberOfIterations);
		};
	}

}

#endif