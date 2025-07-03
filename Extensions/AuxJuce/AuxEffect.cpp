#include "AuxEffect.h"

void AuxPort::Extensions::JuceEffect::setParameterNames(const std::vector<std::string>& parameterNames)
{
	this->parameterNames = parameterNames;
}

void AuxPort::Extensions::JuceEffect::handleAudioProcessor(void* audioProcessor)
{
	parameterMap = static_cast<AuxPort::Extensions::ParameterMap*>(audioProcessor);
}

void JuceExamples::Gain::process(juce::AudioBuffer<float>& buffer)
{
	for (uint32_t i = 0;i < buffer.getNumChannels();i++)
		for (uint32_t j = 0;j < buffer.getNumSamples();j++)
			buffer.setSample(i, j, buffer.getSample(i, j) * *parameterMap->getFloatParameter(parameterNames[outputGain]));
}

