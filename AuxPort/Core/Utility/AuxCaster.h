#ifndef AUXPORT_CASTER_H
#define AUXPORT_CASTER_H
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

#include <math.h>
#include <ctype.h>
#include "../Env/AuxEnv.h"
#ifndef AUXPORT_UTILITY_H
#include "../Utility/AuxUtility.h"
#endif
namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief ICasters is an abstract class that provides pure virtual interfaces to cast data
	/// from one type to another
	///////////////////////////////////////////////////////////////////////////////////////
	class ICasters
	{
	public:
#ifdef AUXPORT_64
		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief This function can be implemented by your Class/Type to cast it to an int32 integer.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual int32 toInt32() = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief This function can be implemented by your Class/Type to cast it to an unsigned int32 integer.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual uint32 toUInt32() = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function can be implemented by your Class/Type to cast it to an int64 integer.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual int64 toInt64() = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief This function can be implemented by your Class/Type to cast it to an unsigned int64 integer.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual uint64 toUInt64() = 0;
#else
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function can be implemented by your Class/Type to cast it to an int32 integer.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual int32 toInt32() = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function can be implemented by your Class/Type to cast it to an unsigned int32 integer.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual uint32 toUInt32() = 0;
#endif
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function can be implemented by your Class/Type to cast it to a std::string.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual std::string toStdString() = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function can be implemented by your Class/Type to cast it to Double.
		///////////////////////////////////////////////////////////////////////////////////////
		virtual double toDouble() = 0;
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides functions to cast data from one type to another
	///////////////////////////////////////////////////////////////////////////////////////
	class Casters
	{
	public:
#ifdef AUXPORT_64

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a numerical char to int64.
		///////////////////////////////////////////////////////////////////////////////////////
		static int64 toInt(char value) { return value >= 48 && value <= 57 ? int64(value) - 48 : -1; };

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief This casts a int64 to char.
		///////////////////////////////////////////////////////////////////////////////////////
		static char toChar(int64 value) { return value <= 9 ? char(48 + value) : char(0); };

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief This casts a unsigned int64 to a std::string
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string toStdString(uint64 number)
		{
			std::string stringNumber;
			stringNumber.resize(AuxPort::Utility::numberOfDigits(number));
			uint64 digit;
			size_t i = stringNumber.size() - 1;
			while (number)
			{
				digit = number % 10;
				stringNumber[i--] = (AuxPort::Casters::toChar((digit)));
				number /= 10;
			}
			return stringNumber;
		}

#else
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a unsigned int32 to a std::string
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string toStdString(uint32 number)
		{
			std::string stringNumber;
			stringNumber.resize(AuxPort::Utility::numberOfDigits(number));
			uint32 digit;
			int i = stringNumber.size() - 1;
			while (number)
			{
				digit = number % 10;
				stringNumber[i--] = (AuxPort::Casters::toChar((digit)));
				number /= 10;
			}
			return stringNumber;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a double to a std::string
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string toStdString(double number)
		{
			return std::to_string(number);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a long long to a std::string
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string toStdString(long long number)
		{
			return std::to_string(number);
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a numerical char to int32.
		///////////////////////////////////////////////////////////////////////////////////////
		static int32 toInt(char value) { return value >= 48 && value <= 57 ? int32(value) - 48 : -1; };

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a int32 to char.
		///////////////////////////////////////////////////////////////////////////////////////
		static char toChar(int32 value) { return value <= 9 ? char(48 + value) : char(0); };
#endif

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a string to Double.
		///////////////////////////////////////////////////////////////////////////////////////
		static double toDouble(const std::string& value)
		{
			try
			{
				return std::stod(value);
			}
			catch (std::invalid_argument invalidArgumentException)
			{
				AuxAssert(false, "String passed does not contain a valid rational number!");
			}
			return 0.0;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a string to a double-precision float
		///////////////////////////////////////////////////////////////////////////////////////
		static long double toLongDouble(const std::string& value)
		{
			try
			{
				return std::stold(value);
			}
			catch (std::invalid_argument invalidArgumentException)
			{
				AuxAssert(false, "String passed does not contain a valid rational number!");
			}
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This casts a std::string to a float.
		///////////////////////////////////////////////////////////////////////////////////////
		static float toFloat(const std::string& value)
		{
			try
			{
				return std::stof(value);
			}
			catch (std::invalid_argument invalidArgumentException)
			{
				AuxAssert(false, "String passed does not contain a valid rational number!");
			}
		}
	};
}
#endif 




