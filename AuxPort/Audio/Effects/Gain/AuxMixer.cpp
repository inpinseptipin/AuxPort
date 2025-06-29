#include "AuxMixer.h"

void AuxPort::Audio::DownMixer::stereoToMono(float* outputMonoChannel, float* leftChannel, float* rightChannel,size_t numberOfSamples)
{
	AuxAssert(numberOfSamples > 0, "Number of Samples > 0");
	AuxAssert(leftChannel != nullptr, "Reference to the left channel cannot be a nullptr");
	AuxAssert(rightChannel != nullptr, "Reference to the right channel cannot be a nullptr");
	AuxAssert(outputMonoChannel != nullptr, "Reference to the output mono channel cannot be a nullptr");
	for (size_t i = 0; i < numberOfSamples; i++)
		outputMonoChannel[i] = 0.707 * leftChannel[i] + 0.707 * rightChannel[i];
}

void AuxPort::Audio::UpMixer::monoToStereo(float* outputLeftChannel, float* outputRightChannel, float* inputMonoChannel, size_t numberOfSamples)
{
	AuxAssert(numberOfSamples > 0, "Number of Samples > 0");
	AuxAssert(outputLeftChannel != nullptr, "Reference to the left channel cannot be a nullptr");
	AuxAssert(outputRightChannel != nullptr, "Reference to the right channel cannot be a nullptr");
	AuxAssert(inputMonoChannel != nullptr, "Reference to the input mono channel cannot be a nullptr");
	for (size_t i = 0; i < numberOfSamples; i++)
		outputLeftChannel[i] = outputRightChannel[i] = 0.707 * inputMonoChannel[i];
}
