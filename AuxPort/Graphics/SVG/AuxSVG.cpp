#include "AuxSVG.h"

AuxPort::Graphics::SVG::SVG::SVG()
{
	svgData.clear();
}

void AuxPort::Graphics::SVG::SVG::addBackground(AuxPort::Graphics::SVG::Colour& colour)
{
	backgroundData.clear();
	colour.generateString();
	backgroundData += "<rect width=\"100%\" height=\"100%\" fill=" + colour.getSVGString() + "/>";
}

void AuxPort::Graphics::SVG::SVG::addText(const std::string& text, float startX, float startY, float fontSize)
{
	textData.push_back("<text x=\"" + std::to_string(startX) + "\" y=\"" + std::to_string(startY) + "\"" + ">" + text + "</text>");
}

void AuxPort::Graphics::SVG::SVG::addText(AuxPort::Graphics::SVG::Text& text)
{
	text.generateString();
	textData.push_back(text.getSVGString());
}

void AuxPort::Graphics::SVG::SVG::save()
{
	svgData += "<svg width=\"800\" height=\"300\"  xmlns=\"http://www.w3.org/2000/svg\">";
	svgData += backgroundData;
	for (uint32_t i = 0;i < textData.size();i++)
		svgData += textData[i];
	svgData += "</svg>";
	writeLineToFile(svgData);
	this->close();
}

AuxPort::Graphics::SVG::Colour::Colour()
{
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

AuxPort::Graphics::SVG::Colour::Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

uint8_t AuxPort::Graphics::SVG::Colour::getRed()
{
	return red;
}

uint8_t AuxPort::Graphics::SVG::Colour::getGreen()
{
	return green;
}

uint8_t AuxPort::Graphics::SVG::Colour::getBlue()
{
	return blue;
}

uint8_t AuxPort::Graphics::SVG::Colour::getAlpha()
{
	return alpha;
}

void AuxPort::Graphics::SVG::Colour::setColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

void AuxPort::Graphics::SVG::Colour::generateString()
{
	svgString.clear();
	svgString += "\"rgba(" + std::to_string(red) + "," + std::to_string(green) + "," + std::to_string(blue) + "," + std::to_string(alpha) + ")\" ";
}

void AuxPort::Graphics::SVG::Text::setText(const std::string& text)
{
	this->text = text;
}

void AuxPort::Graphics::SVG::Text::setFontSize(float fontSize)
{
	this->fontSize = fontSize;
}

void AuxPort::Graphics::SVG::Text::setXY(float startX, float startY)
{
	this->startX = startX;
	this->startY = startY;
}

void AuxPort::Graphics::SVG::Text::setFill(const Colour& fillColour)
{
	this->fillColour = fillColour;
}

void AuxPort::Graphics::SVG::Text::setStroke(const Colour& strokeColour)
{
	this->strokeColour = strokeColour;
}

void AuxPort::Graphics::SVG::Text::generateString()
{
	svgString.clear();
	strokeColour.generateString();
	fillColour.generateString();
	svgString += "<text";
	svgString += valueToString("x", startX);
	svgString += valueToString("y", startY);
	svgString += "fill=" + fillColour.getSVGString();
	svgString += "stroke=" + strokeColour.getSVGString();
	svgString += ">";
	svgString += text;
	svgString += "</text>";
}

std::string& AuxPort::Graphics::SVG::SVGObject::getSVGString()
{
	return svgString;
}

std::string AuxPort::Graphics::SVG::SVGObject::valueToString(const std::string& key, float val)
{
	return " " + key + "=\"" + std::to_string(val) + "\" ";
}
