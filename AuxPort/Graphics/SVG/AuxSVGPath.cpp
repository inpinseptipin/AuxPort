#include "AuxSVGPath.h"

void AuxPort::Graphics::SVG::Path::generateString()
{
    svgString = "<path d=\"";
    
    // Add main path commands
    for (uint32_t i = 0; i < commands.size(); i++)
    {
        svgString += commands[i] + " ";
    }
    
    // Add subpath commands
    for (uint32_t i = 0; i < subPaths.size(); i++)
    {
        for (uint32_t j = 0; j < subPaths[i].commands.size(); j++)
        {
            svgString += subPaths[i].commands[j] + " ";
        }
    }
    
    // Close the `d` attribute
    svgString += "\"";
    
    // Add stroke and fill attributes
    svgString += " stroke=\"" + strokeColour.getSVGString() + "\"";
    svgString += " fill=\"" + fillColour.getSVGString() + "\"";
    svgString += " />";    
}

void AuxPort::Graphics::SVG::Path::moveTo(float x, float y)
{
    commands.push_back("M " + std::to_string(x) + " " + std::to_string(y));
}

void AuxPort::Graphics::SVG::Path::lineTo(float x, float y)
{
    assertInitializedPath();
    commands.push_back("L " + std::to_string(x) + " " + std::to_string(y));
}

void AuxPort::Graphics::SVG::Path::closePath()
{
    assertInitializedPath();
    commands.push_back("Z");
}

void AuxPort::Graphics::SVG::Path::addSubPath(const Path& subPath)
{
    // No need to assert here; subpaths can be independent
    // If subpath is empty, it will be handled in generateString. No commands will be added.
    subPaths.push_back(subPath);
}

void AuxPort::Graphics::SVG::Path::assertInitializedPath()
{
    // A path must start with a moveTo command
    // Reference: https://www.w3.org/TR/SVG2/paths.html#PathDataMovetoCommands
    AuxAssert(!commands.empty() && commands[0][0] == 'M', "Path must be initialized with moveTo before adding other commands.");
}

void AuxPort::Graphics::SVG::Path::setStroke(const Colour& colour)
{
    strokeColour = colour;
}

void AuxPort::Graphics::SVG::Path::setFill(const Colour& colour)
{
    fillColour = colour;
}
