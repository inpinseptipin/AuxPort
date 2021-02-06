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
#include "../Log/AuxPort_Log.h"
#include "../Utility/AuxPort_Caster.h"
namespace AuxPort
{
/*
		String Class, Abstraction over C-Style Strings for ease of use.
		For Example : AuxPort::String string = "Hello There";
*/
	class String : public ILog,ICasters
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
		char* getCString()
		Returns a Cstyle String.
*/
		char* getCString();

/*===================================================================================*/

/*
		void operator =(String& c)
		Overloaded the Assignment Operator. You can assign/initialize a String like:
		String string = "Hello There"
*/
		void operator = (String& c);

/*===================================================================================*/
/*
		void operator +(const char& c)
		Overloaded the + Operator, you can add a character to the end of the string. 
*/
		String* operator += (const char &c);

/*===================================================================================*/
/*
		void operator +(const char& c)
		Overloaded the + Operator, you can add a character to the end of the string. 
*/

/*===================================================================================*/
/*
		friend std::ostream& operator << (std::ostream& out, const String& c)
		 
*/
		friend std::ostream& operator << (std::ostream& out, const String& c);

/*===================================================================================*/
/*
		friend std::ostream& operator << (std::ostream& out, String* c)
*/
		friend std::ostream& operator << (std::ostream& out, String* c);

/*===================================================================================*/

		
		
		//friend std::istream& operator >> (std::istream& in, const String& c);
/*===================================================================================*/
/*
		void replaceCharacter(const char characterToReplace, const char replacementCharacter)
*/
		void replaceCharacter(const char characterToReplace, const char replacementCharacter);

/*===================================================================================*/
/*
		void pushBack(const char c)
*/
		void pushBack(const char c);
		
/*===================================================================================*/
/*
		void Log() override;
*/
		void Log() override;
/*===================================================================================*/
		
		int64 toInt64() override { return 0; }

/*===================================================================================*/
		
		std::string toStdString() override;
		
/*===================================================================================*/

		uint64 toUInt64() override { return 0; }
/*===================================================================================*/

	private:
		char* _string;
		uint64  _length;
/*===================================================================================*/

		char intToAscii(int value);
/*===================================================================================*/

		int32 toInt32() override { return 0; }
		uint32 toUInt32() override { return 0; }

	};
}
#endif