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
#include "../Utility/AuxCircularBuffer.h"
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
		static uint64_t numberOfDigits(int64_t number)
		{
			uint64_t noOfDigits = number ? 0l : 1l; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
		
		static uint64_t numberOfDigits(uint64_t number)
		{
			uint64_t noOfDigits = number ? 0l : 1l; while (number) { noOfDigits++, number /= 10; };
			return noOfDigits;
		}
#else	
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Calculates the number of digits present in an integer.		
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32_t numberOfDigits(int32_t number)
		{
			uint32_t noOfDigits = number ? 0 : 1; while (number) { noOfDigits++, number /= 10; };
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

		static inline void linearTodB(std::vector<float>& data)
		{
			for (uint32_t i = 0;i < data.size();i++)
				data[i] = linearTodB(data[i]);
		}

		static inline void linearTodB(float* data, uint32_t bufferSize)
		{
			for (uint32_t i = 0; i < bufferSize; i++)
					data[i] = linearTodB(data[i]);
		}

		/**
		  @brief Replaces all values in a 1D vector with -negInfinity to the norm value. 
		  @param data
		  @param normValue
		 */
		static inline void normFromNegInfinity(std::vector<float>& data, float normValue)
		{
			for (uint32_t i = 0;i < data.size();i++)
				data[i] = data[i] < normValue ? normValue : data[i];
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
			for (uint32_t i = 0; i < audio.size(); i++)
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

		/**
		  @brief Remaps the range of the values in a 1D vector from [inputStart,inputEnd] to [outputStart,outputEnd] 
		  @param vector
		  @param vectorSize
		  @param outputStart
		  @param outputEnd
		  @param inputStart
		  @param inputEnd
		 */
		template<class range>
		static inline void remap(std::vector<range>& vector,range outputStart,range outputEnd,range inputStart,range inputEnd)
		{
			double slope = 1.0f * (outputEnd - outputStart) / (inputEnd - inputStart);
			for (uint32_t i = 0; i < vector.size(); i++)
				vector[i] = outputStart + static_cast<range>(slope) * (vector[i] - inputStart);
		}

		/**
		  @brief Remaps the range of the values in a 1D vector from [inputStart,inputEnd] to [outputStart,outputEnd] 
		  @param vector
		  @param vectorSize
		  @param outputStart
		  @param outputEnd
		  @param inputStart
		  @param inputEnd
		 */
		template<class range>
		static inline void remap(range* vector, size_t vectorSize,range outputStart, range outputEnd, range inputStart, range inputEnd)
		{
			double slope = 1.0f * (outputEnd - outputStart) / (inputEnd - inputStart);
			for (uint32_t i = 0; i < vectorSize; i++)
				vector[i] = outputStart + static_cast<range>(slope) * (vector[i] - inputStart);
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

		/**
		  @brief Gets maximum element in a 2D Vector 
		  @param vector
		 */
		template<class sample>
		static inline sample getMax(const std::vector<std::vector<sample>>& vector)
		{
			AuxAssert(vector.size() > 0, "Row size should be greater than 0");
			AuxAssert(vector[0].size() > 0, "Columns size should be greater than 0");
			sample maxValue = vector[0][0];
			for (uint32_t i = 0; i < vector.size(); i++)
				for (uint32_t j = 0; j < vector[0].size(); j++)
					maxValue = maxValue < vector[i][j] ? vector[i][j] : maxValue;
			return maxValue;
		}

		/**
		   @brief Computes the min element in an std::vector
		   @param vector
		   @return 
		*/
		template<class sample>
		static inline sample getMin(const std::vector<sample>& vector)
		{
			AuxAssert(vector.size() > 0, "Vector size should be greater than 0");
			if (vector.size() == 1)
				return vector[0];
			sample minValue = vector[0];
			for (uint32_t i = 1; i < vector.size(); i++)
				minValue = minValue > vector[i] ? vector[i] : minValue;
			return minValue;
		}

		/**
		  @brief Gets minimum of a 2D Vector 
		  @param vector
		  @return 
		 */
		template<class sample>
		static inline sample getMin(const std::vector<std::vector<sample>>& vector)
		{
			AuxAssert(vector.size() > 0, "Row size should be greater than 0");
			AuxAssert(vector[0].size() > 0, "Columns size should be greater than 0");
			sample minValue = vector[0][0];
			for (uint32_t i = 0; i < vector.size(); i++)
				for (uint32_t j = 0; j < vector[0].size(); j++)
					minValue = minValue > vector[i][j] ? vector[i][j] : minValue;
			return minValue;
		}

		/**
		   @brief Rotate a 1d vector representing a 2D vector by 90 degrees (Clockwise)
		   @param vector
		*/
		template<class sample>
		static inline void rotateClockwiseBy90(std::vector<sample>& vector)
		{
			size_t rows = sqrt(vector.size());
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = i + 1; j < rows; ++j) 
					std::swap(vector[i * rows + j], vector[j * rows + i]);
		}


		/**
		   @brief Flatten a 2D vector to 1D
		   @param inputVector
		   @param rows
		   @param columns
		   @param output
		*/
		template<class data>
		static inline void flatten(float** inputVector, int rows, int columns, std::vector<float>& output)
		{
			AuxAssert(inputVector != nullptr, "Input Vector cannot be a nullptr");
			AuxAssert(rows > 0, "Rows has to be greater than zero");
			AuxAssert(columns > 0, "Columns has to be greater than zero");
			output.resize(rows * columns);
			AuxPort::CircularBufferEngine<data> circEngine;
			circEngine.attachPointer(output.data(), output.size());
			for (uint32_t i = 0;i < rows;i++)
				for (uint32_t j = 0;j < columns;j++)
					circEngine.push(inputVector[i][j]);
		}

		/**
		   @brief Transpose a 2D Vector
		   @param inputVector
		   @param rows
		   @param columns
		   @param output
		*/
		template<class data>
		static inline void transpose(data** inputVector, int rows, int columns, std::vector<std::vector<data>>& output)
		{
			AuxAssert(inputVector != nullptr, "Input Vector cannot be a nullptr");
			AuxAssert(rows > 0, "Rows has to be greater than zero");
			AuxAssert(columns > 0, "Columns has to be greater than zero");
			output.resize(columns);
			for (uint32_t i = 0;i < output.size();i++)
				output[i].resize(rows);
			for (uint32_t i = 0;i < columns;i++)
				for (uint32_t j = 0; j < rows;j++)
					output[i][j] = inputVector[j][i];
		}

		/**
		  @brief Transposes a 2D vector 
		  @param inputVector
		  @param rows
		  @param columns
		  @param output
		  \code{.cpp}
		  
		  \endcode 
		 */
		template<class data>
		static inline void transpose(const std::vector<std::vector<data>>& inputVector,std::vector<std::vector<data>>& output)
		{
			AuxAssert(inputVector.size() > 0, "Rows has to be greater than zero");
			AuxAssert(inputVector[0].size() > 0, "Columns has to be greater than zero");
			output.resize(inputVector[0].size());
			for (uint32_t i = 0; i < output.size(); i++)
				output[i].resize(inputVector.size();
			for (uint32_t i = 0; i < outputVector.size(); i++)
				for (uint32_t j = 0; j < outputVector[0].size(); j++)
					output[i][j] = inputVector[j][i];
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

		/**
		  @brief Creates an impulse [in-place] of size vector 
		  @param vector
		  @param numberOfSamples
		 */
		template<class sample>
		static inline void impulse(std::vector<sample>& vector, size_t numberOfSamples,uint32_t impulseIndex = 0)
		{
			AuxAssert(impulseIndex <= numberOfSamples, "Impulse index should not be greater than number of samples");
			vector.resize(numberOfSamples);
			std::fill(vector.begin(), vector.end(), 0.0f);
			vector[impulseIndex] = 1.0f;	
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

		/**
		  @brief Converts seconds to a Time String | Format : hour:min:seconds 
		  @param seconds
		  @return
		  @details 
		  Example Implementation
		  \code{.cpp}
			auto timeInString = convertToTime(300);
		  \endcode	
		 */
		static std::string convertToTime(uint32_t seconds)
		{
			auto secondsInFloat = static_cast<float>(seconds);
			float hours = floorf(secondsInFloat / 3600);
			float mins = floorf((secondsInFloat - (hours * 3600)) / 60);
			float secs = floorf(secondsInFloat - (hours*3600) - (mins*60));
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
				vector[i] = fabsf(vector[i]);
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


		/**
		  @brief Returns a string with index of the english alphabet mapped to its String
		  @param indexNumber
		  @return 
		  @details
		  Example : toAlphabet(3) would return a string holding the value = "C"
		 */
		static inline std::string toAlphabet(uint32_t indexNumber)
		{
			AuxAssert(indexNumber >= 0 && indexNumber <= 25,"English alphabet only consist of 26 letters last I checked");
			std::string letter;
			letter.push_back(static_cast<char>(65 + indexNumber));
			return letter;
		}

		static std::vector<std::string> splitIntoTokens(std::string string, const std::string& delimiter);
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
	/// @brief Provides funnctions to get Information about your device
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

#if AUXSIMD
			Env::supportsMMX() == true ? AuxPort::Logger::Log("MMX is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("MMX is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsAVX() == true ? AuxPort::Logger::Log("AVX is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("AVX is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE() == true ? AuxPort::Logger::Log("SSE is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE2() == true ? AuxPort::Logger::Log("SSE2 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE2 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE4_1() == true ? AuxPort::Logger::Log("SSE4.1 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE4.1 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsSSE4_2() == true ? AuxPort::Logger::Log("SSE4.2 is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("SSE4.2 is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
			Env::supportsNeon() == true ? AuxPort::Logger::Log("Neon is Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple) : AuxPort::Logger::Log("Neon is not Supported", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);

#else
			AuxPort::Logger::Log("SIMD is not enabled",AuxPort::LogType::Warning,AuxPort::ColourType::Yellow);
#endif
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

	

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief Consist of Matrix Manipulation and Data Management operations
	///////////////////////////////////////////////////////////////////////////////////////
	namespace DataProcessing
	{
		class DataUtility
		{
		public:
		   /**
			   @brief Convert 2D String to Float Vector 
			   @param inputData 
			   @param outputData 
		   **/
			static void convertToFloat(const std::vector<std::vector<std::string>>& inputData, std::vector<std::vector<float>>& outputData);
			
		   /**
			   @brief  Reshapes the 2D m*n to r*c vector 
			   @tparam data       - uint32,int32,float,double,uint8_t,std::string,bool
			   @param  inputData  - 
			   @param  outputData - 
			   @param  rows       - 
			   @param  cols       - 
		   **/
			template<class data>
			static void reshape(const std::vector<std::vector<data>>& inputData, std::vector<std::vector<data>>& outputData, int32_t rows, int32_t cols) //!< 
			{
				AuxAssert(rows * cols == inputData.size() * inputData[0].size(), "New Reshape Dimensions are not compatible");
				int indexRow = 0;
				int indexColumn = 0;
				outputData.resize(rows);
				for (uint32_t i = 0;i < outputData.size();i++)
					outputData[i].resize(cols);
				for (uint32_t i = 0;i < inputData.size();i++)
				{
					for (uint32_t j = 0;j < inputData[0].size();j++)
					{
						outputData[indexRow][indexColumn++] = inputData[i][j];
						indexColumn = indexColumn == cols ? 0 : indexColumn;
						indexRow = indexColumn == 0 ? indexRow + 1 : indexRow;
					}
				}
			}
		};
	}
}
#endif

