#include "AuxSVG.h"



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

void AuxPort::Graphics::SVG::SVG::generateString()
{
	svgData += "<svg " + valueToString("width", width) + valueToString("height", height) + " xmlns = \"http://www.w3.org/2000/svg\">";
	svgData += backgroundData;
	for (uint32_t i = 0;i < textData.size();i++)
		svgData += textData[i];
	svgData += "</svg>";
}

AuxPort::Graphics::SVG::SVG::SVG(float width, float height)
{
	svgData.clear();
	this->width = width;
	this->height = height;
}

void AuxPort::Graphics::SVG::SVG::save()
{
	generateString();
	writeLineToFile(svgData);
	this->close();
}


