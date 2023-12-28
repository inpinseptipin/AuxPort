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
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Env/AuxEnv.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Log/AuxLog.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Log/AuxLog.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/String/AuxString.h    
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/String/AuxString.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/String/AuxStringPair.cpp 
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Time/AuxTime.h 
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Time/AuxTime.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/File/AuxFile.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/File/AuxFile.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/TestCase/AuxCase.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/TestCase/AuxCase.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Utility/AuxCaster.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Utility/AuxUtility.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/Utility/AuxCircularBuffer.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/SIMD/AuxSimd.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Core/SIMD/AuxSimd.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Buffer/AuxBuffer.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Effects/Distortion/AuxDistortion.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Effects/Distortion/AuxDistortion.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Windows/AuxWindow.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/FFT/AuxFFT.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Filters/AuxIIR.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Filters/AuxIIR.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Effects/Gain/AuxPan.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Effects/Gain/AuxPan.cpp
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Oscillators/AuxOscillator.h
    ${AuxTest_SOURCE_DIR}/AuxPort/Audio/Oscillators/AuxOscillator.cpp
   
)
