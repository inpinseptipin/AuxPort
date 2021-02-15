#ifndef STRING_H
#define STRING_H
/*
			AuxPort Library
			"Generic Modules to facilitate C++ Windows Application development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2020, Satyarth Arora
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
#pragma once
#include<cmath>
#include<cstring>
#include "../Log/AuxPort_Log.h"
#include "../Utility/AuxPort_Caster.h"
namespace AuxPort
{
/*
		String Class, Abstraction over C-Style Strings for ease of use.
		For Example : AuxPort::String string = "Hello There";
*/
	class String : public ILog,ICasters,Casters
	{
	public:
/*===================================================================================*/	
/*
		Creates an empty String object
*/
		String();
/*===================================================================================*/

/* 
		Initializes a String object with a C-Style String.
*/
		String(char* string);

/*===================================================================================*/
/*
		Initializes a String object with a constant C-Style String.
*/
		String(const char* string);

/*===================================================================================*/

/*
		Intializes a String with another const String Object.
*/
		String(const String& string);

/*===================================================================================*/

/*
		Default Destructor
		Safely Deallocates memory before destroying the String object.
*/
		~String();

/*===================================================================================*/

/*
		Returns Length of String.
*/
		uint64 length();

/*===================================================================================*/

/*
		Checks whether the String is Empty or not
*/
		bool Empty();


/*===================================================================================*/

/*
		
		Casts the String object to a C-Style String and returns it.
*/
		char* getCString();

/*===================================================================================*/

/*
		Overloaded the Assignment Operator. You can assign/initialize a String like:
		String string = "Hello There"
*/
		void operator = (String& c);

/*===================================================================================*/

/*
		Overloaded the Assignment Operator. You can assign/initialize a String like:
		String string = "Hello There"
*/
		void operator = (const char* c);

/*===================================================================================*/
/*
		Overloaded the += Operator, you can add a character to the end of the string.
		String string +='a';
*/
		String* operator += (const char &c);

/*===================================================================================*/
/*
		
		Overloaded the += Operator, you can concatenate a C-Style String to the end of the string.
		String string="Hello";
		string+=" World";
*/
		String* operator += (const char* c);



/*===================================================================================*/
/*
		Overloaded << operator to allow console printing of String object using ostream	 
*/
		friend std::ostream& operator << (std::ostream& out, const String& c);

/*===================================================================================*/
/*
		Overloaded >> operator to allow console printing of String object using ostream
*/
		friend std::ostream& operator << (std::ostream& out, String* c);


/*===================================================================================*/
/*
		Searches for all instance of a character in a String and replaces it with the character provided.
*/
		void replaceCharacter(const char characterToReplace, const char replacementCharacter);

/*===================================================================================*/
/*
		Concatenates a character to the end of String
*/
		void pushBack(const char c);

/*===================================================================================*/
/*
		Concatenates a C-Style String to the end of String
*/
		void pushBack(const char* c);

/*===================================================================================*/
/*
		Overrides the Logging Module to Handle String Object Logging
*/
		void Log() override;
/*===================================================================================*/
/*
		Casts the String into a signed 64-bit Integer {Only handles Numerical Strings}
		Example : String string = "123423";
		This can be cast into an signed 64 bit Integer.
*/
		int64 toInt64() override;

/*===================================================================================*/
/*
		Casts the String object to std::string
*/
		std::string toStdString() override;
		
/*===================================================================================*/
/*
		Casts the String into an unsigned 64-bit Integer
*/
		uint64 toUInt64() override { return 0; }
/*===================================================================================*/

	private:
		char* _string;
		uint64  _length;


/*===================================================================================*/

		int32 toInt32() override { return 0; }
		uint32 toUInt32() override { return 0; }

	};
}
#endif