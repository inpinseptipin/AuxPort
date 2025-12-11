#ifndef AUXPORT_SVG_PATH_H
#define AUXPORT_SVG_PATH_H

#include "AuxSVGObject.h"
#include "AuxSVGColour.h"
#include <vector>

namespace AuxPort
{
    namespace Graphics
    {
        namespace SVG
        {
            /**
             * @brief Creates a Path Object
             * @note Follows SVG Path specifications listed at: https://www.w3.org/TR/SVG2/paths.html#PathElement
            */
            class Path : public SVGObject
            {
            public:
                Path() = default;
                ~Path() = default;
                Path(const Path& path) = default;
                
                /**
                 * @brief Generates the appropriate SVG string for the Path Object
                 */
                void generateString() override;
                
                /**
                 * @brief Adds a subpath to this path
                 * @param subPath The subpath to add
                 */
                void addSubPath(const Path& subPath);
                
                /**
                 * @brief Move the current point to the specified coordinates (absolute)
                 * @see https://www.w3.org/TR/SVG2/paths.html#PathDataMovetoCommands
                 */
                Path& moveTo(float x, float y);

                /**
                 * @brief Draw a line to the specified coordinates (absolute)
                 * @see https://www.w3.org/TR/SVG2/paths.html#PathDataLinetoCommands
                */
                Path& lineTo(float x, float y);

                /**
                 * @brief Closes the current path
                 * @see https://www.w3.org/TR/SVG2/paths.html#PathDataClosePathCommand
                 */
                Path& closePath();
                
                // TODO: Implement more SVG Path commands as needed
                // TODO: Implement relative commands (lowercase letters)
                // TODO: Maybe Move these to SVGObject
                Path& setStroke(const Colour& colour);
                Path& setFill(const Colour& colour);
            protected:
                std::vector<std::string> commands;
                std::vector<Path> subPaths;
                Colour strokeColour;
                Colour fillColour;
            };
        }
    }
}

#endif
