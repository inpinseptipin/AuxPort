/*
*			AuxPort Library
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
#include "AuxStringPair.h"

namespace AuxPort
{
	StringPair::StringPair(const std::string& key, const std::string& value)
	{
		key.empty() ? _key = "null_key" : _key = key;
		value.empty() ? _value = "null_value" : _value = value;
	}

	StringPair::StringPair(const String& key, const String& value)
	{
		_key = key;
		_value = value;

	}

	StringPair::StringPair(const char* key, const char* value)
	{
		if (key == nullptr)
			_key = "null_key";
		else
			_key = key;

		if (value == nullptr)
			_value = "null_value";
		else
			_value = value;
	}

	AuxPort::String StringPair::key() const 
	{
		return _key;
	}

	AuxPort::String StringPair::value() const
	{
		return _value;
	}

	void StringPair::setKey(const String& key)
	{
		_key = key;
	}

	void StringPair::setValue(const String& value)
	{
		_value = value;
	}

	std::ostream& operator << (std::ostream& out, const StringPair& sPair)
	{
		out << sPair._key << " : " << sPair._value;
		return out;
	}

	void StringPair::Log()
	{
		setColour(ColourType::Blue);
		std::cout << *this << std::endl;
		setColour(ColourType::White);
	}

	/*===================================================================================*/
}