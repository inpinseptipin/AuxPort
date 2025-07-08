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

AuxPort::Audio::Delay::Delay() : CircularBufferEngine()
{
	delayTime = 0.0f;
	delayTimeInSamples = 0.0f;
	sampleRate = 44100;
	writeDelayIndex = 0;
	readDelayIndex = 0;
	maxDelayTime = 0;
}

void AuxPort::Audio::Delay::setMaxDelayTime(size_t sampleRate,float maxDelayTime)
{
	AuxAssert(maxDelayTime > 0, "Max Delay cannot be less than 0");
	this->maxDelayTime = maxDelayTime;
	this->sampleRate = sampleRate;
	delayBuffer.resize(static_cast<size_t>(sampleRate * maxDelayTime));
}

void AuxPort::Audio::Delay::setDelay(float delayTime)
{
	AuxAssert(delayTime < maxDelayTime, "Delay time cannot be greater than max delay time");
	if (this->delayTime != delayTime)
	{
		this->delayTime = delayTime;
		this->delayTimeInSamples = delayTime * sampleRate;
		std::fill(delayBuffer.begin(), delayBuffer.end(), 0.0f);
		writeDelayIndex = 0;
		readDelayIndex = 0;
	}
}

void AuxPort::Audio::Delay::push(float sample)
{
	return;
}

float AuxPort::Audio::Delay::pop()
{
	delayBuffer[writeDelayIndex++] = buffer[writeIndex++];
	writeIndex %= bufferSize;
	writeDelayIndex %= delayBuffer.size();
	readDelayIndex = writeDelayIndex - delayTimeInSamples;
	readDelayIndex = readDelayIndex < 0 ? readDelayIndex + delayBuffer.size() : readDelayIndex;
	poppedSample = delayBuffer[readDelayIndex];
	return poppedSample;
}
