#include "AuxSVGText.h"

AuxPort::Graphics::SVG::Text::Text(const std::string& text, float fontSize, float startX, float startY)
{
	this->text = text;
	this->fontSize = fontSize;
	this->startX = startX;
	this->startY = startY;
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

