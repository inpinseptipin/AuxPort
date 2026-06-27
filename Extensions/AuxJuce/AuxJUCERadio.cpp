#include "AuxJUCERadio.h"

AuxPort::Extensions::Radio::Radio()
{
}

AuxPort::Extensions::Radio::~Radio()
{
}

void AuxPort::Extensions::Radio::setOptions(const std::vector<juce::String>& optionVector)
{
	AuxAssert(optionVector.size() > 0, "Please provide atleast 1 option");
	for (uint32_t i = 0; i < optionVector.size(); i++)
	{
		std::pair<juce::String, bool> pair;
		pair.first = optionVector[i];
		pair.second = false;
		radioOptions.push_back(pair);
	}
}

void AuxPort::Extensions::Radio::mouseDown(const juce::MouseEvent& mouseEvent)
{
	auto yCoordinate = mouseEvent.getMouseDownY();
	auto bounds = this->getLocalBounds();
	auto location = AuxPort::Utility::remap<float>(yCoordinate, 0, radioOptions.size(), bounds.getY(), bounds.getHeight());
	uint32_t radioLocation = static_cast<uint32_t>(floor(location));

	if (radioOptions.size() > 1)
	{
		if (!radioOptions[radioLocation].second)
			radioOptions[radioLocation].second = !radioOptions[radioLocation].second;
		for (uint32_t i = 0; i < radioOptions.size(); i++)
		{
			if (i != radioLocation)
			{
				radioOptions[i].second = false;
			}
		}
	}
	else
	{
		radioOptions[radioLocation].second = !radioOptions[radioLocation].second;
	}
	
	repaint();
	std::lock_guard lockGuard(mutex);
	if (onChange != nullptr)
		onChange();
}

void AuxPort::Extensions::Radio::paint(juce::Graphics& g)
{
	if (radioOptions.size() > 0)
	{
		auto width = this->getLocalBounds().getWidth();
		auto rowHeight = this->getLocalBounds().getHeight() / radioOptions.size();
		for (uint32_t i = 0; i < radioOptions.size(); i++)
		{
			g.setColour(juce::Colours::black);
			g.drawRect(0, i * rowHeight, width, rowHeight,5);
			radioOptions[i].second == true ? g.setColour(juce::Colours::darkgreen) : g.setColour(juce::Colours::red);
			g.fillRect(0, i * rowHeight, width, rowHeight);
			g.setColour(juce::Colours::white);
			g.drawText(radioOptions[i].first, 0, i * rowHeight, width, rowHeight, juce::Justification::horizontallyCentred);
		}
	}
}

std::vector<std::pair<juce::String, bool>>& AuxPort::Extensions::Radio::getRadioOptionVector()
{
	return radioOptions;
}

void AuxPort::Extensions::Radio::resized()
{

}
