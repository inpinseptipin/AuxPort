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
#include "AuxString.h"
#include "../Utility/AuxUtility.h"
#include <assert.h>

namespace AuxPort
{
/*===================================================================================*/
	char* String::getCString() const
	{
		return _string;
	}

	char String::getFirstCharacter() const
	{
		AuxAssert(!Empty(), "The String is empty, it does not contain any characters");
		return _string[0];
	}
/*===================================================================================*/
	String::String()
	{
		_length = 0;
		_string = nullptr;
	}
/*===================================================================================*/
	String::String(char character)
	{
		_length = 1;
		_string = new char[_length + 1];
		_string[0] = character;
		_string[1] = '\0';
	}
/*===================================================================================*/
#ifdef AUXPORT_64
	String::String(const uint64_t& string)
	{
		uint64_t number = string;
		_length = AuxPort::Utility::numberOfDigits(string);
		_string = new char[_length + 1];
		int32_t i = 0;
		while (number)
		{
			_string[i++] = AuxPort::Casters::toChar(number % 10);
			number /= 10;
		}
		_string[_length] = '\0';
	}
#else
	String::String(const uint32_t& string)
	{
		uint32_t number = string;
		_length = AuxPort::Utility::numberOfDigits(string);
		_string = new char[_length + 1];
		int32_t i = 0;
		while (number)
		{
			_string[i++] = AuxPort::Casters::toChar(number % 10);
			number /= 10;
		}
		_string[_length] = '\0';
	}
#endif // _WIN64

	
/*===================================================================================*/
	String::String(char* string)
	{
		_length = strlen(string);
		_string = new char[_length+1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = string[i];
		_string[_length] = '\0';
	}
/*===================================================================================*/
	String::String(const char* string)
	{
		_length = strlen(string);
		_string = new char[_length+1]; 
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = string[i];
		_string[_length] = '\0';
	}
/*===================================================================================*/
	String::String(const String& string)
	{
		_length = string._length;
		_string = new char[_length+1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = string._string[i];
		_string[_length] = '\0';
	}
/*===================================================================================*/
	String::String(String& string)
	{
		_length = string._length;
		_string = new char[_length+1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = string._string[i];
		_string[_length] = '\0';
	}

	String::String(const std::string& string)
	{
		_length = string.length();
		_string = new char[_length + 1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = string[i];
		_string[_length] = '\0';
	}

	String::String(std::string& string)
	{
		_length = string.length();
		_string = new char[_length + 1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = string[i];
		_string[_length] = '\0';
	}
/*===================================================================================*/
	String::~String()
	{
		if (_string != nullptr)
		{
			delete[] _string;
		}
		_length = 0;
	}
/*===================================================================================*/
	size_t String::length() const
	{
		return _length;
	}
/*===================================================================================*/
	bool String::Empty() const
	{
		return _length == 0 ? true : false; 
	}
/*===================================================================================*/
	void String::operator = (const String& c)
	{
		if (_length == 0)
		{
			_length = c._length;
			_string = new char[_length];
			for (uint32_t i = 0; i < _length; i++)
				_string[i] = c._string[i];
		}
		else
		{
			delete[] _string;
			_length = c._length;
			_string = new char[_length];
			for (uint32_t i = 0; i < _length; i++)
				_string[i] = c._string[i];
			
		}
	}
/*===================================================================================*/
	void String::operator = (const char* c)
	{
		this->pushBack(c);
	}

	void String::operator = (const std::string& c)
	{
		this->pushBack(c);
	}
/*===================================================================================*/
	std::ostream& operator << (std::ostream& out, const String& c)
	{
		for (uint32_t i = 0; i < c._length; i++)
			out << c._string[i];
		
		return out;
	}
/*===================================================================================*/
	std::ostream& operator << (std::ostream& out, String* c)
	{
		for (uint32_t i = 0; i < c->length(); i++)
			out << c->_string[i];
		
		return out;
	}
/*===================================================================================*/
	void String::replaceCharacter(const char CharacterToReplace, const char replacementCharacter)
	{
		for (uint32_t i = 0; i < _length; i++)
		{
			if (_string[i] == CharacterToReplace)
				_string[i] = replacementCharacter;
		}
	}
/*===================================================================================*/
	void String::pushBack(const char c)
	{
		char* temp = new char[_length];
		for (uint32_t i = 0; i < _length; i++)
			temp[i] = _string[i];
		
		delete[] _string;
		_string = new char[_length + 2];
		for (size_t i = 0; i < _length; i++)
			_string[i] = temp[i];
		
		_string[_length++] = c;
		_string[_length] = '\0';
		delete[] temp;
	}
/*===================================================================================*/
	void String::pushBack(const char* c)
	{
		uint32_t length=uint32_t(strlen(c));
		char* temp = new char[_length];
		for (uint32_t i = 0; i < _length; i++)
			temp[i] = _string[i];
		
		delete[] _string;
		_string = new char[_length+length+1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = temp[i];
		
		for(uint32_t i = 0; i<length;i++)
			_string[_length+i]=c[i];

		_length+=length;
		_string[_length] = '\0';

		delete[] temp;
	}
/*===================================================================================*/
	void String::pushBack(const String& c)
	{
		uint32_t length= uint32_t(c._length);
		char* temp = new char[_length];
		for(uint32_t i=0;i<_length;i++)
			temp[i]=_string[i];

		delete[] _string;

		_string = new char[_length+length+1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = temp[i];
		
		for(uint32_t i = 0; i<length;i++)
			_string[_length+i]=c._string[i];

		_length+=length;
		_string[_length]='\0';
		delete[] temp;

	}

	void String::pushBack(const std::string& c)
	{
		size_t length = c.size();
		char* temp = new char[_length];
		for (uint32_t i = 0; i < _length; i++)
			temp[i] = _string[i];

		delete[] _string;

		_string = new char[_length + length + 1];
		for (uint32_t i = 0; i < _length; i++)
			_string[i] = temp[i];

		for (uint32_t i = 0; i < length; i++)
			_string[_length + i] = c[i];

		_length += length;
		_string[_length] = '\0';
		delete[] temp;
	}
/*===================================================================================*/
	void String::Log()
	{
		setColour(AuxPort::ColourType::Blue);
		std::cout << this << std::endl;
		setColour(AuxPort::ColourType::White);
	}

	std::string String::subtract(std::string string1, std::string string2)
	{
		std::string newString;

		if (string1.length() > string2.length())
		{
			for (size_t i = string2.length() + 1; i < string1.length(); i++)
				newString.push_back(string1[i]);
		}
		else
			for (size_t i = string1.length(); i < string2.length(); i++)
				newString.push_back(string2[i]);
		return newString;
	}

	String String::subtract(String& string1, String& string2)
	{
		return String();
	}
/*===================================================================================*/
	String String::operator + (const char* c)
	{
		String string;
		string.pushBack(*this);
		string.pushBack(c);
		return string;

	}
/*===================================================================================*/
	String String::operator + (const String& c)
	{
		String string;
		string.pushBack(*this);
		string.pushBack(c);
		return string;
	}

	String String::operator+(const std::string& c)
	{
		String string;
		string.pushBack(*this);
		string.pushBack(c);
		return string;
	}
/*===================================================================================*/
	String* String::operator+=(const char& c)
	{
		this->pushBack(c);
		return this;
	}
/*===================================================================================*/
	String* String::operator+=(const char* c)
	{
		this->pushBack(c);
		return this;
	}

	String* String::operator+=(const std::string& c)
	{
		this->pushBack(c);
		return this;
	}

	String* String::operator+=(const String& c)
	{
		this->pushBack(c);
		return this;
	}
/*===================================================================================*/
	std::string String::toStdString()
	{
		return std::string(this->getCString());
	}
/*===================================================================================*/

	String String::substring(uint32_t start, uint32_t end) const
	{
		String x = "Hello";
		return x;
	}

/*===================================================================================*/

#ifdef AUXPORT_64
	int64_t String::toInt64()
	{
		double power = 0;
		int64_t Number = 0;
		if (_string[0] == '-')
		{
			for (uint32_t i = uint32_t(_length - 1); i > 0; i--)
			{
				if (_string[i] >= 48 || _string[i] <= 57)
				{
					Number += Casters::toInt(_string[i]) * int64_t(pow(10, power++));
				}
			}
			return Number * -1;
		}
		else
		{
			for (int32_t i = int32_t(_length - 1); i >= 0; i--)
			{
				if (_string[i] >= 48 || _string[i] <= 57)
				{
					Number += Casters::toInt(_string[i]) * int64_t(pow(10, power++));
				}
			}
			return Number;
		}
	}
	/*===================================================================================*/
	uint64_t String::toUInt64()
	{
		double power = 0;
		uint64_t Number = 0;
		for (int32_t i = int32_t(_length - 1); i >= 0; i--)
		{
			if (_string[i] >= 48 || _string[i] <= 57)
			{
				Number += Casters::toInt(_string[i]) * int64_t(pow(10, power++));
			}
		}
		return Number;
	}

	int32_t String::toInt32()
	{
		double power = 0;
		int32_t Number = 0;
		if (_string[0] == '-')
		{
			for (uint32_t i = uint32_t(_length - 1); i > 0; i--)
			{
				if (_string[i] >= 48 || _string[i] <= 57)
				{
					Number += int32_t(Casters::toInt(_string[i])) * int32_t(pow(10, power++));
				}
			}
			return Number * -1;
		}
		else
		{
			for (int32_t i = int32_t(_length - 1); i >= 0; i--)
			{
				if (_string[i] >= 48 || _string[i] <= 57)
				{
					Number += int32_t(Casters::toInt(_string[i]) * int32_t(pow(10, power++)));
				}
			}
			return Number;
		}
	}
	/*===================================================================================*/
	uint32_t String::toUInt32()
	{
		double power = 0;
		uint32_t Number = 0;
		for (int32_t i = int32_t(_length - 1); i >= 0; i--)
		{
			if (_string[i] >= 48 || _string[i] <= 57)
			{
				Number += uint32_t(Casters::toInt(_string[i])) * uint32_t(pow(10, power++));
			}
		}
		return Number;
	}


#else
	int32_t String::toInt32()
	{
		double power = 0;
		int32_t Number = 0;
		if (_string[0] == '-')
		{
			for (uint32_t i = uint32_t(_length - 1); i > 0; i--)
			{
				if (_string[i] >= 48 || _string[i] <= 57)
				{
					Number += Casters::toInt(_string[i]) * int32_t(pow(10, power++));
				}
			}
			return Number * -1;
		}
		else
		{
			for (int32_t i = int32_t(_length - 1); i >= 0; i--)
			{
				if (_string[i] >= 48 || _string[i] <= 57)
				{
					Number += Casters::toInt(_string[i]) * int32_t(pow(10, power++));
				}
			}
			return Number;
		}
	}
	/*===================================================================================*/
	uint32_t String::toUInt32() 
	{
		double power = 0;
		uint32_t Number = 0;
		for (int32_t i = int32_t(_length - 1); i >= 0; i--)
		{
			if (_string[i] >= 48 || _string[i] <= 57)
			{
				Number += Casters::toInt(_string[i]) * int32_t(pow(10, power++));
			}
		}
		return Number;
	}
#endif // 


/*===================================================================================*/
	double String::toDouble()
	{
		return Casters::toDouble(this->getCString());
	}
}
