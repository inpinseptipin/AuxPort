#include "AuxPort/AuxPort.h"
#include "AuxPort/Core/Tree/AuxAVL.h"
#include "AuxPort/Graphics/SVG/AuxSVG.h"
#include "AuxPort/Graphics/SVG/AuxSVGColour.h"
#include "AuxPort/Graphics/SVG/AuxSVGPath.h"

int main(int argc, char* argv[])
{
	// Create a triangle
	AuxPort::Graphics::SVG::SVG obj(500, 500);
	AuxPort::Graphics::SVG::Path path;
	path.moveTo(150, 50);
	path.lineTo(250, 200);
	path.lineTo(50, 200);
	path.setFill(AuxPort::Graphics::SVG::Colour::Black);
	obj.addPath(path);
	obj.open("output.svg", AuxPort::File::Mode::Write);
	obj.save();

	AvlTree avltree(5);
	avltree.add(9);
	avltree.add(4);
	avltree.add(6);
	avltree.add(2);
	avltree.add(10);
	avltree.add(1);
	avltree.add(-3);
}


