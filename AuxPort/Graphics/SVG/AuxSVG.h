#ifndef AUXPORT_SVG
#define AUXPORT_SVG

#include "../../Core/File/AuxFile.h"

namespace AuxPort
{
	namespace Graphics
	{
		namespace SVG
		{
/**
	SVG Abstract Object
*/
			class SVGObject
			{
			public:
				SVGObject() = default;
				~SVGObject() = default;
				SVGObject(const SVGObject& svgObject) = default;
/**
   @brief Returns the SVG String for the particular object
   @return 
*/
				std::string& getSVGString();
			protected:
/**
   @brief Generates the appropriate SVG string for the object [Overridable]
*/
				virtual void generateString() = 0;
				static std::string valueToString(const std::string& key,float val);
				std::string svgString;
			};

/**
	Creates a Colour Object [Supports 8 bit RGBA]
*/
			class Colour : public SVGObject
			{
			public:
				Colour();
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

/**
	Creates a Text SVG object
*/
			class Text : public SVGObject
			{
			public:
				Text() = default;
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


/**
	Scalable Vector Graphic Engine (Creates/Reads an SVG file)
*/
			class SVG : public AuxPort::TextFile
			{
			public:
				SVG();
				~SVG() = default;
				SVG(const SVG& svg) = default;
				void save();
/**
	@brief Adds Background to the SVG file
	@param red
	@param green
	@param blue
	@param alpha
	@details
	Example Definition/Implementation
	\code{.cpp}
		AuxPort::Graphics::SVG svg;
		svg.addBackground(13,13,13,255);
	\endcode
*/
				void addBackground(AuxPort::Graphics::SVG::Colour& colour);
/**
	@brief Draws Text on the File
	@param text
	@param startX
	@param startY
	@param fontSize
	@details
*/
				void addText(const std::string& text, float startX, float startY, float fontSize);
				void addText(AuxPort::Graphics::SVG::Text& text);
			protected:
				std::string svgData;
				std::string backgroundData;
				std::vector<std::string> textData;
			};

		}
	}
}

#endif
