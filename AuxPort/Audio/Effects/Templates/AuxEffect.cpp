#include "AuxEffect.h"

void AuxPort::Audio::Effect::setSampleRate(float sampleRate)
{
	this->sampleRate = sampleRate;
}

void AuxPort::Audio::Effect::setParameters(const std::vector<float>& parameters)
{
	this->parameters = parameters;
}

void AuxPort::Audio::MonoEffect::process(float * buffer, uint32_t bufferSize)
{
	AuxAssert(buffer != nullptr, "Buffer cannot be a null pointer, pass a valid audio buffer");
	AuxAssert(bufferSize > 0, "Buffer Size has to be greater than 0");
	timer.start();
	processBlock(buffer,bufferSize);
	timer.stop();
	benchmarkBlock(static_cast<float>(timer.getEllapsedTime()));
	analysisBlock(buffer,bufferSize);
}

void AuxPort::Audio::Effect::handleAudioProcessor(void *audioProcessor)
{
	AuxAssert(1==1,"Implement this with a valid pointer to an audio processor");
}

void AuxPort::Audio::StereoEffect::process(float* leftChannel, float* rightChannel, uint32_t bufferSize)
{
	AuxAssert(leftChannel != nullptr, "Buffer cannot be a null pointer, pass a valid audio buffer");
	AuxAssert(rightChannel != nullptr, "Buffer cannot be a null pointer, pass a valid audio buffer");
	AuxAssert(bufferSize > 0, "Buffer Size has to be greater than 0");
	timer.start();
	processBlock(leftChannel, rightChannel, bufferSize);
	timer.stop();
	benchmarkBlock(static_cast<float>(timer.getEllapsedTime()));
	analysisBlock(leftChannel,rightChannel, bufferSize);
}


float AuxPort::Audio::Synthesizer::midiToFreq(uint32_t midiNote)
{
	return 440 * std::powf(2, (static_cast<float>(midiNote) - 69) / 12.0f);
}

void AuxPort::Audio::Synthesizer::handleMidiEvent(void* midiMessage)
{
	AuxAssert(1 == 1, "Implement this Method");
}

void AuxPort::Audio::Synthesizer::handleNoteOn(void* midiMessage)
{
	AuxAssert(1 == 1, "Implement this Method");
}

void AuxPort::Audio::Synthesizer::handleNoteOff(void* midiMessage)
{
	AuxAssert(1 == 1, "Implement this Method");
}

void AuxPort::Audio::Synthesizer::handleAllNotesOff(void* midiMessage)
{
	AuxAssert(1 == 1, "Implement this Method");
}