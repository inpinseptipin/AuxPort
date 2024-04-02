/*
  ==============================================================================

    CustomLabel.h
    Created: 2 Apr 2024 9:25:45pm
    Author:  Deepak Chauhan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomLabel  : public juce::Label
{
public:
    CustomLabel();
    ~CustomLabel() override;

    void setLabelDrawFunction(std::function<void(juce::Graphics&, juce::Label&)> labelDrawFunction);
private:
    class CustomLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void drawLabel(juce::Graphics& g, juce::Label& label) override;

        std::function<void(juce::Graphics&, juce::Label&)> labelDrawFunction;
    };
    CustomLookAndFeel labelLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLabel)
};
