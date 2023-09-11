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
#
#

add_library(
    AuxPort
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Env/AuxEnv.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Log/AuxLog.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Log/AuxLog.cpp
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/String/AuxString.h    
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/String/AuxString.cpp
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/String/AuxStringPair.cpp 
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Time/AuxTime.h 
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Time/AuxTime.cpp
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/File/AuxFile.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/File/AuxFile.cpp
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Utility/AuxCaster.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Core/Utility/AuxUtility.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Buffer/AuxBuffer.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Effects/Distortion/AuxDistortion.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Effects/Distortion/AuxDistortion.cpp
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Windows/AuxWindow.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/FFT/AuxFFT.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Filters/AuxIIR.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Filters/AuxIIR.cpp
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Effects/Gain/AuxPan.h
    ${Sandbox_SOURCE_DIR}/AuxPort/AuxPort/Audio/Effects/Gain/AuxPan.cpp
)
