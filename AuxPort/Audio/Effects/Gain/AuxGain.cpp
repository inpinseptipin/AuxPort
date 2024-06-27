#include "AuxGain.h"

AuxPort::Audio::Gain::Gain(float defaultGain)
{
	smoothedGain = defaultGain;
}

void AuxPort::Audio::Gain::process(float& leftChannel, float& rightChannel, float currGain)
{
	smoothedGain = smoothedGain - 0.05 * (smoothedGain - currGain);
	leftChannel *= smoothedGain;
	rightChannel *= smoothedGain;
}
