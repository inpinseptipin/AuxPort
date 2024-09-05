#include "AuxEffect.h"

void AuxPort::Audio::Effect::setSampleRate(uint32 sampleRate)
{
	this->sampleRate = sampleRate;
}

void AuxPort::Audio::Effect::setParameters(const std::vector<float>& parameters)
{
	this->parameters = parameters;
}

void AuxPort::Audio::Effect::process(std::vector<float>& buffer)
{
	timer.start();
	processBlock(buffer);
	timer.stop();
	benchmarkBlock(timer.getEllapsedTime());
	analysisBlock(buffer);
}
