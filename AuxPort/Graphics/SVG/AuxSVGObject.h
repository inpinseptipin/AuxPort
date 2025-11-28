#ifndef AUXPORT_SVG_OBJECT_H
#define AUXPORT_SVG_OBJECT_H
#include "../../Core/Env/AuxEnv.h"
#include <string>

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
				static std::string valueToString(const std::string& key, float val);
				std::string svgString;
			};

		}
	}
}

#endif
