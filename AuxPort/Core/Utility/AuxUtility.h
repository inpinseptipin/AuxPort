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
#include <random>
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



		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Converts decibels (dB) to single-precision float		
		///////////////////////////////////////////////////////////////////////////////////////
		static inline float dBToLinear(float val)
		{
			return powf(10.0f, (val / 20.0f));
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Converts decibels (dB) to double-precision float	
		///////////////////////////////////////////////////////////////////////////////////////
		static inline double dBToLinear(double val)
		{
			return pow(10.0, (val / 20.0));
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Converts single-precision float to decibels (dB)	
		///////////////////////////////////////////////////////////////////////////////////////
		static inline float linearTodB(float val)
		{
			return 20.0f * log10f(val);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Converts double-precision float to decibels (dB)		
		///////////////////////////////////////////////////////////////////////////////////////
		static inline double linearTodB(double val)
		{
			return 20.0 * log10(val);
		}


		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Fill a standard vector with zeros		
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void zeroThis(std::vector<sample>& audio)
		{
			for (uint32 i = 0; i < audio.size(); i++)
				audio[i] = 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Evaluates the Signum function
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample signum(const sample& audio)
		{
			return  audio < 0 ? -1.0f : audio > 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Rounds a number to the nearest integer	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample round(const sample& audio)
		{
			return audio > 0.0 ? static_cast<sample>(floor(audio + 0.5)) : static_cast<float>(ceil(audio - 0.5));
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Remaps a input in a particular range to another range.
		///////////////////////////////////////////////////////////////////////////////////////
		template<class range>
		static inline range remap(range input, range outputStart, range outputEnd, range inputStart, range inputEnd)
		{
			double slope = 1.0f * (outputEnd - outputStart) / (inputEnd - inputStart);
			return outputStart + static_cast<range>(slope) * (input - inputStart);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Computes the mean for a vector		
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample mean(const std::vector<sample>& vector)
		{
			sample sum = 0;
			for (uint32_t i = 0; i < vector.size(); i++)
				sum += vector[i];
			sum /= vector.size();
			return sum;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Computes the median for a vector [Time Complexity : O(Nlog2(n)), Memory Complexity : O(N)]	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample median(std::vector<sample> vector)
		{
			std::sort(vector.begin(), vector.end());
			return vector.size() % 2 == 0 ? vector[vector.size() / 2] : mean<sample>({ vector[vector.size() / 2],vector[vector.size() / 2 + 1] });
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Normalizes a vector with a val.		
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void norm(std::vector<sample>& vec, float norm)
		{
			AuxAssert(norm != 0, "Cannot Divide by Zero");
			for (uint32_t i = 0; i < vec.size(); i++)
				vec[i] /= norm;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Computes sum of a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample sum(const std::vector<sample>& vec)
		{
			AuxAssert(vec.size() > 0, "Cannot take the absolute sum of an empty vector");
			sample sum = 0;
			for (uint32_t i = 0; i < vec.size(); i++)
				sum += vec[i];
			return sum;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Computes absolute sum of a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample abssum(const std::vector<sample>& vec)
		{
			AuxAssert(vec.size() > 0, "Cannot take the absolute sum of an empty vector");
			sample sum = 0;
			for (uint32_t i = 0; i < vec.size(); i++)
				sum += abs(vec[i]);
			return sum;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Returns a std::vector with Random Values between a range	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline std::vector<sample> generateRandomValues(size_t size, float rangeStart = -1.0, float rangeEnd = 1.0)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distr(rangeStart, rangeEnd);
			std::vector<sample> vec;
			vec.resize(size);
			for (uint32_t i = 0; i < vec.size(); i++)
				vec[i] = distr(gen);
			return vec;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Fills a memory allocated std::vector with random values.	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void generateRandomValues(std::vector<sample>& vector, float rangeStart = -1.0, float rangeEnd = 1.0)
		{
			AuxAssert(vector.size() > 0, "Vector size should be greater than 0")
				std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distr(rangeStart, rangeEnd);
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] = static_cast<sample>(distr(gen));
		}


		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Computes the max element in an std::vector	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample getMax(const std::vector<sample>& vector)
		{
			AuxAssert(vector.size() > 0, "Vector size should be greater than 0");
			if (vector.size() == 1)
				return vector[0];
			sample max = vector[0];
			for (uint32_t i = 1; i < vector.size(); i++)
				max = max < vector[i] ? vector[i] : max;
			return max;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Dot-Divide operation over a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void divide(std::vector<sample>& vector, sample value)
		{
			AuxAssert(value != 0, "Divide by Zero encountered");
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] /= value;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Dot-Divide operation over a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void multiply(std::vector<sample>& vector, sample value)
		{
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] *= value;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Dot-Divide operation over a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void multiply(std::vector<sample>& vector1, const std::vector<sample>& vector2)
		{
			for (uint32_t i = 0; i < vector1.size(); i++)
				vector1[i] *= vector2[i];
		}


		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Sinc(x) = sin(pi*x)/pi*x (Normalized Sinc Function)
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample sinc(sample val)
		{
			return val == 0 ? 1 : sinf(val * pi) / (val * pi);
		}

		template<class sample>
		static inline void constantThis(std::vector<sample>& vec, sample val)
		{
			for (uint32_t i = 0; i < vec.size(); i++)
				vec[i] = val;
		}

		static void split(std::vector<std::string>& tokens, const std::string& str, const char& delimiter)
		{
			tokens.clear();
			std::stringstream stream(str);
			std::string token;
			while (getline(stream, token, delimiter))
			{
				tokens.push_back(token);
			}
		}

		static void join(std::string& str, const std::vector<std::string>& tokens, const char& delimiter)
		{
			str = "";
			size_t tokensCount = tokens.size();
			for (size_t i = 0; i < tokensCount - 1; i++)
			{
				str += tokens[i] + delimiter;
			}
			str += tokens[tokensCount - 1];
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Evaluates a polynomial  of the following form using Horner's Method:
		/// a(n) * x^n + a(n-1) * x^(n-1) + .......... + a(1) * x + a(0) 
		/// Coefficients Vector contains the coefficients [a(0), a(1), ...... , a(n-1), a(n)]
		/// Make sure to consider the maximum value of float while evaluating polynomial. Trying to evaluate
		/// polynomials with large number of coefficients (or large power of x) may result in infinity.
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static sample horner(const std::vector<sample>& coefficients, sample x)
		{
			AuxAssert(!coefficients.empty(), "Coefficients Vector cannot be empty!");
			sample result = 0;
			for (int i = coefficients.size() - 1; i > -1; i--)
			{
				result = (result * x) + coefficients[i];
			}
			return result;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Static] Evaluates a polynomial  of the following form using Estrin's Algorithm:
		/// a(n) * x^n + a(n-1) * x^(n-1) + .......... + a(1) * x + a(0) 
		/// EvenIndexCoefficients contains the coefficients [a(0), a(2), ...]
		/// OddIndexCoefficients contains the coefficients [a(1), a(3), ...]
		/// SIMD Instruction Set must be available for this function to work!!
		/// Make sure to consider the maximum value of float while evaluating polynomial. Trying to evaluate
		/// polynomials with large number of coefficients (or large power of x) may result in infinity.
		///////////////////////////////////////////////////////////////////////////////////////
		static float estrin(std::vector<float>& evenIndexCoefficients, std::vector<float>& oddIndexCoefficients, float x)
		{
#if AUXSIMD
			AuxAssert(AuxPort::Env::supportsAVX(), "The current processor does not support AVX and hence 256-bit SIMD instructions cannot be performed.");

			// Determining the maximum Power of x we need to compute explicitly (or how many times the outer loop will run)
			uint32 outerIterationCount = log2(evenIndexCoefficients.size() + oddIndexCoefficients.size());

			// Making sure both vectors are of equal sizes and have size as a multiple of 8. 
			// OddIndexCoefficients vector might have one less element in some cases but it will be dealt with here
			size_t paddedSize = evenIndexCoefficients.size() + (8 - evenIndexCoefficients.size() % 8) % 8;
			evenIndexCoefficients.resize(paddedSize);
			oddIndexCoefficients.resize(paddedSize);

			uint32 writeIndex;
			auto xRegister = _mm256_set1_ps(x);
			auto evenIdx = _mm256_setr_epi32(0, 2, 4, 6, 0, 0, 0, 0);
			auto oddIdx = _mm256_setr_epi32(1, 3, 5, 7, 0, 0, 0, 0);
			while (outerIterationCount--)
			{
				writeIndex = 0;
				for (uint32_t i = 0; i < evenIndexCoefficients.size(); i += 8)
				{
					auto OddRegister = _mm256_loadu_ps(oddIndexCoefficients.data() + i);
					auto EvenRegister = _mm256_loadu_ps(evenIndexCoefficients.data() + i);
					auto ansRegister = _mm256_fmadd_ps(xRegister, OddRegister, EvenRegister);

					_mm256_storeu_ps(evenIndexCoefficients.data() + writeIndex, _mm256_permutevar8x32_ps(ansRegister, evenIdx));
					_mm256_storeu_ps(oddIndexCoefficients.data() + writeIndex, _mm256_permutevar8x32_ps(ansRegister, oddIdx));

					writeIndex += 4;
				}

				evenIndexCoefficients.resize(writeIndex + 1);
				oddIndexCoefficients.resize(writeIndex + 1);

				x = x * x;
				xRegister = _mm256_set1_ps(x);
			}

			return evenIndexCoefficients[0] + oddIndexCoefficients[0] * x;
#else
			AuxPort::Logger::Log("SIMD Instruction set not available! Please use Horner's Algorithm for polynomial evaluation.");
			return 0.0f;
#endif
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