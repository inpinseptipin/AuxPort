/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2026, Satyarth Arora
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

/*===================================================================================*/
#pragma once
/*
*			Core Headers
*/
#include "Core/Env/AuxEnv.h"
#include "Core/Env/AuxDebug.h"
#include "Core/Log/AuxLog.h"
#include "Core/Time/AuxTime.h"
#include "Core/String/AuxString.h"
#include "Core/File/AuxFile.h"
#include "Core/Utility/AuxCaster.h"
#include "Core/Utility/AuxUtility.h"
#include "Core/Utility/AuxSeries.h"
#include "Core/Utility/AuxMath.h"
#include "Core/Utility/AuxPascal.h"
#include "Core/TestCase/AuxCase.h"
#include "Core/SIMD/AuxSimd.h"
#include "Core/Crypto/AuxCrypto.h"



/*
*			Audio Headers
*/
#include "Audio/Buffer/AuxBuffer.h"
#include "Audio/Effects/Templates/AuxEffect.h"
#include "Audio/Effects/Distortion/AuxDistortion.h"
#include "Audio/Effects/Gain/AuxPan.h"
#include "Audio/Effects/Gain/AuxMixer.h"
#include "Audio/Windows/AuxWindow.h"
#include "Audio/FFT/AuxFFT.h"
#include "Audio/Filters/AuxFIR.h"
#include "Audio/Filters/AuxIIR.h"
#include "Audio/Oscillators/AuxOscillator.h"
#include "Audio/Stimulus/AuxStimulus.h"
#include "Audio/Transforms/AuxWH.h"

/*
*			Graphics Headers
*/
#include "Graphics/Scopes/AuxScope.h"
#include "Graphics/Images/AuxImage.h"
#include "Graphics/SVG/AuxSVGObject.h"
#include "Graphics/SVG/AuxSVGColour.h"
#include "Graphics/SVG/AuxSVGText.h"
#include "Graphics/SVG/AuxSVG.h"



/*===================================================================================*/