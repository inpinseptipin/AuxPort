#include "AuxParam.h"

AuxPort::Extensions::ParameterMap::Parameter::Parameter(size_t index, const AuxPort::Extensions::ParameterMap::type& paramType, const std::string& paramName)
{
	parameterPosition = index;
	this->parameterType = paramType;
	this->parameterName = paramName;
}

std::string AuxPort::Extensions::ParameterMap::Parameter::getParameterName()
{
	return parameterName;
}

uint32_t AuxPort::Extensions::ParameterMap::Parameter::getParameterPosition()
{
	return parameterPosition;
}

AuxPort::Extensions::ParameterMap::type AuxPort::Extensions::ParameterMap::Parameter::getParameterType()
{
	return parameterType;
}



AuxPort::Extensions::ParameterMap::ParameterMap(juce::AudioProcessor* audioProcessor)
{
	this->audioProcessor = audioProcessor;
}

void AuxPort::Extensions::ParameterMap::addParameter(juce::AudioParameterBool* boolParam)
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxAssert(map[i].getParameterName() != boolParam->name, "A Parameter with that name already exists");
	}
	boolParameters.push_back(boolParam);
	map.push_back({ boolParameters.size() - 1,AuxPort::Extensions::ParameterMap::type::aBool,boolParam->name.toStdString()});
}

void AuxPort::Extensions::ParameterMap::addParameter(juce::AudioParameterFloat* floatParam)
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxAssert(map[i].getParameterName() != floatParam->name, "A Parameter with that name already exists");
	}
	floatParameters.push_back(floatParam);
	map.push_back({ floatParameters.size() - 1,AuxPort::Extensions::ParameterMap::type::aFloat,floatParam->name.toStdString() });
}

void AuxPort::Extensions::ParameterMap::addParameter(juce::AudioParameterInt* intParam)
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxAssert(map[i].getParameterName() != intParam->name, "A Parameter with that name already exists");
	}
	intParameters.push_back(intParam);
	map.push_back({ intParameters.size() - 1,AuxPort::Extensions::ParameterMap::type::aInt,intParam->name.toStdString()});
}

juce::AudioParameterFloat* AuxPort::Extensions::ParameterMap::getFloatParameter(const std::string& parameterName)
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxPort::Extensions::ParameterMap::Parameter* param = &map[i];
		if (param->getParameterType() == AuxPort::Extensions::ParameterMap::aFloat)
			if (param->getParameterName() == parameterName)
				return floatParameters[param->getParameterPosition()];
	}
}

juce::AudioParameterBool* AuxPort::Extensions::ParameterMap::getBoolParameter(const std::string& parameterName)
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxPort::Extensions::ParameterMap::Parameter* param = &map[i];
		if (param->getParameterType() == AuxPort::Extensions::ParameterMap::aBool)
			if (param->getParameterName() == parameterName)
				return boolParameters[param->getParameterPosition()];
	}
}

juce::AudioParameterInt* AuxPort::Extensions::ParameterMap::getIntParameter(const std::string& parameterName)
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxPort::Extensions::ParameterMap::Parameter* param = &map[i];
		if (param->getParameterType() == AuxPort::Extensions::ParameterMap::aInt)
			if (param->getParameterName() == parameterName)
				return intParameters[param->getParameterPosition()];
	}
}



void AuxPort::Extensions::ParameterMap::save()
{
	for (uint32_t i = 0; i < map.size(); i++)
	{
		AuxPort::Extensions::ParameterMap::Parameter* param = &map[i];
		if (param->getParameterType() == AuxPort::Extensions::ParameterMap::aBool)
		{
			audioProcessor->addParameter(boolParameters[param->getParameterPosition()]);
		}
		if (param->getParameterType() == AuxPort::Extensions::ParameterMap::aFloat)
		{
			audioProcessor->addParameter(floatParameters[param->getParameterPosition()]);
		}
		if (param->getParameterType() == AuxPort::Extensions::ParameterMap::aInt)
		{
			audioProcessor->addParameter(intParameters[param->getParameterPosition()]);
		}
	}
}
