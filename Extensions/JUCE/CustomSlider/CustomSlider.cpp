/*
  ==============================================================================

    CustomSlider.cpp
    Created: 30 Mar 2024 2:12:26am
    Author:  Nitin Rawat

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomSlider.h"

//==============================================================================
CustomSlider::CustomSlider()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

CustomSlider::~CustomSlider()
{
    setLookAndFeel(nullptr);
}

void CustomSlider::setSliderDrawFunction(std::function<void(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle)> sliderDrawFunction)
{
    sliderLookAndFeel.sliderDrawFunction = sliderDrawFunction;
    setLookAndFeel(&sliderLookAndFeel);
}

void CustomSlider::CustomLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider)
{
    if(sliderDrawFunction)
        sliderDrawFunction(g, x, y, width, height, sliderPos, rotaryStartAngle, rotaryEndAngle);
}