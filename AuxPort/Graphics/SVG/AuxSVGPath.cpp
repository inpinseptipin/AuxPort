#include "AuxSVGPath.h"

void AuxPort::Graphics::SVG::Path::generateString()
{
    svgString = "<path d=\"";
    
    // Add main path commands
    for (const auto& command : commands)
    {
        svgString += command + " ";
    }
    
    // Add subpath commands
    for (const auto& subPath : subPaths)
    {
        for (const auto& command : subPath.commands)
        {
            svgString += command + " ";
        }
    }
    
    // Close the `d` attribute
    svgString += "\"";
    
    // Add stroke and fill attributes
    svgString += " stroke=\"" + strokeColour.getSVGString() + "\"";
    svgString += " fill=\"" + fillColour.getSVGString() + "\"";
    svgString += " />";    
}

AuxPort::Graphics::SVG::Path& AuxPort::Graphics::SVG::Path::moveTo(float x, float y)
{
    commands.push_back("M " + std::to_string(x) + " " + std::to_string(y));
    return *this;
}

AuxPort::Graphics::SVG::Path& AuxPort::Graphics::SVG::Path::lineTo(float x, float y)
{
    commands.push_back("L " + std::to_string(x) + " " + std::to_string(y));
    return *this;
}

AuxPort::Graphics::SVG::Path& AuxPort::Graphics::SVG::Path::closePath()
{
    commands.push_back("Z");
    return *this;
}

void AuxPort::Graphics::SVG::Path::addSubPath(const Path& subPath)
{
    subPaths.push_back(subPath);
}

AuxPort::Graphics::SVG::Path& AuxPort::Graphics::SVG::Path::setStroke(const Colour& colour)
{
    strokeColour = colour;
    return *this;
}

AuxPort::Graphics::SVG::Path& AuxPort::Graphics::SVG::Path::setFill(const Colour& colour)
{
    fillColour = colour;
    return *this;
}

