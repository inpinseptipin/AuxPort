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

///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion for SIMD and SIMD Headers Inculsion
///////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
	#include <intrin.h>
	#define AUXSIMD 1
#endif

///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion to determine the current Compiler
///////////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
	#define AUXPORT_COMPILER_MSVC
#elif __GNUC__
	#define AUXPORT_COMPILER_GCC
#elif __clang__
	#define AUXPORT_COMPILER_CLANG
#endif

///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion to determine the current C++ Standard Version
///////////////////////////////////////////////////////////////////////////////////////
#ifdef AUXPORT_COMPILER_MSVC
	#if _MSVC_LANG == 201402L
		#define AUXPORT_CXX14
		#define AUXPORT_CXX_VER 14
	#elif _MSVC_LANG == 201703L
		#define AUXPORT_CXX17
		#define AUXPORT_CXX_VER 17
	#elif __MSVC_LANG == 202002L
		#define AUXPORT_CXX20
		#define AUXPORT_CXX_VER 20
	#endif
#elif defined(AUXPORT_COMPILER_GCC) || defined(AUXPORT_COMPILER_CLANG)
	#if __cplusplus == 201402L
		#define AUXPORT_CXX14
		#define AUXPORT_CXX_VER 14
	#elif __cplusplus == 201703L
		#define AUXPORT_CXX17
		#define AUXPORT_CXX_VER 17
	#elif __cplusplus == 202002L
		#define AUXPORT_CXX20
		#define AUXPORT_CXX_VER 20
	#endif
#endif

///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion to determine if Compiling on WINDOWS x86 or x64
///////////////////////////////////////////////////////////////////////////////////////
#if _WIN32 || _WIN64
	#if _WIN64
		#define AUXPORT_64 64
		typedef int int32;
		typedef unsigned int uint32;
		typedef long long int int64;
		typedef unsigned long long int uint64;
		typedef unsigned char uint8;
		typedef signed char int8;
		typedef unsigned short uint16;
		typedef signed short int16;
	#else
		#define AUXPORT_32 32
		typedef int int32;
		typedef unsigned int uint32;
		typedef unsigned char uint8;
		typedef signed char int8;
		typedef unsigned short uint16;
		typedef signed short int16;
	#endif

	#define AUXPORT_WINDOWS 9999
	#define STR(x) #x
	#define XSTR(x) STR(x)
	#define AuxMessage(y) #y
	#define AuxAssert(x,y) if (!(x)) { printf("Error Message :%s \nStatement : %s \nFunction: %s \nfile %s, line %d.\n", AuxMessage(y),STR(x), __FUNCTION__, __FILE__, __LINE__); abort(); }
#endif

///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion to determine if Compiling on LINUX x86 or x64
///////////////////////////////////////////////////////////////////////////////////////
#if __linux__
	#if __x86_64__
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

	#define AUXPORT_LINUX
	#define STR(x) #x
	#define XSTR(x) STR(x)
	#define AuxMessage(y) #y
	#define AuxAssert(x,y) if (!(x)) { printf("Error Message :%s \nStatement : %s \nFunction: %s \nfile %s, line %d.\n", AuxMessage(y),STR(x), __FUNCTION__, __FILE__, __LINE__); abort(); }
#endif

///////////////////////////////////////////////////////////////////////////////////////
///	Preprocessor Defintion to determine if Compiling on APPLE x86 or x64
///////////////////////////////////////////////////////////////////////////////////////
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

	#define AUXPORT_MAC
	#define STR(x) #x
	#define XSTR(x) STR(x)
	#define AuxMessage(y) #y
	#define AuxAssert(x,y) if (!(x)) { printf("Error Message :%s \nStatement : %s \nFunction: %s \nfile %s, line %d.\n", AuxMessage(y),STR(x), __FUNCTION__, __FILE__, __LINE__); abort(); }
#endif


namespace AuxPort
{
	class Env
	{
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

		static bool isWindowsOS()
		{
#if AUXPORT_WINDOWS
			return true;
#endif
			return false;
		}

		static bool isLinuxOS()
		{
#if AUXPORT_LINUX
			return true;
#endif
			return false;
		};

		static bool isMacOS()
		{
#if AUXPORT_MAC
			return true;
#endif
			return false;
		};

		static bool is32Bit() 
		{
#if AUXPORT_32
			return true;
#endif
			return false;
		}

		static bool is64Bit()
		{
#if AUXPORT_64
			return true;
#endif
			return false;
		}

	};
}
#endif // !ENV_H