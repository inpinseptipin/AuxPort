# JUCE Custom Text Editor Extension

``CustomTextEditor`` is a subclass of the JUCE `TextEditor` component that allow to draw custom Text Editors. This class allows users to implement their own drawing logic for the text editor, enabling them to create highly customized text editing components.

## Usage
To use ``CustomTextEditor`` in your JUCE project, follow these steps:
- Add the extension files to your project.
- Include `CustomTextEditor.h` in your source file.

## Documentation
The ``CustomTextEditor`` class allows users to specify custom drawing logic for the text editor. This customization is achieved through two functions:
- `setFillBackgroundFunction()`: Allows users to specify the drawing logic for the text editor background.
- `setOutlineDrawFunction()`: Allows users to specify the drawing logic for the text editor outline.

### `setFillBackgroundFunction()`
To specify the drawing logic for the text editor background, use the `setFillBackgroundFunction()` method to provide a lambda or function with the following signature:
```cpp
void fillBackgroundFunction(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
```
The following parameters are passed to the provided function while drawing the editor:
- `g`: The graphics context used for drawing the text editor background.
- `width`, `height`: The width and height of the text editor.
- `textEditor`: Reference to the text editor being draw.

### `setOutlineDrawFunction()`
To specify the drawing logic for the text editor's outline, use the `setOutlineDrawFunction()` method to provide a lambda or function with the following signature:
```cpp
void outlineDrawFunction(juce::Graphics& g, int width, int height, juce::TextEditor& textEditor))
```
The following parameters are passed to the provided function while drawing the editor:
- `g`: The graphics context used for drawing the text editor background.
- `width`, `height`: The width and height of the text editor.
- `textEditor`: Reference to the text editor being draw.

**Note** : If no custom draw functions are set, the default look and feel of `juce::TextEditor` will be used. Also, if a custom fillBackgroundFunction is specified, then custom outlineDrawFunction also need to be specified for outline to be drawn on screen.


## Example Usage
``` C++
#include "CustomTextEditor.h"
.
.
.
// Create a CustomTextEditor instance
CustomTextEditor customTextEditor;
.
.
.
// Specify the drawing logic for the custom text editor background
customTextEditor.setFillBackgroundFunction(
    [](juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
    {
        // Custom background drawing logic here
    }
);
// Specify the drawing logic for the custom text editor outline
customTextEditor.setOutlineDrawFunction(
    [](juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
    {
        // Custom outline drawing logic here
    }
);
.
.
.
// Use like any other juce::TextEditor component
customTextEditor.setBounds(100, 100, 200, 50);
```