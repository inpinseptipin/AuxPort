/*
  ==============================================================================

    CustomButton.cpp
    Created: 2 Apr 2024 1:27:07am
    Author:  Nitin Rawat

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomButton.h"

//==============================================================================
CustomButton::CustomButton()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomButton::~CustomButton()
{
    setLookAndFeel(nullptr);
}

void CustomButton::setBackgroundDrawFunction(std::function<void(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool)> backgroundDrawFunction)
{
    buttonLookAndFeel.backgroundDrawFunction = backgroundDrawFunction;
    setLookAndFeel(&buttonLookAndFeel);
}

void CustomButton::setTextDrawFunction(std::function<void(juce::Graphics&, juce::TextButton&, bool, bool)> textDrawFunction)
{
    buttonLookAndFeel.textDrawFunction = textDrawFunction;
    setLookAndFeel(&buttonLookAndFeel);
}

void CustomButton::CustomLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOver, bool isButtonDown)
{
    if(backgroundDrawFunction)
        backgroundDrawFunction(g, button, backgroundColour, isMouseOver, isButtonDown);
}

void CustomButton::CustomLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown)
{
    if(textDrawFunction)
        textDrawFunction(g, button, isMouseOver, isButtonDown);
}
