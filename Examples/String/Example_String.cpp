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

#include "../../AuxPort/AuxPort.h"

/*===================================================================================*/

int main()
{
/*
    Creating a String Object
*/
    AuxPort::String string;

/*
    Initiliazing a String object with C-Style String
*/
    AuxPort::String string_1 = "Hello ";

/*
    Initiliazing a String object with another String object
*/
    AuxPort::String string_2 = string_1;

/*
    Initializing a String with a sum of two strings;
*/
    AuxPort::String string_3 = string_1 + string_2;    

/*
    Logging String value onto the console;
*/
    string_3.Log();    

/*
    Converting String to C-Style String
*/
    string_3.getCString();

/*
    Get Length of String
*/
    string_3.length();

/*
    Replacing all instances of a given character in a string
*/
    string_3.replaceCharacter('h','y');

/*
    Converts the String into an unsigned 64 bit Integer (Provided The entire String consist of Numeric Characters)
*/
    string="83838282883821";
    string.toUInt64();

/*
    Converts the String into an signed 64 bit Integer (Provided The entire String consist of Numeric Characters)
*/
    string="-83838282";
    string.toInt64();

}