#ifndef STRINGOBJECTARRAY_H
#define STRINGOBJECTARRAY_H

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
#pragma once
#include<string>
#include<vector>
#include<iostream>
#include "../Log/AuxPort_Log.h"

namespace AuxPort
{
/*
		StringObject Array allows to create one to many key value object arrays.
		For Example : AuxPort::StringObjectArray objectArray("key",{"1","2","3"});
*/
	class StringObjectArray : public ILog
	{
	public:
		StringObjectArray() = default;
		StringObjectArray(const StringObjectArray& objectarray) = default;
		StringObjectArray(const std::string& key, const std::vector<std::string>& values);
		StringObjectArray(const std::string& key, const std::string& values);
		StringObjectArray(const std::string& key, std::string values[]);
		~StringObjectArray() = default;

		friend std::ostream& operator << (std::ostream& out, StringObjectArray& sObject);

		void Log() override;

		std::string& key();
		std::vector<std::string>& values();
	private:
		std::string _key;
		std::vector<std::string> _values;
	};
}
#endif