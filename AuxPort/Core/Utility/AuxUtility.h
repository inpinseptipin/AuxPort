#ifndef AUXPORT_UTILITY_H
#define AUXPORT_UTILITY_H
/*
			AuxPort Library
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
#include "../Env/AuxEnv.h"
#include <complex>
namespace AuxPort
{
	const std::complex<double> iota(0, 1);
	const float pi = 3.14159265358979323846264338328F;
	const float sqrt2 = 1.41421356237F;
	const float e = 2.718281828459F;

	///////////////////////////////////////////////////////////////////////////////////////	
	/// Utility is a class that provides interfaces (Static Functions) for stuff that are easy to implement but still require you to write code for it.
	///////////////////////////////////////////////////////////////////////////////////////
	class Utility
	{
	public:
#ifdef AUXPORT_64	
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Calculates the number of digits present in an integer.		
		///////////////////////////////////////////////////////////////////////////////////////
		static uint64 numberOfDigits(int64 number)
		{
			uint64 noOfDigits = number ? 0 : 1; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
#else	
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Calculates the number of digits present in an integer.		
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32 numberOfDigits(int32 number)
		{
			uint32 noOfDigits = number ? 0 : 1; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
#endif 

		static inline std::vector<float> generateRandomVals(uint32_t size)
		{
			srand(0);
			std::vector<float> vals(size);
			for (uint32_t i = 0; i < vals.size(); i++)
				vals[i] = rand() / RAND_MAX;
			return vals;
		}

		static inline float dBToLinear(float val)
		{
			return powf(10.0f, (val / 20.0f));
		}

		static inline double dBToLinear(double val)
		{
			return pow(10.0, (val / 20.0));
		}

		static inline float linearTodB(float val)
		{
			return 20.0f * log10f(val);
		}

		static inline double linearTodB(double val)
		{
			return 20.0 * log10(val);
		}

		template<class sample>
		static inline void zeroThis(std::vector<sample>& audio)
		{
			for (uint32 i = 0; i < audio.size(); i++)
				audio[i] = 0;
		}

		template<class sample>
		static inline sample signum(const sample& audio)
		{
			return  audio < 0 ? -1 : audio > 0;
		}

		template<class sample>
		static inline sample round(const sample& audio)
		{
			return audio > 0.0 ? static_cast<sample>(floor(audio + 0.5)) : static_cast<float>(ceil(audio - 0.5));
		}

		template<class range>
		static inline range remap(range input, range outputStart, range outputEnd, range inputStart, range inputEnd)
		{
			double slope = 1.0f * (outputEnd - outputStart) / (inputEnd - inputStart);
			return outputStart + slope * (input - inputStart);
		}

		template<class sample>
		static inline sample mean(const std::vector<sample>& vector)
		{
			sample sum = 0;
			for (uint32_t i = 0; i < vector.size(); i++)
				sum += vector[i];
			sum /= vector.size();
			return sum;
		}

		template<class sample>
		static inline sample median(const std::vector<sample>& vector)
		{
			sample sum = 0;
		}
		
	};

	class Expansions
	{
	public:
		enum Type
		{
			CDAA, ADAA
		};
		Expansions();
		~Expansions() = default;
		Expansions(const Expansions& expansions) = default;
		void setType(const Type& type);
		void setMaxSize(uint32_t N);
		std::vector<float>& compute(const std::vector<float>& xPowers, const std::vector<float>& yPowers, uint32_t N);

	private:
		std::vector<float> leftAccumulator;
		std::vector<float> rightAccumulator;
		std::vector<float> terms;
		float sum;
		Type type;
	};

	class Terms
	{
	public:
		Terms();
		~Terms() = default;
		Terms(const Terms& terms) = default;
		void computePowers(float sample, uint32_t powers);
		void computeAdditionalPowers(uint32_t start, uint32_t end);
		std::vector<float>& getInternalVector();
		void swap(Terms& term);
	private:
		std::vector<float> termPowers;
	};

}
#endif

