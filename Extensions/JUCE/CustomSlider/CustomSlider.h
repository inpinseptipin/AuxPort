/*
  ==============================================================================

    CustomSlider.h
    Created: 30 Mar 2024 2:12:26am
    Author:  Nitin Rawat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
/**
Sub-class to juce::Slider which allows to create Sliders using custom draws.
*/
class CustomSlider  : public juce::Slider
{
public:
    CustomSlider();
    ~CustomSlider() override;

    /**
     * Sets the function which will be used to draw the slider.
     * If unset, the default look and feel of juce::Slider will be used.
     *
     * @param customDrawFunction - A function pointer or lambda that will be used to draw the slider.
     * The custom draw function should have the following signature:
     * void customDrawFunction(juce::Graphics& g, int x, int y, int width, int height,
     *                         float sliderPos, float rotaryStartAngle, float rotaryEndAngle)
     * - g: The graphics context that will be used for drawing the slider.
     * - x, y: The top-left corner coordinates of the slider.
     * - width, height: The width and height of the slider.
     * - sliderPos: The current position of the slider (normalized from 0.0 to 1.0).
     * - rotaryStartAngle, rotaryEndAngle: The start and end angles for rotary sliders (in radians).
     *
     * The custom draw function will be called internally to draw the slider. 
     * It works similar to drawRotarySlider() function of juce::LookAndFeel_V4.
     * The graphics context and other parameters will be passed to the function. One can use this function to implement 
     * custom drawing logic for the slider.
     */
    void setCustomDrawFunction(std::function<void(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle)> customDrawFunction);
private:
    class CustomLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;
        std::function<void(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle)> customDrawFunction;
    };
    CustomLookAndFeel sliderLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};
