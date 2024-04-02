/*
  ==============================================================================

    CustomLabel.cpp
    Created: 2 Apr 2024 9:25:45pm
    Author:  Deepak Chauhan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomLabel.h"

//==============================================================================
CustomLabel::CustomLabel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomLabel::~CustomLabel()
{
    setLookAndFeel(nullptr);
}

void CustomLabel::setLabelDrawFunction(std::function<void(juce::Graphics&, juce::Label&)> labelDrawFunction)
{
    labelLookAndFeel.labelDrawFunction = labelDrawFunction;
    setLookAndFeel(&labelLookAndFeel);
}

void CustomLabel::CustomLookAndFeel::drawLabel(juce::Graphics& g, juce::Label& label)
{
    if (labelDrawFunction)
        labelDrawFunction(g, label);
}
