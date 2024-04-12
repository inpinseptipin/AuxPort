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

# Fetching CURL
FetchContent_Declare(
	curl
	GIT_REPOSITORY https://github.com/curl/curl
	GIT_TAG	master
)
FetchContent_MakeAvailable(curl)

project(AuxCurl)
add_executable(
	${PROJECT_NAME}
	main.cpp
	AuxCurl.cpp
	AuxCurl.h 
)

# Adding AuxPort include directories
target_include_directories(${PROJECT_NAME} PUBLIC "${AuxTest_SOURCE_DIR}/AuxPort")
# Linking AuxPort Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC AuxPort)

# Adding CURL as a dependency to build it before building the extension
add_dependencies(${PROJECT_NAME} CURL::libcurl)
# Adding CURL include directories
target_include_directories(${PROJECT_NAME} PUBLIC "${CURL_SOURCE_DIR}/include")
# Linking CURL import Libraries and other required Librarires
target_link_libraries(${PROJECT_NAME} PUBLIC debug "${CURL_BINARY_DIR}/lib/Debug/libcurl-d_imp.lib" optimized "${CURL_BINARY_DIR}/lib/Release/libcurl_imp.lib")
target_link_libraries(${PROJECT_NAME} PUBLIC Ws2_32.lib)
target_link_libraries(${PROJECT_NAME} PUBLIC Crypt32.lib)
target_link_libraries(${PROJECT_NAME} PUBLIC Wldap32.lib)
target_link_libraries(${PROJECT_NAME} PUBLIC Normaliz.lib)

# Copying the libcurl dll to the executable's directory
add_custom_command(
	TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${CURL_BINARY_DIR}/lib/$<IF:$<CONFIG:Debug>,Debug/libcurl-d.dll,Release/libcurl.dll>"
	"${CMAKE_CURRENT_BINARY_DIR}/$<IF:$<CONFIG:Debug>,Debug,Release>"
)