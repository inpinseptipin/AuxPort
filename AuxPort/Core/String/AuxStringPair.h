#ifndef AUXPORT_STRINGPAIR_H
#define AUXPORT_STRINGPAIR_H
/*
*			AuxPort Library
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

#include<string>
#include<iostream>
#include<vector>
#include"../Log/AuxLog.h"
#include"AuxString.h"
/*===================================================================================*/

namespace AuxPort
{
/*
		StringPair Class, This class allows you to create string pair objects. 
		For Example : AuxPort::StringPair pair("key","value"); 
*/	
	class StringPair : public ILog
	{
	public:
/*
		StringPair() = default Constructor
		Creates an empty StringPair object
*/		
		StringPair() = default;
/*===================================================================================*/
/*
		StringPair(const StringPair& stringPair) = default Copy constructor
		Creates a StringPair object initialized with the Passed StringPair Object
*/
		StringPair(const StringPair& stringPair) = default;
/*===================================================================================*/
/*
		StringPair(const std::string& key, const std::string& value)
		Creates a StringPair object initialized with a std::string key-value pair.
*/
		StringPair(const std::string& key, const std::string& value);

/*===================================================================================*/
/*
		StringPair(const String& key, const String& value)
		Creates a StringPair object initialized with a std::string key-value pair.
*/
		StringPair(const String& key, const String& value);
/*===================================================================================*/	
/*
		StringPair(const std::string& key, const std::string& value)
		Creates a StringPair object initialized with a char* key-value pair.
*/
		StringPair(const char* key, const char* value);
/*===================================================================================*/	
/*
		Safely Deallocates data members when object goes out of scope.
*/
		~StringPair() = default;
/*===================================================================================*/	
/*
		Overloads ostream << operator to allow printing of StringPair object directly.
*/
		friend std::ostream& operator << (std::ostream& out, const StringPair& sPair);
/*===================================================================================*/	
/*
		Returns reference to the internal key.
*/
		AuxPort::String key() const;
/*===================================================================================*/	
/*
		Returns reference to the internal value.
*/
		AuxPort::String value() const;
/*===================================================================================*/
/*
		Updates the Key
*/
		void setKey(const AuxPort::String& key);

/*===================================================================================*/
/*
		Updates the Value
*/		
		void setValue(const AuxPort::String& value);
/*===================================================================================*/	
		void Log() override;
	private:
		AuxPort::String _key;
		AuxPort::String _value;
	};
}

#endif