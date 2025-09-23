#ifndef AUXPORT_UTILITY_H
#define AUXPORT_UTILITY_H
/*
			AuxPort Library
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

#include "../Env/AuxEnv.h"
#include "../Log/AuxLog.h"
#include <complex>
#include <random>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <unordered_map>

namespace AuxPort
{
	const std::complex<double> iota(0, 1);
	const float pi = 3.14159265358979323846264338328F;
	const float sqrt2 = 1.41421356237F;
	const float e = 2.718281828459F;

	///////////////////////////////////////////////////////////////////////////////////////	
	/// @brief This class provides interfaces (Static Functions) for stuff that are easy to implement but still require you to write code for it.
	///////////////////////////////////////////////////////////////////////////////////////
	class Utility
	{
	public:
		
#ifdef AUXPORT_64	
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Calculates the number of digits present in an integer.		
		///////////////////////////////////////////////////////////////////////////////////////
		static uint64 numberOfDigits(int64 number)
		{
			uint64 noOfDigits = number ? 0l : 1l; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
		
		static uint64 numberOfDigits(uint64 number)
		{
			uint64 noOfDigits = number ? 0l : 1l; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
#else	
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Calculates the number of digits present in an integer.		
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32 numberOfDigits(int32 number)
		{
			uint32 noOfDigits = number ? 0 : 1; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
#endif 

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts decibels (dB) to single-precision float		
		///////////////////////////////////////////////////////////////////////////////////////
		static inline float dBToLinear(float val)
		{
			return powf(10.0f, (val / 20.0f));
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts decibels (dB) to double-precision float	
		///////////////////////////////////////////////////////////////////////////////////////
		static inline double dBToLinear(double val)
		{
			return pow(10.0, (val / 20.0));
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts single-precision float to decibels (dB)	
		///////////////////////////////////////////////////////////////////////////////////////
		static inline float linearTodB(float val)
		{
			return 20.0f * log10f(val);
		}

		static inline std::vector<float> linearTodB(std::vector<float>& data)
		{
			auto dbData = data;
			for (uint32_t i = 0;i < data.size();i++)
				dbData[i] = 20.0f * log10f(data[i]);
			return dbData;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Converts double-precision float to decibels (dB)		
		///////////////////////////////////////////////////////////////////////////////////////
		static inline double linearTodB(double val)
		{
			return 20.0 * log10(val);
		}


		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Fill a standard vector with zeros		
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void zeroThis(std::vector<sample>& audio)
		{
			for (uint32 i = 0; i < audio.size(); i++)
				audio[i] = 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Evaluates the Signum function
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample signum(sample audio)
		{
			return  audio < 0 ? -1.0f : audio > 0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Rounds a number to the nearest integer	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample round(sample audio)
		{
			return audio > 0.0 ? static_cast<sample>(floor(audio + 0.5)) : static_cast<float>(ceil(audio - 0.5));
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Remaps a input in a particular range to another range.
		///////////////////////////////////////////////////////////////////////////////////////
		template<class range>
		static inline range remap(range input, range outputStart, range outputEnd, range inputStart, range inputEnd)
		{
			double slope = 1.0f * (outputEnd - outputStart) / (inputEnd - inputStart);
			return outputStart + static_cast<range>(slope) * (input - inputStart);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes the mean for a vector		
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
		/// @brief Computes the median for a vector [Time Complexity : O(Nlog2(n)), Memory Complexity : O(N)]	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample median(const std::vector<sample>& vector)
		{
			std::sort(vector.begin(), vector.end());
			return vector.size() % 2 == 0 ? vector[vector.size() / 2] : mean<sample>({ vector[vector.size() / 2],vector[vector.size() / 2 + 1] });
		}
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Normalizes a vector with a val.		
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void norm(std::vector<sample>& vec, float norm)
		{
			AuxAssert(norm != 0, "Cannot Divide by Zero");
			for (uint32_t i = 0; i < vec.size(); i++)
				vec[i] /= norm;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes absolute sum of a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample abssum(const std::vector<sample>& vec)
		{
			AuxAssert(vec.size() > 0, "Cannot take the absolute sum of an empty vector");
			sample sum = 0;
			for (uint32_t i = 0; i < vec.size(); i++)
				sum += std::abs(vec[i]);
			return sum;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns a std::vector with Random Values between a range	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline std::vector<sample> generateRandomValues(size_t size, float rangeStart = -1.0, float rangeEnd = 1.0)
		{
			std::vector<sample> vec;
			vec.resize(size);
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distr(rangeStart, rangeEnd);
			for (uint32_t i = 0; i < vec.size(); i++)
				vec[i] = static_cast<sample>(distr(gen));
			return vec;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Fills a memory allocated std::vector with random values.	
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void generateRandomValues(std::vector<sample>& vector,float rangeStart = -1.0, float rangeEnd = 1.0)
		{
			AuxAssert(vector.size() > 0,"Vector size should be greater than 0")
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<> distr(rangeStart, rangeEnd);
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] = static_cast<sample>(distr(gen));
		}


		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes the max element in an std::vector	
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
		/// @brief Dot-Divide operation over a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void divide(std::vector<sample>& vector, sample value)
		{
			AuxAssert(value != 0, "Divide by Zero encountered");
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] /= value;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Dot-Multiply operation over a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void multiply(std::vector<sample>& vector, sample value)
		{
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] *= value;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Dot-multiply operation over a std::vector
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void multiply(std::vector<sample>& vector1, const std::vector<sample>& vector2)
		{
			for (uint32_t i = 0; i < vector1.size(); i++)
				vector1[i] *= vector2[i];
		}

		
		

		template<class sample>
		static inline void impulse(std::vector<sample>& vector, size_t numberOfSamples)
		{
			vector.resize(numberOfSamples);
			std::fill(vector.begin(), vector.end(), 0.0f);
			vector[0] = 1.0f;	
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sinc(x) = sin(pi*x)/pi*x (Normalized Sinc Function)
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline sample sinc(sample val)
		{
			return val == 0 ? 1 : sinf(val*pi) / (val*pi);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Fills up all the elements of the given vector with the given value
		///////////////////////////////////////////////////////////////////////////////////////
		template<class sample>
		static inline void constantThis(std::vector<sample>& vec, sample val)
		{
			for (uint32_t i = 0; i < vec.size(); i++)
				vec[i] = val;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Splits the given string in a vector of tokens based on the given delimiter
		///////////////////////////////////////////////////////////////////////////////////////
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

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Joins the given vector of tokens using the given delimiter to form a string
		///////////////////////////////////////////////////////////////////////////////////////
		static void join(std::string& str, const std::vector<std::string>& tokens, const char& delimiter)
		{
			str = "";
			if (tokens.empty()) return;
			size_t tokensCount = tokens.size();
			for (size_t i = 0; i < tokensCount - 1; i++)
			{
				str += tokens[i] + delimiter;
			}
			str += tokens[tokensCount - 1];
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Linear Interpolation
		///////////////////////////////////////////////////////////////////////////////////////
		static float lerp(float start, float target, float delta)
		{
			return start + (target - start) * delta;
		}

		/**
		  @brief Converts degrees to radians
		  @param degrees
		  @param normalizedTo2pi  = true (Default)
		  @return
		  @details
		  Example Implementation
		  \code{.cpp}
			auto inRadians = AuxPort::Utility::degreesToRadians(900)
		  \endcode 
		 */
		template<class sample>
		static sample degreesToRadians(float degrees,bool normalizedTo2pi = true)
		{
			return normalizedTo2pi ? fmod(degrees, 360.0f) * 0.0174533f : degrees * 0.0174533f;
		}

		static std::string convertToTime(uint32_t seconds)
		{
			auto secondsInFloat = static_cast<float>(seconds);
			float hours = std::floorf(secondsInFloat / 3600);
			float mins = std::floorf((secondsInFloat - (hours * 3600)) / 60);
			float secs = std::floorf(secondsInFloat - (hours*3600) - (mins*60));
			return std::to_string(hours) + " : " + std::to_string(mins) + " : " + std::to_string(secs);
		}
		 /*
		  @brief Performs Linear Search over a vector
		  @param vector
		  @param data 
		  @return
		 */
		template<class sample>
		static int search(const std::vector<sample>& vector, float data)
		{
			for (int i = 0; i < vector.size(); i++)
				if (data == vector[i])
					return i;
			return -1;
		}

		
		/**
		  @brief Applies abs over a vector [In-Place]
		  @param vector
		  @param data 
		  @return
		 */
		static void abs(std::vector<float>& vector)
		{
			for (size_t i = 0; i < vector.size(); i++)
				vector[i] = std::fabsf(vector[i]);
		}

		/**
		  @brief Formats a floating point value to a string that's acceptable as a filename on a given OS
		  @details
		  Example :  0.05 will be convered to 0_05
		 */
		static std::string formatFloatForFileNames(float val)
		{
			auto data = std::to_string(val);
			data = data.replace(data.find("."), data.find("."), "_");
			return data;
		}
