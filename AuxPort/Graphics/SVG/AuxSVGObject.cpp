#include "AuxSVGObject.h"



std::string& AuxPort::Graphics::SVG::SVGObject::getSVGString()
{
	return svgString;
}

std::string AuxPort::Graphics::SVG::SVGObject::valueToString(const std::string& key, float val)
{
	return " " + key + "=\"" + std::to_string(val) + "\" ";
}
