#ifndef AUXPORT_STRING_H
#define AUXPORT_STRING_H
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

#include<cmath>
#include<cstring>
#include "../Log/AuxLog.h"
#include "../Utility/AuxCaster.h"
namespace AuxPort
{

	///////////////////////////////////////////////////////////////////////////////////////	
	/// @brief Abstraction over C-Style Strings for ease of use.
	/// 
	/// Example : 
	/// @code AuxPort::String string = "Hello There"; @endcode
	///////////////////////////////////////////////////////////////////////////////////////
	class String : public ILog, ICasters, Casters
	{
	public:

		///////////////////////////////////////////////////////////////////////////////////////	
		/// @brief Creates an empty String object
		///////////////////////////////////////////////////////////////////////////////////////
		String();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Initializes a String object with a character.
		///////////////////////////////////////////////////////////////////////////////////////
		String(char character);

#ifdef AUXPORT_64
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Initializes a String object with a integer.
		///////////////////////////////////////////////////////////////////////////////////////	
		String(const uint64& string);
#else
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Initializes a String object with a integer.
		///////////////////////////////////////////////////////////////////////////////////////
		String(const uint32& string);
#endif

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Initializes a String object with a C-Style String.
		///////////////////////////////////////////////////////////////////////////////////////
		String(char* string);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Initializes a String object with a constant C-Style String.
		///////////////////////////////////////////////////////////////////////////////////////
		String(const char* string);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Intializes a String with another const String Object.
		///////////////////////////////////////////////////////////////////////////////////////
		String(const String& string);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Intializes a String with a String Object.
		///////////////////////////////////////////////////////////////////////////////////////
		String(String& string);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Intializes a String with a std::string Object.
		///////////////////////////////////////////////////////////////////////////////////////
		String(const std::string& string);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Intializes a String with a std::string Object.
		///////////////////////////////////////////////////////////////////////////////////////
		String(std::string& string);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Default Destructor.
		/// Safely Deallocates memory before destroying the String object.
		///////////////////////////////////////////////////////////////////////////////////////
		~String();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns Length of String.
		///////////////////////////////////////////////////////////////////////////////////////
		size_t length() const;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Checks whether the String is Empty or not
		///////////////////////////////////////////////////////////////////////////////////////
		bool Empty() const;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String object to a C-Style String and returns it.
		///////////////////////////////////////////////////////////////////////////////////////
		char* getCString() const;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the first character in the string
		char getFirstCharacter() const;
		///////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the Assignment Operator. 
		/// 
		/// You can assign/initialize a String like:
		/// @code String string = "Hello There" @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		void operator = (const String& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the Assignment Operator.
		/// 
		/// You can assign/initialize a String like:
		/// @code String string = "Hello There" @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		void operator = (const char* c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the Assignment Operator. 
		/// 
		/// You can assign/initialize a String like:
		/// @code String string = "Hello There" @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		void operator = (const std::string& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded + operator for String Concatenation with a const C-Style String
		///////////////////////////////////////////////////////////////////////////////////////
		String operator + (const char* c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded + operator for String Concatenation with a const C-Style String
		///////////////////////////////////////////////////////////////////////////////////////
		String operator + (const String& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded + operator for String Concatenation with a const C-Style String
		///////////////////////////////////////////////////////////////////////////////////////
		String operator + (const std::string& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the += Operator.
		///
		/// You can add a character to the end of the string.
		/// @code 
		/// String str='a';
		/// str+='b'; 
		/// @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		String* operator += (const char& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the += Operator.
		///
		/// You can concatenate a C-Style String to the end of the string.
		/// @code
		/// String string="Hello";
		/// string+=" World";
		/// @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		String* operator += (const char* c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the += Operator.
		///
		/// You can concatenate a std::string to the end of the string.
		/// @code 
		/// String str="Hello";
		/// std::string str2=" World";
		/// str += str2;
		/// @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		String* operator += (const std::string& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded the += Operator.
		/// 
		/// You can concatenate a AuxPort::String to the end of the string.
		/// @code
		/// String str="Hello";
		/// String str2=" World";
		/// str += str2;
		/// @endcode
		///////////////////////////////////////////////////////////////////////////////////////
		String* operator += (const String& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded << operator to allow console printing of String object using ostream	 
		///////////////////////////////////////////////////////////////////////////////////////
		friend std::ostream& operator << (std::ostream& out, const String& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overloaded >> operator to allow console printing of String object using ostream
		///////////////////////////////////////////////////////////////////////////////////////
		friend std::ostream& operator << (std::ostream& out, String* c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Searches for all instance of a character in a String and replaces it with the character provided.
		///////////////////////////////////////////////////////////////////////////////////////
		void replaceCharacter(const char characterToReplace, const char replacementCharacter);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Concatenates a character to the end of String
		///////////////////////////////////////////////////////////////////////////////////////
		void pushBack(const char c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Concatenates a C-Style String to the end of String
		///////////////////////////////////////////////////////////////////////////////////////
		void pushBack(const char* c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Concatenates a String object to the end of String
		///////////////////////////////////////////////////////////////////////////////////////
		void pushBack(const String& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Concatenates an std::String to the end of String
		///////////////////////////////////////////////////////////////////////////////////////
		void pushBack(const std::string& c);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns the Substring in a String.
		///////////////////////////////////////////////////////////////////////////////////////
		String substring(const uint32& start = 0, const uint32& end = 1) const;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Overrides the Logging Module to Handle String Object Logging
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Allows you to substract two AuxPort::Strings and get the resulted "Difference" as an AuxPort::String;
		///////////////////////////////////////////////////////////////////////////////////////
		static String subtract(String& string1, String& string2);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Allows you to substract two std::strings and get the resulted "Difference" as a std::string;
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string subtract(std::string string1, std::string string2);

#ifdef AUXPORT_64
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into a signed 64-bit Integer (Only handles Numerical Strings)
		/// 
		/// Example : @code String string = "123423"; @endcode
		/// This can be cast into an signed 64 bit Integer.
		///////////////////////////////////////////////////////////////////////////////////////
		int64 toInt64() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into an unsigned 64-bit Integer (Only handles Numerical Strings)
		/// 
		/// Example : @code String string = "123423"; @endcode
		/// This can be cast into an Unsigned 64 bit Integer.
		///////////////////////////////////////////////////////////////////////////////////////
		uint64 toUInt64() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into a signed 32-bit Integer (Only handles Numerical Strings)
		/// 
		/// Example : @code String string = "123423"; @endcode
		/// This can be cast into an signed 32 bit Integer.
		///////////////////////////////////////////////////////////////////////////////////////
		int32 toInt32() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into a unsigned 32-bit Integer (Only handles Numerical Strings)
		/// 
		/// Example : @code String string = "123423"; @endcode
		/// This can be cast into an signed Unsigned 32-bit Integer.
		///////////////////////////////////////////////////////////////////////////////////////
		uint32 toUInt32() override;
#else
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into a signed 32-bit Integer (Only handles Numerical Strings)
		/// 
		/// Example : @code String string = "123423"; @endcode
		/// This can be cast into an signed 32 bit Integer.
		///////////////////////////////////////////////////////////////////////////////////////
		int32 toInt32() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into a unsigned 32-bit Integer (Only handles Numerical Strings)
		/// 
		/// Example : @code String string = "123423"; @endcode
		/// This can be cast into an signed Unsigned 32-bit Integer.
		///////////////////////////////////////////////////////////////////////////////////////
		uint32 toUInt32() override;

#endif // AUXPORT_64

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String object to std::string
		///////////////////////////////////////////////////////////////////////////////////////
		std::string toStdString() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Casts the String into a double  (Only handles Numerical Strings)
		///////////////////////////////////////////////////////////////////////////////////////
		double toDouble() override;

	private:
		char* _string;
		size_t  _length;
	};
}
#endif
