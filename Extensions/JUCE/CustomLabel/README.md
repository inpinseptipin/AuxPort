# JUCE Custom Label Extension

`CustomLabel` is a subclass of the JUCE `Label` component that enhances the functionality of the standard JUCE Label by providing the ability to set custom draw functions. This class allows users to implement their own drawing logic for the label, enabling them to create highly customized text labels.

## Usage
To use `CustomLabel` in your JUCE project, follow these steps:
- Add the extension files to your project.
- Include `CustomLabel.h` in your source file.

## Documentation
The `CustomLabel` class allows users to specify custom drawing logic for the label. This customization is achieved through the `setLabelDrawFunction()` method.

### `setLabelDrawFunction()`
To specify the drawing logic for the label, use the `setLabelDrawFunction()` method to provide a lambda or function with the following signature:
```cpp
void labelDrawFunction(juce::Graphics& g, juce::Label& label)
```
The following parameters are passed to the provided function while drawing the button:
- `g`: The graphics context used for drawing the label.
- `label`: Reference to the label being drawn.

**Note** : If no custom draw functions are set, the default look and feel of `juce::Label` will be used.

## Example Usage
``` C++
#include "CustomLabel.h"
.
.
.
// Create a CustomLabel instance
CustomLabel customLabel;
.
.
.
// Specify the drawing logic for the custom label
customLabel.setLabelDrawFunction(
    [](juce::Graphics& g, juce::Label& label)
    {
        // Custom label drawing logic here
    }
);
.
.
.
// Use like any other juce::Label component
customLabel.setText("Custom Label");
customLabel.setBounds(100, 100, 200, 50);

```