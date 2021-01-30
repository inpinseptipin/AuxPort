#ifndef TimeType_H
#define TimeType_H
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

/*===================================================================================*/
#pragma once
#include<ctime>
#include<string>
#include<sstream>



/*===================================================================================*/
/*
		This is a wrapper over the C Time Library, It is used to get Date and Time formatted onto std::string
		The wrapper provides you with an interface that can be called.

		Eg: AuxPort::Time::getCurrentTime(TimeType::Time)

*/
namespace AuxPort
{
/*
		TimeType is a type that can be used to set Formatting rules for the values returned by getCurrentTime() function
*/

	enum class TimeType
	{
		Day = 0x31,
		Date = 0x32,
		Time = 0x33,
		Year = 0x34,
		Raw = 0x35
	};
/*===================================================================================*/
	class Time
	{
	public:

/*
		This function is used to get current system time and returns the time typecasted into std::string.
		Parameters
*		TimeType : TimeType is a type that can be used to set Formatting rules for the values returned by getCurrentTime() function
*/
		static std::string getCurrentTime(const TimeType& timeType);
	};
}
#endif