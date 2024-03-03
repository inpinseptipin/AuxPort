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

# Fetching imgui
FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui
	GIT_TAG	docking
)
FetchContent_MakeAvailable(imgui)

project(AuxGui)
add_executable(
	${PROJECT_NAME}
	AuxGui.h
	AuxGui.cpp
	main.cpp 
)

# Adding AuxPort include directories
target_include_directories(${PROJECT_NAME} PUBLIC "${AuxTest_SOURCE_DIR}/AuxPort")
# Linking AuxPort Libraries
target_link_libraries(${PROJECT_NAME} PUBLIC AuxPort)


# Adding ImGui as a library
add_library(
	ImGui
	"${imgui_SOURCE_DIR}/imconfig.h"
	"${imgui_SOURCE_DIR}/imgui.h"
	"${imgui_SOURCE_DIR}/imgui_internal.h"
	"${imgui_SOURCE_DIR}/imstb_rectpack.h"
	"${imgui_SOURCE_DIR}/imstb_textedit.h"
	"${imgui_SOURCE_DIR}/imstb_truetype.h"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_win32.h"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.h"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.h"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.h"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.h"
	"${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h"
	"${imgui_SOURCE_DIR}/imgui.cpp"
	"${imgui_SOURCE_DIR}/imgui_demo.cpp"
	"${imgui_SOURCE_DIR}/imgui_draw.cpp"
	"${imgui_SOURCE_DIR}/imgui_tables.cpp"
	"${imgui_SOURCE_DIR}/imgui_widgets.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp"
	"${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp"
)
# Adding ImGui include directories for the library itself
target_include_directories(
	ImGui 
	PUBLIC 
    "${imgui_SOURCE_DIR}"
	"${imgui_SOURCE_DIR}/backends"
	"${imgui_SOURCE_DIR}/misc/cpp"
)
# Adding ImGui include directories to our project
target_include_directories(
	${PROJECT_NAME} 
	PUBLIC 
    "${imgui_SOURCE_DIR}"
	"${imgui_SOURCE_DIR}/backends"
	"${imgui_SOURCE_DIR}/misc/cpp"
)
# Linking ImGui to our project
target_link_libraries(${PROJECT_NAME} PUBLIC ImGui d3d9.lib d3d10.lib d3d11.lib d3d12.lib dxgi.lib)