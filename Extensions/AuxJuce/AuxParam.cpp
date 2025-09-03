#include "AuxParam.h"

void AuxPort::Extensions::ParameterMap::addAudioProcessor(juce::AudioProcessor* audioProcessor)
{
	this->audioProcessor = audioProcessor;
}

void AuxPort::Extensions::ParameterMap::addParameter(juce::AudioProcessorParameter* parameter, PType ptype)
{
	AuxAssert(audioProcessor != nullptr, "No Audio Processor is linked to the Parameter Map");
	AuxAssert(parameter != nullptr, "Parameter can't be a nullptr");

	std::pair<std::string, uint32_t> parameterPair;
	auto hostedParam = dynamic_cast<juce::HostedAudioProcessorParameter*>(parameter);
	AuxAssert(parameters.find(hostedParam->getParameterID().toStdString()) == parameters.end(), "Parameter with that ID already exists");
	audioProcessor->addParameter(parameter);
	parameterPair.first = hostedParam->getParameterID().toStdString();
	parameterPair.second = audioProcessor->getParameters().size() - 1;
	parameters.insert(parameterPair);



	std::pair<std::string, ParameterData> parameterDataPair;
	if (ptype == PType::Boolean)
	{
		auto boolParam = dynamic_cast<juce::AudioParameterBool*>(parameter);
		parameterDataPair.second.maxValue = 1.0f;
		parameterDataPair.second.minValue = 0.0f;
		parameterDataPair.second.interval = 1.0f;
		parameterDataPair.first = boolParam->getParameterID().toStdString();
	}
	else if (ptype == PType::Choice)
	{
		auto choiceParam = dynamic_cast<juce::AudioParameterChoice*>(parameter);
		parameterDataPair.second.maxValue = choiceParam->choices.size();
		parameterDataPair.second.minValue = 0.0f;
		parameterDataPair.second.interval = 1.0f;
		parameterDataPair.first = choiceParam->getParameterID().toStdString();
	}
	else if (ptype == PType::Floating)
	{
		auto floatParam = dynamic_cast<juce::AudioParameterFloat*>(parameter);
		parameterDataPair.second.maxValue = floatParam->getNormalisableRange().end;
		parameterDataPair.second.minValue = floatParam->getNormalisableRange().start;
		parameterDataPair.second.interval = floatParam->getNormalisableRange().interval;
		parameterDataPair.first = floatParam->getParameterID().toStdString();
	}
	else if (ptype == PType::Integer)
	{
		auto integerParam = dynamic_cast<juce::AudioParameterInt*>(parameter);
		parameterDataPair.second.maxValue = integerParam->getNormalisableRange().end;
		parameterDataPair.second.minValue = integerParam->getNormalisableRange().start;
		parameterDataPair.second.interval = integerParam->getNormalisableRange().interval;
		parameterDataPair.first = integerParam->getParameterID().toStdString();
	}
	parameterDataMap.insert(parameterDataPair);

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

void AuxPort::Extensions::ParameterMap::saveToFile(const std::string& fileName)
{
	csv.reset(new AuxPort::CSV());
	csv->open(fileName, AuxPort::File::Mode::Write, true);
	csv->setHeader({ "Parameter","Raw Value","Normalized Value","Normalized Max","Normalized Min"});
	auto juceParameters = audioProcessor->getParameters();
	for (auto i = parameters.begin(); i != parameters.end(); i++)
	{
		auto parameter = juceParameters[i->second];
		auto data = parameterDataMap.at(i->first);
		auto rawValue = parameter->getValue();
		auto currentNormalizedValue = AuxPort::Utility::remap<float>(rawValue, data.minValue, data.maxValue, 0, 1);
		csv->addDataRow({ i->first,std::to_string(rawValue),std::to_string(currentNormalizedValue),std::to_string(data.maxValue),std::to_string(data.minValue),std::to_string(data.interval)});
	}
	csv->write();
	csv->close();
	csv.reset();
}

void AuxPort::Extensions::ParameterMap::readFromFile(const std::string& fileName)
{
	csv.reset(new AuxPort::CSV());
	csv->open(fileName, AuxPort::File::Mode::Read, true);
	std::vector<std::vector<std::string>> data;
	std::vector<std::string> header;
	csv->read(data, header);
	auto juceParameters = audioProcessor->getParameters();
	for (uint32_t i = 0; i < data.size(); i++)
	{
		juceParameters[parameters.at(data[i][0])]->setValue(stof(data[i][1]));
	}
	csv->close();
	if (updatePluginUI != nullptr)
		updatePluginUI();
	csv.release();
}

juce::AudioProcessorParameter* AuxPort::Extensions::ParameterMap::getParameter(const std::string& parameterID)
{
	auto parameter = parameters.find(parameterID);
	AuxAssert(parameter != parameters.end(), "Parameter ID does not exist in the map");
	return audioProcessor->getParameters().getUnchecked(parameter->second);
}

AuxPort::Extensions::PresetMenu::PresetMenu()
{
	addAndMakeVisible(label);
	label.setEditable(true);
	label.setText("No Preset Selected", juce::dontSendNotification);
	label.setJustificationType(juce::Justification::horizontallyCentred);
	label.setFont(juce::Font(16, 1));

	addAndMakeVisible(loadPresetButton);
	loadPresetButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
	loadPresetButton.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::blueviolet);
	loadPresetButton.setButtonText("Load Preset");
	loadPresetButton.onClick = [this]
		{
			fileChooser = std::make_unique<juce::FileChooser>("Load Preset", juce::File(), "*." + presetExtension, true, false, nullptr);
			fileChooser->launchAsync(juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::openMode, [this](const juce::FileChooser& chooser)
				{
					if (chooser.getResults().size() > 0)
					{
						parameterMap->readFromFile(chooser.getResult().getFullPathName().toStdString());
						label.setText(chooser.getResult().getFileNameWithoutExtension(), juce::dontSendNotification);
						if(updatePluginUI != nullptr)
							updatePluginUI();
					}
				});
		};

	addAndMakeVisible(savePresetButton);
	savePresetButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
	savePresetButton.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::blueviolet);
	savePresetButton.setButtonText("Save Preset");

	savePresetButton.onClick = [this]
		{
			
			fileChooser = std::make_unique<juce::FileChooser>("Save Preset", juce::File(), "*." + presetExtension, true, false, nullptr);
			fileChooser->launchAsync(juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::saveMode, [this](const juce::FileChooser& chooser)
				{
					if (chooser.getResults().size() > 0)
					{
						parameterMap->saveToFile(chooser.getResult().getFullPathName().toStdString());
					}
				});
			
		};

}

AuxPort::Extensions::PresetMenu::~PresetMenu()
{
}

void AuxPort::Extensions::PresetMenu::handleParameterMap(AuxPort::Extensions::ParameterMap* parameterMap)
{
	this->parameterMap = parameterMap;
}

void AuxPort::Extensions::PresetMenu::paint(juce::Graphics& g)
{
	g.fillAll(juce::Colours::transparentBlack);
	g.setColour(juce::Colours::white);
	g.drawRoundedRectangle(this->getLocalBounds().toFloat(), 5, 5);
}

void AuxPort::Extensions::PresetMenu::resized()
{
	auto x = this->getLocalBounds().getWidth();
	auto y = this->getLocalBounds().getHeight();

	loadPresetButton.setBounds(0, 0, x, 0.33 * y);
	label.setBounds(0, 0.33*y, x, 0.33 * y);
	savePresetButton.setBounds(0, 0.66 * y, x, 0.33 * y);
}

void AuxPort::Extensions::PresetMenu::setPresetExtension(const std::string& presetExtension)
{
	this->presetExtension = presetExtension;
}


