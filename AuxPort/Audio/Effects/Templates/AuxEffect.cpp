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
	AuxAssert(midiNote >= 0, "Invalid Midi Note");
	return referenceFrequency * std::powf(2, (static_cast<float>(midiNote) - referenceMidiNote) / 12.0f);
}

void AuxPort::Audio::Synthesizer::configureMidiToFreq(uint32_t midiNote, float frequency)
{
	AuxAssert(midiNote >= 0 && midiNote < 128, "Invalid reference Midinote");
	AuxAssert(frequency > 0 && frequency < 20000, "Invalid reference frequency");
	AuxAssert(frequency * std::powf(2, (static_cast<float>(0) - midiNote) / 12.0f > 0), "Invalid reference midi and frequency combination");
	AuxAssert(frequency * std::powf(2, (static_cast<float>(127) - midiNote) / 12.0f < 20000), "Invalid reference midi and frequency combination");
	this->referenceFrequency = frequency;
	this->referenceMidiNote = midiNote;

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

void AuxPort::Audio::DelayTuner::findDelayPeak()
{
	for (uint32_t i = 0; i < delayTunerBuffers.size(); i++)
	{
		std::fill(delayTunerBuffers[i].begin(), delayTunerBuffers[i].end(), 0.0f);
		delayTunerBuffers[i][0] = 1;
		if (parallelBlockVector[i] != nullptr)
			parallelBlockVector[i]();
		AuxPort::Utility::abs(delayTunerBuffers[i]);
		float maxValue = AuxPort::Utility::getMax<float>(delayTunerBuffers[i]);
		delayValues[i] = AuxPort::Utility::search<float>(delayTunerBuffers[i], maxValue);
	}
}

void AuxPort::Audio::DelayTuner::setNumberOfBlocks(int n)
{
	AuxAssert(n > 0, "Number of blocks cannot be negative");
	delayTunerBuffers.resize(n);
	parallelBlockVector.resize(n);
	delayValues.resize(n);
}

void AuxPort::Audio::DelayTuner::setBlockBufferSize(size_t blockSize)
{
	AuxAssert(blockSize > 0 && blockSize < 8192, "Please input a sensible block Size");
	for (uint32_t i = 0; i < delayTunerBuffers.size(); i++)
		delayTunerBuffers[i].resize(blockSize);
}
