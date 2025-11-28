#ifndef AUXPORT_SVG
#define AUXPORT_SVG

#include "../../Core/File/AuxFile.h"
#include "AuxSVGObject.h"
#include "AuxSVGText.h"

namespace AuxPort
{
	namespace Graphics
	{
		namespace SVG
		{
/**
	Scalable Vector Graphic Engine (Creates/Reads an SVG file)
*/
			class SVG : public AuxPort::TextFile,protected AuxPort::Graphics::SVG::SVGObject
			{
			public:
				SVG(float width, float height);
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
				void generateString() override;
				std::string svgData;
				std::string backgroundData;
				std::vector<std::string> textData;
				float width;
				float height;
			};

		}
	}
}

#endif
