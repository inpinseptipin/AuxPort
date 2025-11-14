#
#			AuxPort Library
#			"Modules for Audio Software Development" - inpinseptipin
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
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Env/AuxEnv.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Log/AuxLog.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Log/AuxLog.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/String/AuxString.h    
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/String/AuxString.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/String/AuxStringPair.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/String/AuxStringPair.cpp 
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Time/AuxTime.h 
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Time/AuxTime.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/File/AuxFile.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/File/AuxFile.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/TestCase/AuxCase.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/TestCase/AuxCase.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxCaster.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxUtility.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxUtility.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxCircularBuffer.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxPascal.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxPascal.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxSeries.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxSeries.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxMath.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Utility/AuxMath.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/SIMD/AuxSimd.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/SIMD/AuxSimd.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Crypto/AuxCrypto.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Core/Crypto/AuxCrypto.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Buffer/AuxBuffer.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Templates/AuxEffect.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Templates/AuxEffect.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Distortion/AuxDistortion.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Distortion/AuxDistortion.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Windows/AuxWindow.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/FFT/AuxFFT.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/FFT/AuxFFT.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Filters/AuxFIR.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Filters/AuxFIR.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Filters/AuxIIR.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Filters/AuxIIR.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Gain/AuxPan.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Gain/AuxPan.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Gain/AuxMixer.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Effects/Gain/AuxMixer.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Oscillators/AuxOscillator.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Oscillators/AuxOscillator.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Stimulus/AuxStimulus.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Audio/Stimulus/AuxStimulus.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Graphics/Scopes/AuxScope.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Graphics/Scopes/AuxScope.cpp
    ${PROJECT_SOURCE_DIR}/AuxPort/Graphics/Images/AuxImage.h
    ${PROJECT_SOURCE_DIR}/AuxPort/Graphics/Images/AuxImage.cpp
   
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()