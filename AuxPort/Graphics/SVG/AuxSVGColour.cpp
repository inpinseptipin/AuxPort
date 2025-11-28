#include "AuxSVGColour.h"

AuxPort::Graphics::SVG::Colour::Colour()
{
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

AuxPort::Graphics::SVG::Colour::Colour(const Colours& colour)
{
	switch (colour)
	{
	case Colours::Black:
		red = 0;green = 0;blue = 0;alpha = 255;
		break;
	case Colours::White:
		red = 255;green = 255;blue = 255;alpha = 255;
		break;
	}
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

