#ifndef AUXPORT_SVG_COLOUR_H
#define AUXPORT_SVG_COLOUR_H
#include "AuxSVGObject.h"
namespace AuxPort
{
	namespace Graphics
	{
		namespace SVG
		{
			/**
				Creates a Colour Object [Supports 8 bit RGBA]
			*/
			class Colour : public SVGObject
			{
			public:
				enum Colours
				{
					Black, White
				};
				Colour();
				Colour(const Colours& colour);
				Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
				~Colour() = default;
				Colour(const Colour& colour) = default;
				uint8_t getRed();
				uint8_t getGreen();
				uint8_t getBlue();
				uint8_t getAlpha();
				/**
				   @brief Sets a new RGBA colour
				   @param red
				   @param green
				   @param blue
				   @param alpha
				*/
				void setColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
				/**
				   @brief Generates the appropriate SVG string for the Colour Object
				*/
				void generateString() override;
			protected:
				uint8_t red;
				uint8_t green;
				uint8_t blue;
				uint8_t alpha;
			};
		}
	}
}

#endif
