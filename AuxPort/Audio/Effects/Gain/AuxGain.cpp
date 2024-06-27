#include "AuxGain.h"

AuxPort::Audio::Gain::Gain(float defaultGain)
{
	smoothedGain = defaultGain;
}

void AuxPort::Audio::Gain::process(float* leftChannel, float* rightChannel, size_t bufferSize, float currGain)
{
	for (size_t i = 0; i < bufferSize; i++)
	{
		smoothedGain = smoothedGain - 0.05 * (smoothedGain - currGain);
		leftChannel[i] *= smoothedGain;
		rightChannel[i] *= smoothedGain;
	}
}