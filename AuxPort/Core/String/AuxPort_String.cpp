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
#include "AuxPort_String.h"

namespace AuxPort
{


	int64 String::toInt64()
	{
		double power=0;
		int64 Number=0;
		for(int i=_length-1;i>=0;i--)
		{
			if(_string[i]>=48 || _string[i]<=57)
			{
				Number+= charToInt(_string[i]) * pow(10,power++);
			}
		}
		return Number;
	}

	char* String::getCString()
	{
		return _string;
	}

	String::String()
	{
		_length = 0;
		_string = nullptr;
	}

	String::String(char* string)
	{
		_length = strlen(string);
		_string = new char[_length+1];
		for (int i = 0; i < _length; i++)
			_string[i] = string[i];
		_string[_length] = '\0';
	}

	String::String(const char* string)
	{
		_length = strlen(string);
		_string = new char[_length+1]; 
		for (int i = 0; i < _length; i++)
			_string[i] = string[i];
		_string[_length] = '\0';
	}

	String::String(const String& string)
	{
		_length = string._length;
		_string = new char[_length+1];
		for (int i = 0; i < _length; i++)
			_string[i] = string._string[i];
		_string[_length] = '\0';
	}

	String::~String()
	{
		delete[] _string;
		_length = 0;
	}

	uint64 String::length()
	{
		return _length;
	}

	bool String::Empty()
	{
		return _length == 0 ? true : false; 
	}

	void String::operator = (String& c)
	{
		if (_length == 0)
		{
			_length = c._length;
			_string = new char[_length];
			for (int i = 0; i < _length; i++)
				_string[i] = c._string[i];
		}
		else
		{
			delete[] _string;
			_length = c._length;
			_string = new char[_length];
			for (int i = 0; i < _length; i++)
				_string[i] = c._string[i];
			
		}
	}

	std::ostream& operator << (std::ostream& out, const String& c)
	{
		for (int i = 0; i < c._length; i++)
			out << c._string[i];
		
		return out;
	}

	std::ostream& operator << (std::ostream& out, String* c)
	{
		for (int i = 0; i < c->length(); i++)
			out << c->_string[i];
		
		return out;
	}

	void String::replaceCharacter(const char CharacterToReplace, const char replacementCharacter)
	{
		for (int i = 0; i < _length; i++)
		{
			if (_string[i] == CharacterToReplace)
				_string[i] = replacementCharacter;
		}
	}

	void String::pushBack(const char c)
	{
		char* temp = new char[_length];
		for (int i = 0; i < _length; i++)
			temp[i] = _string[i];
		
		delete[] _string;
		_string = new char[_length + 2];
		for (int i = 0; i < _length; i++)
			_string[i] = temp[i];
		
		_string[_length++] = c;
		_string[_length] = '\0';
		delete[] temp;
	}

	void String::pushBack(const char* c)
	{
		uint32 length=strlen(c);
		char* temp = new char[_length];
		for (int i = 0; i < _length; i++)
			temp[i] = _string[i];
		
		delete[] _string;
		_string = new char[_length+length+1];
		for (int i = 0; i < _length; i++)
			_string[i] = temp[i];
		
		for(int i = 0; i<length;i++)
			_string[_length+i]=c[i];

		_length+=length;
		_string[_length] = '\0';

		delete[] temp;
	}

	

	void String::Log()
	{
		setColour(AuxPort::ColourType::Blue);
		std::cout << this << std::endl;
		setColour(AuxPort::ColourType::White);
	}

	String* String::operator+=(const char& c)
	{
		this->pushBack(c);
		return this;
	}

	String* String::operator+=(const char* c)
	{
		this->pushBack(c);
		return this;
	}

	std::string String::toStdString()
	{
		return std::string(this->getCString());
	}

}