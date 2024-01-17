#ifndef AUXPORT_ENV_H
#define AUXPORT_ENV_H
/*
			AuxPort Library
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
#include <assert.h>
#include "../Log/AuxLog.h"

#if defined(_MSC_VER)
#include <intrin.h>
#define AUXSIMD 1
#endif
///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion to Determine if Compiling on Windows x86 or x64
///////////////////////////////////////////////////////////////////////////////////////


#if _WIN32 || _WIN64
#if _WIN64
#define AUXPORT_64
typedef int int32;
typedef unsigned int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
#else
#define AUXPORT_32
typedef int int32;
typedef unsigned int uint32;
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;

#endif
#define STR(x) #x
#define XSTR(x) STR(x)
#define AuxMessage(y) #y
#define AuxAssert(x,y) if (!(x)) { printf("Error Message :%s \nStatement : %s \nFunction: %s \nfile %s, line %d.\n", AuxMessage(y),STR(x), __FUNCTION__, __FILE__, __LINE__); abort(); }


#endif

#if __APPLE__ || __MACH__
#if __x86_64__ || _M_X64
#define AUXPORT_64
typedef int int32;
typedef unsigned int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
#elif i386 || __i386__ || __i386 || _M_IX86
#define AUXPORT_32
typedef int int32;
typedef unsigned int uint32;
typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
#endif
#endif // 


namespace AuxPort {
	class Env {
	public:
		static bool supportsSSE()
		{
#if AUXSIMD
#if _WIN32 || _WIN64
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);
			return (cpuInfo[3] & (1 << 25));
#endif
#endif	
			return false;
		}

		static bool supportsSSE2()
		{
#if AUXSIMD
#if _WIN32 || _WIN64
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);
			return (cpuInfo[3] & (1 << 26));
#endif
#endif
			return false;
		}

		static bool supportsAVX() 
		{
#if AUXSIMD
#if _WIN32 || _WIN64
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);
			return (cpuInfo[2] & (1 << 28));
#endif
#endif
			return false;
		}
	};

}


#endif // !ENV_H



