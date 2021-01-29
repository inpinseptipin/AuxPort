/*
*			AuxPort Library
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
#include "AuxPort_StringObjectArray.h"
namespace AuxPort
{
	StringObjectArray::StringObjectArray(const std::string& key, std::string values[])
	{
		_key = key;
		size_t length = sizeof * values / sizeof values;
		_values.reserve(length);
		for (int i = 0; i < length; i++)
		{
			_values.emplace_back(values[i]);
		}
	}

	StringObjectArray::StringObjectArray(const std::string& key, const std::vector<std::string>& values)
	{
		_key = key;
		_values.insert(_values.end(), values.begin(), values.end());
	}

	StringObjectArray::StringObjectArray(const std::string& key, const std::string& values)
	{
		_key = key;
		_values.emplace_back(values);
	}

	std::string& StringObjectArray::key()
	{
		return _key;
	}

	std::vector<std::string>& StringObjectArray::values()
	{
		return _values;
	}

	std::ostream& operator << (std::ostream& out, StringObjectArray& sObject)
	{
		out << sObject.key()<<":";
		for (int i = 0; i < sObject._values.size(); i++)
		{
			if (i == sObject._values.size() - 1)
			{
				out << sObject._values[i];
			}
			else
			{
				out << sObject._values[i] << ",";
			}
		}
		return out;
	}

	void StringObjectArray::Log()
	{
		setColour(ColourType::Blue);
		std::cout << *this << std::endl;
		setColour(ColourType::White);
	}
}