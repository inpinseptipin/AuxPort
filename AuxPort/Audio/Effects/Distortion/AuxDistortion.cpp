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

#include "AuxDistortion.h"

void AuxPort::Audio::Distortion::DC(AuxPort::Audio::Buffer<float>& buffer, const float& offset)
{
	buffer.add(offset);
}

float AuxPort::Audio::Distortion::DC(float& audio, const float& offset, const bool& preserve)
{
	return preserve == false ? audio += offset : audio + offset;
}

void AuxPort::Audio::Distortion::zeroCrossing(AuxPort::Audio::Buffer<float>& buffer, const float& threshold)
{
	for (size_t i = 0; i < buffer.size(); i++)
	{
		if (abs(buffer.get(i)) < threshold)
			buffer.set(0,i);
	}
}

float AuxPort::Audio::Distortion::zeroCrossing(float& audio, const float& threshold, const bool& preserve)
{
	return preserve == false ? audio = audio < threshold ? 0 : audio : audio < threshold ? 0 : audio;
}

void AuxPort::Audio::Distortion::arcTan(AuxPort::Audio::Buffer<float>& buffer, const float& drive)
{
	for (size_t i = 0; i < buffer.size(); i++)
		buffer.set(atan(drive * buffer.get(i)), i);
}

float AuxPort::Audio::Distortion::arcTan(float& audio, const float& drive, const bool& preserve)
{
	return preserve == false ? audio = atan(audio * drive) : atan(audio * drive);

}

void AuxPort::Audio::Distortion::arcTan2(AuxPort::Audio::Buffer<float>& buffer, const float& drive)
{
	for (size_t i = 0; i < buffer.size(); i++)
		buffer.set(
			(2 / AuxPort::pi) * atan(drive * buffer.get(i)),
			i);
}

float AuxPort::Audio::Distortion::arcTan2(float& audio, const float& drive, const bool& preserve)
{
	return preserve == false ? audio = (2 / AuxPort::pi) * arcTan(audio, drive) : (2 / AuxPort::pi) * arcTan(audio, drive);
}

void AuxPort::Audio::Distortion::hyperbolicTan(AuxPort::Audio::Buffer<float>& buffer, const float& drive)
{
	for (size_t i = 0; i < buffer.size(); i++)
		buffer.set(tanh(drive * buffer.get(i)), i);
}

float AuxPort::Audio::Distortion::hyperbolicTan(float& audio, const float& drive, const bool& preserve)
{
	return preserve == false ? audio = tanh(drive * audio) : tanh(drive * audio);
}

float AuxPort::Audio::Distortion::schetzenOverdrive(float& audio, const bool& preserve)
{
	auto x = abs(audio);
	if (preserve)
	{
		if (x >= 0.0f && x < 0.34f)
			return 2 * audio;
		else if (x >= 0.34f && x < 0.66f)
			return audio < 0 ? -(3 - powf(2 - 3 * audio, 2)) / 3 : (3 - powf(2 - 3 * audio, 2)) / 3;
		else if (x >= 0.66f && x <= 1.0f)
			return audio < 0 ? -1.0f : 1.0f;
	}
	else
	{
		if (x >= 0.0f && x < 0.34f)
			audio = 2 * audio;
		else if (x >= 0.34f && x < 0.66f)
			audio = audio < 0 ? -(3 - powf(2 - 3 * audio, 2)) / 3 : (3 - powf(2 - 3 * audio, 2)) / 3;
		else if (x >= 0.66f && x <= 1.0f)
			audio = audio < 0 ? -1.0f : 1.0f;
	}
	return 0.0f;
	
}

float AuxPort::Audio::Distortion::exponential(float& audio, const bool& preserve)
{
	return preserve == false ? audio = AuxPort::Utility::signum(audio) * (1 - exp(-abs(audio))) : AuxPort::Utility::signum(audio) * (1 - exp(-abs(audio)));
}

float AuxPort::Audio::Distortion::softClipper(float& audio, const bool& preserve)
{
	return preserve == false ? audio = audio - 0.34f * powf(audio, 3) : audio - 0.34f * powf(audio, 3);

}

float AuxPort::Audio::Distortion::crush(float& audio, const float& depth, const bool& preserve)
{
	auto quantizationLevel = powf(2, depth) - 1;
	return preserve == false ? audio = AuxPort::Utility::round<float>(audio + 1) * quantizationLevel / (quantizationLevel - 1) : AuxPort::Utility::round<float>(audio + 1) * quantizationLevel / (quantizationLevel - 1);

}

float AuxPort::Audio::Distortion::sinusoidalFold(float& audio, const bool& preserve)
{
	return preserve == false ? audio = std::sin(audio) : std::sin(audio);
}

float AuxPort::Audio::Distortion::squareFold(float& audio, const bool& preserve)
{
	return preserve == true ? audio = (audio > 0.0f ? 1.0f : -1.0f) : audio > 0.0f ? 1.0f : -1.0f;
}

float AuxPort::Audio::Distortion::levianTanh(float& audio, const bool& preserve)
{
	float x2 = audio * audio;
	float x3 = x2 * audio;
	float x5 = x2 * x3;
	float z = audio + (0.16489087f * x3) + (0.00985468f * x5);
	return preserve == true ? audio = z / sqrtf(1.f + (z * z)) : audio = z / sqrtf(1.f + (z * z));
}

float AuxPort::Audio::Assymetric::process(float sample,float k,float g = 1.0,Type type = Type::v1)
{
	if (type == v1)
	{
		if (sample >= 0)
			circBuffer.push(Distortion::hyperbolicTan(sample, k, true));
		if (sample < 0)
			circBuffer.push(Distortion::arcTan(sample,k,true));
	}
	if (type == v2)
	{
		if (sample >= 0)
			circBuffer.push(Distortion::arcTan(sample, k, true) / Distortion::arcTan(k, 1, true));
		if (sample < 0)
		{
			auto constant = k / g;
			circBuffer.push((g * Distortion::arcTan(sample, k / g, true)) / Distortion::arcTan(constant, 1.0, true));
		}
	}
	counter++;
	if (counter == circBuffer.getSize() - 1)
		circBuffer.meanRemoval();
	return circBuffer.pop();
}
