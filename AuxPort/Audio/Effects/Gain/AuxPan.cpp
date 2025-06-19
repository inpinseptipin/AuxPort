  #include "AuxPan.h"
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2025, Satyarth Arora
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



AuxPort::Audio::Pan::Pan(const Type& type)
{
	this->type = type;
	this->pan = 0.0f;
}

void AuxPort::Audio::Pan::setPan(float pan, float panStart, float panEnd)
{
	if (type == Linear || type == Sqrt || type == Sinusoidal)
	{
		this->pan = AuxPort::Utility::remap<float>(pan, 0, 1, panStart, panEnd);
	}
	if (type == Constant)
	{
		this->pan = AuxPort::Utility::remap<float>(pan, 0, 2, panStart, panEnd);
	}
}



void AuxPort::Audio::Pan::process(float& leftChannel, float& rightChannel)
{
	if (type == Type::Linear)
	{
		leftChannel *= (1-pan);
		rightChannel *= pan;
	}
	if (type == Type::Sqrt)
	{
		leftChannel *= sqrtf(1-pan);
		rightChannel *= sqrtf(pan);
	}
	if (type == Type::Sinusoidal)
	{
		leftChannel *= cosf(pan * (AuxPort::pi / 2));
		rightChannel *= sinf(pan * (AuxPort::pi / 2));
	}
	if (type == Type::Constant)
	{
		leftChannel *= cosf(pan * (AuxPort::pi / 4));
		rightChannel *= sinf(pan * (AuxPort::pi / 4));
	}

}

void AuxPort::Audio::Pan::process(float* leftChannel,float* rightChannel, uint32_t numberOfSamples)
{
	AuxAssert(numberOfSamples > 0, "Cannot Process an empty buffer");
	for (uint32_t i = 0; i < numberOfSamples; i++)
		this->process(leftChannel[i], rightChannel[i]);
}




