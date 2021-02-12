#ifndef CASTER_H
#define CASTER_H
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

typedef int int32;
typedef unsigned int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;

namespace AuxPort
{
/*
		ICasters is an abstract class that provides pure virtual interfaces to Cast AuxPort Library Types to Fundamental Datatypes and STL Types.
*/
	class ICasters
	{
	public:
/*===================================================================================*/	
/*
	Virtual interface that can be inhertied and defined to convert a given Class Type to int32	
*/
		 virtual int32 toInt32()=0;

/*===================================================================================*/	
/*
	Virtual interface that can be inhertied and defined to convert a given Class Type to uint32	
*/		 
		 virtual uint32 toUInt32()=0;
/*===================================================================================*/	
/*
	Virtual interface that can be inhertied and defined to convert a given Class Type to int64	
*/
		 virtual int64 toInt64()=0;
/*===================================================================================*/	
/*
	Virtual interface that can be inhertied and defined to convert a given Class Type to uint64	
*/
		 virtual uint64 toUInt64()=0;
/*===================================================================================*/	
/*
	Virtual interface that can be inhertied and defined to convert a given Class Type to std::string	
*/
		 virtual std::string toStdString() = 0;
	};

/*===================================================================================*/	
/*
	Casters is a class that consist of functions to cast fundamental types into each other	
*/
	class Casters
	{
	protected:
/*===================================================================================*/	
/*
	This casts a numerical char to int64 (Inheritable)	
*/	
		int64 charToInt(char value) { return value >= 48 && value <= 57 ? int64(value)-48 : -1;};
/*===================================================================================*/	
/*
	This casts a int64 values to char (Inheritable)	
*/
		char intToChar(int64 value) { return value > 128 ? value : 0;};
	public:
/*===================================================================================*/	
/*
	This casts a numerical char to int64.	
*/	
		static int64 toInt(char value) { return value >= 48 && value <= 57 ? int64(value)-48 : -1;};
/*
	This casts a int64 to char.	
*/
		static char toChar(int64 value) { return value > 128 ? value : 0;}; 
		
	};
}

#endif 




