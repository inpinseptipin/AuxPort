#include "AuxSynth.h"

void AuxPort::Extensions::JuceSynthesizer::process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
{
	auto currentSample = 0;
	for (const auto midi : midiBuffer)
	{
		auto message = midi.getMessage();
		auto messagePosition = static_cast<int32_t>(message.getTimeStamp());
		render(buffer, currentSample, messagePosition);
		currentSample = messagePosition;
		handleMidiEvent(static_cast<void*>(&message));
	}
	render(buffer, currentSample, buffer.getNumSamples());
	mix(buffer);
}

void AuxPort::Extensions::JuceSynthesizer::attachParameterMap(AuxPort::Extensions::ParameterMap* parameterMap)
{
	this->parameterMap = parameterMap;
}

void AuxPort::Extensions::JuceSynthesizer::handleMidiEvent(void* midiMessage)
{
	auto message = static_cast<juce::MidiMessage*>(midiMessage);
	if (message->isNoteOn())
	{
		handleNoteOn(midiMessage);
	}
	if (message->isNoteOff())
	{
		handleNoteOff(midiMessage);
	}
	if (message->isAllNotesOff())
	{
		handleAllNotesOff(midiMessage);
	}
}

void AuxPort::Extensions::JuceSynthesizer::copyMonoToAll(juce::AudioBuffer<float>& buffer,uint32_t startSample,uint32_t endSample)
{
	auto firstChannel = buffer.getWritePointer(0);

	for (size_t i = 1; i < buffer.getNumChannels(); i++)
	{
		auto channel = buffer.getWritePointer(i);
		std::copy(firstChannel + startSample, firstChannel + endSample, channel + startSample);
	}
}

void AuxPort::Extensions::JuceSynthesizer::mix(juce::AudioBuffer<float>& buffer)
{
	copyMonoToAll(buffer, 0, buffer.getNumSamples());
}

AuxPort::Extensions::SimplePolyphony::SimplePolyphony()
{
	oscillator.resize(128);
}

void AuxPort::Extensions::SimplePolyphony::setSampleRate(float sampleRate)
{
	this->sampleRate = sampleRate;
	for (uint32_t i = 0; i < oscillator.size(); i++)
	{
		this->oscillator[i].setSampleRate(sampleRate);
	}
}

void AuxPort::Extensions::SimplePolyphony::handleAudioProcessor(void* parameterMap)
{
	this->parameterMap = static_cast<AuxPort::Extensions::ParameterMap*>(parameterMap);
}

void AuxPort::Extensions::SimplePolyphony::render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample)
{
	auto firstChannel = buffer.getWritePointer(0);
	for (uint32_t i = 0; i < oscillator.size(); i++)
	{
		if (oscillator[i].isPlaying())
		{
			for (uint32_t k = startSample; k < endSample; k++)
			{
				firstChannel[k] += oscillator[i].process();
			}
		}
	}
}

void AuxPort::Extensions::SimplePolyphony::handleNoteOn(void* midiMessage)
{
	auto midi = static_cast<juce::MidiMessage*>(midiMessage);
	oscillator[midi->getNoteNumber()].setFrequency(midiToFreq(midi->getNoteNumber()));
}

void AuxPort::Extensions::SimplePolyphony::handleNoteOff(void* midiMessage)
{
	auto midi = static_cast<juce::MidiMessage*>(midiMessage);
	oscillator[midi->getNoteNumber()].stop();
}

void AuxPort::Extensions::SimplePolyphony::handleAllNotesOff(void* midiMessage)
{
	for (uint32_t i = 0; i < oscillator.size(); i++)
		oscillator[i].stop();
}




