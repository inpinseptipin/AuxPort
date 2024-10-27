#include "AuxSynth.h"

float AuxPort::Extensions::Synthesizer::midiToFreq(uint32_t midiNote)
{
	return 440 * std::powf(2, (static_cast<float>(midiNote) - 69) / 12.0f);
}

void AuxPort::Extensions::JuceSynthesizer::process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer)
{
	auto currentSample = 0;
	for (const auto midi : midiBuffer)
	{
		auto message = midi.getMessage();
		auto messagePosition = static_cast<int32_t>(message.getTimeStamp());
		render(buffer, currentSample, messagePosition);
		currentSample = messagePosition;
		handleMidiEvent(message);
	}
	render(buffer, currentSample, buffer.getNumSamples());
}

void AuxPort::Extensions::JuceSynthesizer::attachParameterMap(AuxPort::Extensions::ParameterMap* parameterMap)
{
	this->parameterMap = parameterMap;
}
