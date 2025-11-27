#ifndef AUXPORT_SVG
#define AUXPORT_SVG

#include "../../Core/File/AuxFile.h"

namespace AuxPort
{
	namespace Graphics
	{
		/**
			Scalable Vector Graphic Engine (Creates/Reads an SVG file)
		*/
		class SVG : protected AuxPort::TextFile
		{
		public:
			SVG();
			~SVG() = default;
			SVG(const SVG& svg) = default;
			bool open(const std::string& fileName, const Mode& mode = Mode::Read, bool log = false) override;
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
			void addBackground(uint8_t red = 13, uint8_t green = 13, uint8_t blue = 13, uint8_t alpha = 255);
/**
   @brief Draws Text on the File
   @param text
   @param startX
   @param startY
   @param fontSize
   @details
*/
			void addText(const std::string& text, float startX, float startY, float fontSize);
		protected:
			std::string svgData;
			std::string backgroundData;
			std::vector<std::string> textData;
		};
	}
}

#endif
