#ifndef AUXPORT_SVG_TEXT_H
#define AUXPORT_SVG_TEXT_H

#include "AuxSVGColour.h"

namespace AuxPort
{
	namespace Graphics
	{
		namespace SVG
		{
			/**
				Creates a Text SVG object
			*/
			class Text : public SVGObject
			{
			public:
				Text() = default;
				Text(const std::string& text, float fontSize, float startX, float startY);
				~Text() = default;
				Text(const Text& text) = default;
				void setText(const std::string& text);
				void setFontSize(float fontSize);
				void setXY(float startX, float startY);
				void setFill(const Colour& fillColour);
				void setStroke(const Colour& strokeColour);
				void generateString() override;
			protected:
				std::string text;
				float fontSize;
				float startX;
				float startY;
				Colour fillColour;
				Colour strokeColour;
			};
		}
	}
}

#endif
