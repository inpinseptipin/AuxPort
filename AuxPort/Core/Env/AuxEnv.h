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
/// @cond
/// Command for Doxygen to ignore comments below
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
/// Preprocessor Definitions to Determine C++ Compiler
///////////////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
	#define AUXPORT_COMPILER_MSVC
#elif __GNUC__
	#define AUXPORT_COMPILER_GCC
#elif __clang__
	#define AUXPORT_COMPILER_CLANG
#endif

///////////////////////////////////////////////////////////////////////////////////////
/// Preprocessor Definitions for SIMD Header Availability (Header File)
///////////////////////////////////////////////////////////////////////////////////////

#ifdef AUXPORT_COMPILER_MSVC
#if _WIN32 || _WIN64
	#include <intrin.h>
	#define AUXSIMD 1
#endif
#elif defined(AUXPORT_COMPILER_GCC) || defined(AUXPORT_COMPILER_CLANG)
#if __x86_64__ || _M_X64 || _M_IX86 || i386 || __i386__ || __i386
	#include <immintrin.h>
	#include <cpuid.h>
	#define AUXSIMD 1
	#define AUX64SIMD 1
#elif __arm64__ || __APPLE__
	#include <arm_neon.h>
	#define AUXSIMD 1
	#define AUXNEON 1
#endif
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

	#define AUXPORT_LINUX 9999
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
		#define AUXPORT_64 64
		typedef int int32;
		typedef unsigned int uint32;
		typedef long long int int64;
		typedef unsigned long long int uint64;
		typedef unsigned char uint8;
		typedef signed char int8;
		typedef unsigned short uint16;
		typedef signed short int16;
	#elif i386 || __i386__ || __i386 || _M_IX86
		#define AUXPORT_32 32
		typedef int int32;
		typedef unsigned int uint32;
		typedef unsigned char uint8;
		typedef signed char int8;
		typedef unsigned short uint16;
		typedef signed short int16;
	#endif

	#if __arm64__
		#define AUXPORT_ARM 640
		#define AUXPORT_64 64
		typedef int int32;
		typedef unsigned int uint32;
		typedef long long int int64;
		typedef unsigned long long int uint64;
		typedef unsigned char uint8;
		typedef signed char int8;
		typedef unsigned short uint16;
		typedef signed short int16;
	#endif


	#define AUXPORT_MAC 9999
	#define STR(x) #x
	#define XSTR(x) STR(x)
	#define AuxMessage(y) #y
	#define AuxAssert(x,y) if (!(x)) { printf("Error Message :%s \nStatement : %s \nFunction: %s \nfile %s, line %d.\n", AuxMessage(y),STR(x), __FUNCTION__, __FILE__, __LINE__); abort(); }
#endif

///////////////////////////////////////////////////////////////////////////////////////
/// @endcond
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
///	@brief This namespace contains all classes and function in the AuxPort Library
///////////////////////////////////////////////////////////////////////////////////////
namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	///	@brief This class provides a interface to get information about the current environment
	///////////////////////////////////////////////////////////////////////////////////////
	class Env {
	public:
		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if the CPU supports SSE Instruction Set. Otherwise, returns false.
		///////////////////////////////////////////////////////////////////////////////////////
		static bool supportsSSE()
		{
#if AUXSIMD
#if AUXPORT_WINDOWS
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);
			return (cpuInfo[3] & (1 << 25));
#elif AUXPORT_LINUX
			int cpuInfo[4];
			cpuid(cpuInfo,0);
			int nIds = cpuInfo[0];
			if(nIds >=0x00000001)
			{
				cpuid(cpuInfo,0x00000001);
				return (cpuInfo[3] & static_cast<int>(1<<25)) !=0;
			}
#endif
#endif	
			return false;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if the CPU supports SSE2 Instruction Set. Otherwise, returns false.
		///////////////////////////////////////////////////////////////////////////////////////
		static bool supportsSSE2()
		{
#if AUXSIMD
#if AUXPORT_WINDOWS
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);
			return (cpuInfo[3] & (1 << 26));
#elif AUXPORT_LINUX
			int cpuInfo[4];
			cpuid(cpuInfo,0);
			int nIds = cpuInfo[0];
			if(nIds >=0x00000001)
			{
				cpuid(cpuInfo,0x00000001);
				return (cpuInfo[3] & static_cast<int>(1<<26)) !=0;
			}
#endif
#endif
			return false;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if the CPU supports AVX Instruction Set. Otherwise, returns false.
		///////////////////////////////////////////////////////////////////////////////////////
		static bool supportsAVX()
		{
#if AUXSIMD
#if AUXPORT_WINDOWS
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);
			return (cpuInfo[2] & (1 << 28));
#elif AUXPORT_LINUX
			int cpuInfo[4];
			cpuid(cpuInfo,0);
			int nIds = cpuInfo[0];
			if(nIds >=0x00000001)
			{
				cpuid(cpuInfo,0x00000001);
				return (cpuInfo[2] & static_cast<int>(1<<28)) !=0;
			}
#endif

#endif
			return false;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if current platform is Windows
		///////////////////////////////////////////////////////////////////////////////////////
		static bool isWindowsOS()
		{
#if AUXPORT_WINDOWS
			return true;
#endif
			return false;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if current platform is Linux
		///////////////////////////////////////////////////////////////////////////////////////
		static bool isLinuxOS()
		{
#if AUXPORT_LINUX
			return true;
#endif
			return false;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if current platform is MAC
		///////////////////////////////////////////////////////////////////////////////////////
		static bool isMacOS()
		{
#if AUXPORT_MAC
			return true;
#endif
			return false;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns true if current architecture is 32-bit
		///////////////////////////////////////////////////////////////////////////////////////
		static bool is32Bit() 
		{
#if AUXPORT_32
			return true;
#endif
			return false;
		}

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Return true if current architecture is 64-bit
		///////////////////////////////////////////////////////////////////////////////////////
		static bool is64Bit()
		{
#if AUXPORT_64
			return true;
#endif
			return false;
		}

		static bool isArm()
		{
#if AUXPORT_ARM
			return true;
#endif
			return false;
		}

		static bool supportsNeon()
		{
#if AUXPORT_ARM
			return true;
#endif
			return false;
		}

	private:
#if AUXPORT_LINUX
		static void cpuid(int info[4],int infoType)
		{
			__cpuid_count(infoType,0,info[0],info[1],info[2],info[3]);
		}
#endif

	};
}
#endif // !ENV_H
