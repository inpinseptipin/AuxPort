/*
  ==============================================================================

    CustomButton.h
    Created: 2 Apr 2024 1:27:07am
    Author:  Nitin Rawat

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomButton  : public juce::TextButton
{
public:
    CustomButton();
    ~CustomButton() override;

    void setBackgroundDrawFunction(std::function<void(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool)> backgroundDrawFunction);
    void setTextDrawFunction(std::function<void(juce::Graphics&, juce::TextButton&, bool, bool)> textDrawFunction);
private:
    class CustomLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOver, bool isButtonDown) override;
        void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOver, bool isButtonDown) override;
        
        std::function<void(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool)> backgroundDrawFunction;
        std::function<void(juce::Graphics&, juce::TextButton&, bool, bool)> textDrawFunction;
    };
    CustomLookAndFeel buttonLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomButton)
};
