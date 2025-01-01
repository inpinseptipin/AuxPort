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
