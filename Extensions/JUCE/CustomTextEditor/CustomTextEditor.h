/*
  ==============================================================================

    CustomTextEditor.h
    Created: 2 Apr 2024 1:27:58am
    Author:  Nitin Rawat

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomTextEditor  : public juce::TextEditor
{
public:
    CustomTextEditor();
    ~CustomTextEditor() override;

    void setFillBackgroundFunction(std::function<void(juce::Graphics&, int, int, juce::TextEditor&)> fillBackgroundFunction);
    void setOutlineDrawFunction(std::function<void(juce::Graphics&, int, int, juce::TextEditor&)> outlineDrawFunction);
private:
    class CustomLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override;
        void drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor) override;
        
        std::function<void(juce::Graphics&, int, int, juce::TextEditor&)> fillBackgroundFunction;
        std::function<void(juce::Graphics&, int, int, juce::TextEditor&)> outlineDrawFunction;
    };
    CustomLookAndFeel editorLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomTextEditor)
};
