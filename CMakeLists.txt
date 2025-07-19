#
#			AuxPort Library
#			"Generic Modules to facilitate C++ Windows Application development" - inpinseptipin
#
#			BSD 3-Clause License
#
#			Copyright (c) 2020, Satyarth Arora
#			All rights reserved.
#
#			Redistribution and use in source and binary forms, with or without
#			modification, are permitted provided that the following conditions are met:
#
#			1. Redistributions of source code must retain the above copyright notice, this
#			   list of conditions and the following disclaimer.
#
#			2. Redistributions in binary form must reproduce the above copyright notice,
#			   this list of conditions and the following disclaimer in the documentation
#			   and/or other materials provided with the distribution.
#
#			3. Neither the name of the copyright holder nor the names of its
#			   contributors may be used to endorse or promote products derived from
#			   this software without specific prior written permission.
#
#			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#			AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#			IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#			FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#			DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS  ON)





option(AUXPORT_EXPERIMENTAL "Use Experimental Code" OFF)
option(AUXPORT_BUILD_TESTS "Build AuxPort Test Library" OFF)
option(AUXPORT_BUILD_SANDBOX "Build Sandbox Environment" OFF)
option(AUXPORT_BUILD_BENCH "Build AuxPort Benchmark Library" OFF)

if("${CMAKE_GENERATOR_PLATFORM}" STREQUAL "Win32")
	option(AUXPORT_BUILD_FOR_RACKAFX "Build AuxPort for RackAFX" OFF)  
endif()

if(AUXPORT_EXPERIMENTAL)
	add_compile_definitions(AUXPORT_EXP 1337)
endif()
project(AuxPort)
add_subdirectory(AuxPort)




if(AUXPORT_BUILD_FOR_RACKAFX)
	set(AUXPORT_RACKAFX_COMPILE_OPTIONS_DEBUG "-MTd")
	set(AUXPORT_RACKAFX_COMPILE_OPTIONS_RELEASE "-MT")
	target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${AUXPORT_RACKAFX_COMPILE_OPTIONS_DEBUG}>")
	target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${AUXPORT_RACKAFX_COMPILE_OPTIONS_RELEASE}>")
 endif()


if(AUXPORT_BUILD_SANDBOX)
	option(AUXPORT_BUILD_EXTENSION_FOR_AUDIOFILE "Build AuxPort Extensions for AudioFile" OFF)
	



	set(AUXPORT_SANDBOX_NAME "SandBox")
	add_executable(
		${AUXPORT_SANDBOX_NAME}
		main.cpp	
		${PROJECT_SOURCE_DIR}/Extensions/AuxAudioFile/AuxAudioFile.h
		${PROJECT_SOURCE_DIR}/Extensions/AuxAudioFile/AuxAudioFile.cpp
	)
	target_link_libraries(${AUXPORT_SANDBOX_NAME} AuxPort)
	
	if(AUXPORT_BUILD_EXTENSION_FOR_AUDIOFILE)
		include(FetchContent)
		FetchContent_Declare(
			audiofile
			GIT_REPOSITORY https://github.com/adamstark/AudioFile.git
			GIT_TAG master
		)
		FetchContent_MakeAvailable(audiofile)
		target_include_directories(${AUXPORT_SANDBOX_NAME} PUBLIC "${AudioFile_SOURCE_DIR}/")
		target_include_directories(${AUXPORT_SANDBOX_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/AuxPort")
	endif(AUXPORT_BUILD_EXTENSION_FOR_AUDIOFILE)



	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${AUXPORT_SANDBOX_NAME})
endif(AUXPORT_BUILD_SANDBOX)





if(AUXPORT_BUILD_TESTS)
	add_subdirectory(AuxTest)
	target_link_libraries(${AUXPORT_SANDBOX_NAME} AuxTest)
endif(AUXPORT_BUILD_TESTS)

if(AUXPORT_BUILD_BENCH)
	add_subdirectory(AuxBench)
	target_link_libraries(${AUXPORT_SANDBOX_NAME} AuxBench)
endif(AUXPORT_BUILD_BENCH)