#if AUXPORT_EXP == 1337
		/**
		  @brief Fast Approximation for conputing x^n 
		  @param x
		  @param n
		  @return 
		 */
		static float pow(float x,int n)
		{
			long* lp, l;
			lp = (long*)(&x);
			l = *lp;
			l -= 0x3F800000l;
			l <<= (n-1);
			l += 0x3F800000l;
			*lp = l;		
			return x;
		}

		/**
		  @brief Fast approximation for root of x 
		  @param x
		  @param n
		  @return 
		 */
		static float root(float x, int n)
		{
			long* lp, l;
			lp = (long*)(&x);
			l = *lp;
			l -= 0x3F800000l;
			l >>= (n - 1);
			l += 0x3F800000l;
			*lp = l;
			return x;
		}
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief Provides funnctions to get Information about current Enviroment
	///////////////////////////////////////////////////////////////////////////////////////
	class About
	{
	public:	
		static void printAbout()
		{
			Env::isArm() ? AuxPort::Logger::Log("Detected Architecture : Arm",AuxPort::LogType::Success,AuxPort::ColourType::Light_Purple):AuxPort::Logger::Log("Detected Architecture : x86_64",AuxPort::LogType::Success,AuxPort::ColourType::Light_Purple);
			if (Env::isWindowsOS())
				AuxPort::Logger::Log("Detected OS : Windows", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			else if (Env::isLinuxOS())
				AuxPort::Logger::Log("Detected OS : Linux", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			else if (Env::isMacOS())
				AuxPort::Logger::Log("Detected OS : Mac", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			else
				AuxPort::Logger::Log("Unknown OS", AuxPort::LogType::Warning, AuxPort::ColourType::Red);

			Env::supportsMMX() == true ? AuxPort::Logger::Log("MMX is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("MMX is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsAVX() == true ? AuxPort::Logger::Log("AVX is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple): AuxPort::Logger::Log("AVX is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE() == true ? AuxPort::Logger::Log("SSE is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE2() == true ? AuxPort::Logger::Log("SSE2 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple): AuxPort::Logger::Log("SSE2 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE4_1() == true ? AuxPort::Logger::Log("SSE4.1 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE4.1 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE4_2() == true ? AuxPort::Logger::Log("SSE4.2 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE4.2 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsNeon() == true ? AuxPort::Logger::Log("Neon is Supported",AuxPort::LogType::Success,AuxPort::ColourType::Light_Purple):AuxPort::Logger::Log("Neon is not Supported",AuxPort::LogType::Success,AuxPort::ColourType::Light_Purple);
		}
	private:
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides an interface to compute Expansions
	///////////////////////////////////////////////////////////////////////////////////////
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

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the type of expansion
		///////////////////////////////////////////////////////////////////////////////////////
		void setType(const Type& type);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sets the max size of the expansion
		///////////////////////////////////////////////////////////////////////////////////////
		void setMaxSize(uint32_t N);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes the expansion using given xPowers and yPowers
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<float>& compute(const std::vector<float>& xPowers, const std::vector<float>& yPowers, uint32_t N);
	private:
		std::vector<float> leftAccumulator;
		std::vector<float> rightAccumulator;
		std::vector<float> terms;
		float sum;
		Type type;
	};


	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides functionality to compute and manage powers of a given sample.
	///////////////////////////////////////////////////////////////////////////////////////
	class Terms
	{
	public:
		Terms();
		~Terms() = default;
		Terms(const Terms& terms) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes the powers of the given sample (from sample^0 to sample^powers).
		/// The computed powers are stored in the internal vector.
		///////////////////////////////////////////////////////////////////////////////////////
		void computePowers(float sample, uint32_t powers);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes the additional powers of the given sample.
		///////////////////////////////////////////////////////////////////////////////////////
		void computeAdditionalPowers(uint32_t start, uint32_t end);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns a refrence to the internal vector which contains the calculated powers.
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<float>& getInternalVector();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Swaps the contents with another Term Object
		///////////////////////////////////////////////////////////////////////////////////////
		void swap(Terms& term);
	private:
		std::vector<float> termPowers;
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides an efficient way to generate random float values
	///////////////////////////////////////////////////////////////////////////////////////
	class FastRandomFloat
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Default constructor. This initializes the class with a random seed value of 1
		///////////////////////////////////////////////////////////////////////////////////////
		FastRandomFloat();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This initialized the class with the given random seed value. T
		/// @note The given randomSeed should be non-zero.
		///////////////////////////////////////////////////////////////////////////////////////
		FastRandomFloat(const int& randomSeed);

		FastRandomFloat(const FastRandomFloat& random) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns a random float value between -1 and 1
		///////////////////////////////////////////////////////////////////////////////////////
		float getRandomFloat();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns a random float value in the range [start, end]
		///////////////////////////////////////////////////////////////////////////////////////
		float getRandomFloat(float start, float end);
	private:
		int randomSeed;
	};

	



	

}
#endif

