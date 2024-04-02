# JUCE Custom Button Extension
``CustomButton`` is a subclass of the JUCE `TextButton` component that allows to create buttons using custom draw functions. This class allows users to implement their own drawing logic for the button, enabling them to create highly customized buttons.

## Usage
To use ``CustomButton`` in your JUCE project, follow these steps:
- Add the extension files to your project.
- Include `CustomButton.h` in your source file.

## Documentation
The ``CustomButton`` class allows users to specify custom drawing logic for the button. This customization is achieved through two functions:
- `setBackgroundDrawFunction()`: Allows users to specify the drawing logic for the button background.
- `setTextDrawFunction()`: Allows users to specify the drawing logic for the button text.

### `setBackgroundDrawFunction()`
To specify the drawing logic for the button background, use the `setBackgroundDrawFunction()` method to provide a lambda or function with the following signature:
```cpp
void backgroundDrawFunction(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOver, bool isButtonDown)
```
The following parameters are passed to the provided function while drawing the button:
- `g`: The graphics context that will be used for drawing the button.
- `button`: Reference to the button being drawn.
- `backgroundColour`: The background color of the button.
- `isMouseOver`: Indicates whether the mouse is currently over the button.
- `isButtonDown`: Indicates whether the button is currently being pressed.

### `setTextDrawFunction()`
To specify the drawing logic for the button background, use the `setTextDrawFunction()` method to provide a lambda or function with the following signature:
```cpp
void textDrawFunction(juce::Graphics&, juce::Button&, bool, bool)
```
The following parameters are passed to the provided function while drawing the button:
- `g`: The graphics context that will be used for drawing the button.
- `button`: Reference to the button being drawn.
- `isMouseOver`: Indicates whether the mouse is currently over the button.
- `isButtonDown`: Indicates whether the button is currently being pressed.

**Note** : If no custom draw functions are set, the default look and feel of `juce::Button` will be used. Also, if a custom backgroundDrawFunction is specified, then custom textDrawFunction also need to be specified for text to be drawn on screen.

## Example Usage
``` C++
#include "CustomButton.h"
.
.
.
.
// Create a CustomButton Instance
CustomButton customButton;
.
.
.
// Specify the drawing logic for the custom Button's Background
customButton.setBackgroundDrawFunction(
    [](juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOver, bool isButtonDown)
    {
        auto buttonArea = button.getLocalBounds();
        auto edge = 4;
 
        buttonArea.removeFromLeft (edge);
        buttonArea.removeFromTop (edge);
 
        g.setColour (juce::Colours::darkgrey.withAlpha (0.5f));
        g.fillRect (buttonArea);
 
        auto offset = isButtonDown ? -edge / 2 : -edge;
        buttonArea.translate (offset, offset);
 
        g.setColour (backgroundColour);
        g.fillRect (buttonArea);
    }
)

// Specify the drawing logic for the custom Button's Text
customButton.setTextDrawFunction(
    [](juce::Graphics& g, juce::Button& button, bool isMouseOver, bool isButtonDown)
    {
        // Code to draw text upon button
    }
)
.
.
.
// Use like any other juce::Button component
customButton.setButtonText("Click Here");

```