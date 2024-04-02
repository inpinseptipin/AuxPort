/*
  ==============================================================================

    CustomTextEditor.cpp
    Created: 2 Apr 2024 1:27:58am
    Author:  Nitin Rawat

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomTextEditor.h"

//==============================================================================
CustomTextEditor::CustomTextEditor()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomTextEditor::~CustomTextEditor()
{
    setLookAndFeel(nullptr);
}

void CustomTextEditor::setFillBackgroundFunction(std::function<void(juce::Graphics&, int, int, juce::TextEditor&)> fillBackgroundFunction)
{
    editorLookAndFeel.fillBackgroundFunction = fillBackgroundFunction;
    setLookAndFeel(&editorLookAndFeel);
}

void CustomTextEditor::setOutlineDrawFunction(std::function<void(juce::Graphics&, int, int, juce::TextEditor&)> outlineDrawFunction)
{
    editorLookAndFeel.outlineDrawFunction = outlineDrawFunction;
    setLookAndFeel(&editorLookAndFeel);
}

void CustomTextEditor::CustomLookAndFeel::fillTextEditorBackground(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
{
    if (fillBackgroundFunction)
        fillBackgroundFunction(g, width, height, textEditor);
}

void CustomTextEditor::CustomLookAndFeel::drawTextEditorOutline(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
{
    if (outlineDrawFunction)
        outlineDrawFunction(g, width, height, textEditor);
}
