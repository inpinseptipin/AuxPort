#include "AuxParam.h"

void AuxPort::Extensions::ParameterMap::addAudioProcessor(juce::AudioProcessor* audioProcessor)
{
	this->audioProcessor = audioProcessor;
}

void AuxPort::Extensions::ParameterMap::addParameter(juce::AudioProcessorParameter* parameter)
{
	AuxAssert(audioProcessor != nullptr, "No Audio Processor is linked to the Parameter Map");
	AuxAssert(parameter != nullptr, "Parameter can't be a nullptr");
	auto hostedParam = dynamic_cast<juce::HostedAudioProcessorParameter*>(parameter);
	AuxAssert(parameters.find(hostedParam->getParameterID().toStdString()) == parameters.end(),"Parameter with that ID already exists");
	audioProcessor->addParameter(parameter);
	std::pair<std::string, uint32_t> pair;
	pair.first = hostedParam->getParameterID().toStdString();
	pair.second = audioProcessor->getParameters().size() - 1;
	parameters.insert(pair);
}

juce::AudioParameterFloat* AuxPort::Extensions::ParameterMap::getFloatParameter(const std::string& parameterID)
{
	return static_cast<juce::AudioParameterFloat*>(getParameter(parameterID));
}

juce::AudioParameterInt* AuxPort::Extensions::ParameterMap::getIntParameter(const std::string& parameterID)
{
	return static_cast<juce::AudioParameterInt*>(getParameter(parameterID));
}

juce::AudioParameterBool* AuxPort::Extensions::ParameterMap::getBoolParameter(const std::string& parameterID)
{
	return static_cast<juce::AudioParameterBool*>(getParameter(parameterID));
}

juce::AudioParameterChoice* AuxPort::Extensions::ParameterMap::getChoiceParameter(const std::string& parameterID)
{
	return static_cast<juce::AudioParameterChoice*>(getParameter(parameterID));
}

void AuxPort::Extensions::ParameterMap::getStateInformation(juce::MemoryBlock& destData)
{
	auto juceParameters = audioProcessor->getParameters();
	auto stream = juce::MemoryOutputStream(destData, true);
	for (uint32_t i = 0; i < juceParameters.size(); i++)
	{
		auto value = juceParameters.getUnchecked(i)->getValue();
		stream.writeFloat(value);
	}
}

void AuxPort::Extensions::ParameterMap::setStateInformation(const void* data, int sizeInBytes)
{
	auto juceParameters = audioProcessor->getParameters();
	auto stream = juce::MemoryInputStream(data, static_cast<size_t>(sizeInBytes), true);
	for (uint32_t i = 0; i < juceParameters.size(); i++)
	{
		auto value = stream.readFloat();
		juceParameters.getUnchecked(i)->setValue(value);
	}
}

juce::AudioProcessorParameter* AuxPort::Extensions::ParameterMap::getParameter(const std::string& parameterID)
{
	auto parameter = parameters.find(parameterID);
	AuxAssert(parameter != parameters.end(), "Parameter ID does not exist in the map");
	return audioProcessor->getParameters().getUnchecked(parameter->second);
}
