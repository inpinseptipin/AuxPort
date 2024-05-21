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
set(AUXPORT_VERSION 0.1)
include(FetchContent)

# Fetching AuxPort
FetchContent_Declare(
	auxport
	GIT_REPOSITORY https://github.com/inpinseptipin/AuxPort
	GIT_TAG	master
)
FetchContent_MakeAvailable(auxport)

# Fetching rtaudio
FetchContent_Declare(
	rtaudio
	GIT_REPOSITORY https://github.com/thestk/rtaudio
	GIT_TAG	master
)
FetchContent_MakeAvailable(rtaudio)

project(AuxRtAudio)
add_executable(
	${PROJECT_NAME}
	main.cpp
	AuxRtAudio.h 
	AuxRtAudio.cpp
)

# Adding AuxPort include directories
target_include_directories(${PROJECT_NAME} PUBLIC "${AuxTest_SOURCE_DIR}/AuxPort")
# Linking AuxPort Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC AuxPort)

# Adding rtaudio as a dependency to build it before building the extension
add_dependencies(${PROJECT_NAME} rtaudio)
# Adding rtaudio include directories
target_include_directories(${PROJECT_NAME} PUBLIC "${rtaudio_SOURCE_DIR}")
# Linking audio import Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC debug "${rtaudio_BINARY_DIR}/Debug/rtaudiod.lib" optimized "${rtaudio_BINARY_DIR}/Release/rtaudio.lib")

# Copying the rtaudio dll to the executable's directory
add_custom_command(
	TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${rtaudio_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug/rtaudiod.dll,Release/rtaudio.dll>"
	"${CMAKE_CURRENT_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>"
)