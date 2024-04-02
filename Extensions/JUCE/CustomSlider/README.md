# JUCE Custom Slider Extension
``CustomSlider`` is a subclass of the JUCE Slider component that allows creating custom sliders. This class extends the functionality of the standard JUCE Slider by providing the ability to set a custom draw function, enabling users to implement their own drawing logic for the slider.

## Usage
To use ``CustomSlider`` in your project, follow the following steps:
- Add the extension files to your project
- Include ``CustomSlider.h`` in your source file.

## Documentation
The ``CustomSlider`` class allows the user to specify how the slider will be drawn. This allows to create sliders customized to suit one's need. Apart from this, ``CustomSlider`` class is used just like JUCE Slider class.

### ``setSliderDrawFunction()``
To specify the drawing logic for customized slider, one needs to use setSliderDrawFunction() to specify a lambda (or function) which will be used to draw the slider on screen. The slider draw function passed should have the following signature:

```cpp
void sliderDrawFunction(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle)
```
The following parameters are passed to the provided function while drawing the button:
- ``g``: The graphics context that will be used for drawing the slider.
- ``x, y``: The top-left corner coordinates of the slider.
- ``width, height``: The width and height of the slider.
- ``sliderPos``: The current position of the slider (normalized from 0.0 to 1.0).
- ``rotaryStartAngle, rotaryEndAngle``: The start and end angles for rotary sliders (in radians).

The slider draw function will be called internally to draw the slider.  It works similar to drawRotarySlider() function of juce::LookAndFeel_V4. The graphics context and other parameters will be passed to the function. One can use this function to implement custom drawing logic for the slider.

**Note**: If not slider draw function is set, then the default look and feel of `juce::Slider` will be used.

## Example Usage
``` C++
#include "CustomSlider.h"
.
.
.
.
// Create a CustomSlider Instance
CustomSlider customSlider;
.
.
.
// Specify the drawing logic for the custom slider
customSlider.setSliderDrawFunction(
    [](juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle)
    {
        float diameter = juce::jmin(width, height);
        float radius = diameter / 2;
        float centerX = x + width / 2;
        float centerY = y + height / 2;

        juce::Rectangle<float> sliderArea(centerX - radius, centerY - radius, diameter, diameter);
        g.setColour(juce::Colours::grey);
        g.fillEllipse(sliderArea);

        float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        juce::Path knob;
        knob.addRectangle(centerX, centerY - radius, 5, 12);
        g.setColour(juce::Colour::fromRGB(119, 158, 158));
        g.fillPath(knob, juce::AffineTransform::rotation(angle, centerX, centerY));
    }
)
.
.
.
// Use like any other juce::Slider component
customSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
customSlider.setRange(-255.0, 255.0);
customSlider.setValue(0.0);

```