#include "AuxDelay.h"

AuxPort::Audio::Delay::Delay() : CircularBufferEngine()
{
	delayTime = 0.0f;
	delayTimeInSamples = 0;
	sampleRate = 44100;
	writeDelayIndex = 0;
	readDelayIndex = 0;
	maxDelayTime = 0;
}

void AuxPort::Audio::Delay::setMaxDelayTime(size_t sampleRate, float maxDelayTime)
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
		this->delayTimeInSamples = static_cast<size_t>(delayTime * sampleRate);
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
	readDelayIndex = writeDelayIndex - static_cast<int>(delayTimeInSamples);
	readDelayIndex = readDelayIndex < 0 ? readDelayIndex + static_cast<int>(delayBuffer.size()) : readDelayIndex;
	poppedSample = delayBuffer[readDelayIndex];
	return poppedSample;
}
