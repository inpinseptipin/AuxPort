#include"AuxSVGPathTest.h"

// Helper function to setup basic path tests
void setupBasicPathTests(std::vector<AuxPort::Case>& testcases) {
	AuxPort::Case test;

	// Test: Basic Path Creation and MoveTo
	test.setTestID("AuxUTSVGPathBASIC001");
	test.setTestName("Basic Path Creation and MoveTo Command");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		path.moveTo(10.0f, 20.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Get Default colour string
		AuxPort::Graphics::SVG::Colour defaultColour;
		defaultColour.generateString();

		// Expected Path String:
		// 	<path d="M 10.000000 20.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(10.0f) + " " + AuxPort::Casters::toStdString(20.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Path with LineTo Commands
	test.setTestID("AuxUTSVGPathBASIC002");
	test.setTestName("Path with LineTo Commands");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		path.moveTo(0.0f, 0.0f);
		path.lineTo(100.0f, 100.0f);
		path.lineTo(200.0f, 50.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Get default colour string
		AuxPort::Graphics::SVG::Colour defaultColour;
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 0.000000 0.000000 L 100.000000 100.000000 L 200.000000 50.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(100.0f) + " " + AuxPort::Casters::toStdString(100.0f) + 
							   " L " + AuxPort::Casters::toStdString(200.0f) + " " + AuxPort::Casters::toStdString(50.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Performance Test - Multiple Line Commands
	test.setTestID("AuxUTSVGPathBASIC003");
	test.setTestName("Performance Test - Multiple Line Commands");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		path.moveTo(0.0f, 0.0f);
		path.lineTo(1.0f, 1.0f);
		path.lineTo(2.0f, 0.0f);
		path.lineTo(3.0f, 1.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 0.000000 0.000000 L 1.000000 1.000000 L 2.000000 0.000000 L 3.000000 1.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(1.0f) + " " + AuxPort::Casters::toStdString(1.0f) + 
							   " L " + AuxPort::Casters::toStdString(2.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(3.0f) + " " + AuxPort::Casters::toStdString(1.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Path with Multiple LineTo Commands (Rectangle)
	test.setTestID("AuxUTSVGPathBASIC004");
	test.setTestName("Path with Multiple LineTo Commands (Rectangle)");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		path.moveTo(0.0f, 0.0f);
		path.lineTo(100.0f, 0.0f);
		path.lineTo(100.0f, 100.0f);
		path.lineTo(0.0f, 100.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Get default colour string
		AuxPort::Graphics::SVG::Colour defaultColour;
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 0.000000 0.000000 L 100.000000 0.000000 L 100.000000 100.000000 L 0.000000 100.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(100.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(100.0f) + " " + AuxPort::Casters::toStdString(100.0f) + 
							   " L " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(100.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Closed Path
	test.setTestID("AuxUTSVGPathBASIC005");
	test.setTestName("Closed Path with ClosePath Command");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		path.moveTo(50.0f, 50.0f);
		path.lineTo(150.0f, 50.0f);
		path.lineTo(100.0f, 150.0f);
		path.closePath();
		path.generateString();
		std::string result = path.getSVGString();
		
		// Get default colour string
		AuxPort::Graphics::SVG::Colour defaultColour;
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 50.000000 50.000000 L 150.000000 50.000000 L 100.000000 150.000000 Z" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(50.0f) + " " + AuxPort::Casters::toStdString(50.0f) + 
							   " L " + AuxPort::Casters::toStdString(150.0f) + " " + AuxPort::Casters::toStdString(50.0f) + 
							   " L " + AuxPort::Casters::toStdString(100.0f) + " " + AuxPort::Casters::toStdString(150.0f) + 
							   " Z\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);
}

// Helper function to setup stroke and fill color tests
void setupStrokeAndFillTests(std::vector<AuxPort::Case>& testcases) {
	AuxPort::Case test;

	// Test: Path with Stroke Color
	test.setTestID("AuxUTSVGPathSTROKE001");
	test.setTestName("Path with Stroke Color");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour strokeColor(255, 0, 0, 255); // Red
		AuxPort::Graphics::SVG::Colour defaultFillColor;
		
		path.moveTo(10.0f, 10.0f);
		path.lineTo(90.0f, 90.0f);
		path.setStroke(strokeColor);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate color string
		strokeColor.generateString();
		defaultFillColor.generateString();

		// Expected Path String:
		// 	<path d="M 10.000000 10.000000 L 90.000000 90.000000" stroke="rgba(255,0,0,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(10.0f) + " " + AuxPort::Casters::toStdString(10.0f) + 
							   " L " + AuxPort::Casters::toStdString(90.0f) + " " + AuxPort::Casters::toStdString(90.0f) + 
							   "\" stroke=" + strokeColor.getSVGString() + " fill=" + defaultFillColor.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Path with Fill Color
	test.setTestID("AuxUTSVGPathFILL001");
	test.setTestName("Path with Fill Color");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour fillColor(0, 255, 0, 255); // Green
		AuxPort::Graphics::SVG::Colour defaultStrokeColor;
		
		path.moveTo(20.0f, 20.0f);
		path.lineTo(80.0f, 20.0f);
		path.lineTo(50.0f, 80.0f);
		path.closePath();
		path.setFill(fillColor);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate color string
		fillColor.generateString();
		defaultStrokeColor.generateString();
		
		// Expected Path String:
		// 	<path d="M 20.000000 20.000000 L 80.000000 20.000000 L 50.000000 80.000000 Z" stroke="rgba(255,255,255,1.000000)" fill="rgba(0,255,0,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(20.0f) + " " + AuxPort::Casters::toStdString(20.0f) + 
							   " L " + AuxPort::Casters::toStdString(80.0f) + " " + AuxPort::Casters::toStdString(20.0f) + 
							   " L " + AuxPort::Casters::toStdString(50.0f) + " " + AuxPort::Casters::toStdString(80.0f) + 
							   " Z\" stroke=" + defaultStrokeColor.getSVGString() + " fill=" + fillColor.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Path with Both Stroke and Fill
	test.setTestID("AuxUTSVGPathSTROKEFILL001");
	test.setTestName("Path with Both Stroke and Fill Colors");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour strokeColor(255, 0, 0, 255); // Red
		AuxPort::Graphics::SVG::Colour fillColor(0, 0, 255, 128);   // Blue with transparency
		
		path.moveTo(30.0f, 30.0f);
		path.lineTo(70.0f, 30.0f);
		path.lineTo(70.0f, 70.0f);
		path.lineTo(30.0f, 70.0f);
		path.closePath();
		path.setStroke(strokeColor);
		path.setFill(fillColor);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate color string
		strokeColor.generateString();
		fillColor.generateString();
		
		// Expected Path String:
		// 	<path d="M 30.000000 30.000000 L 70.000000 30.000000 L 70.000000 70.000000 L 30.000000 70.000000 Z" stroke="rgba(255,0,0,1.000000)" fill="rgba(0,0,255,0.501961)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(30.0f) + " " + AuxPort::Casters::toStdString(30.0f) + 
							   " L " + AuxPort::Casters::toStdString(70.0f) + " " + AuxPort::Casters::toStdString(30.0f) + 
							   " L " + AuxPort::Casters::toStdString(70.0f) + " " + AuxPort::Casters::toStdString(70.0f) + 
							   " L " + AuxPort::Casters::toStdString(30.0f) + " " + AuxPort::Casters::toStdString(70.0f) + 
							   " Z\" stroke=" + strokeColor.getSVGString() + " fill=" + fillColor.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);
}

// Helper function to setup subpath tests
void setupSubPathTests(std::vector<AuxPort::Case>& testcases) {
	AuxPort::Case test;

	// Test: SubPath Addition
	test.setTestID("AuxUTSVGPathSUBPATH001");
	test.setTestName("Path with SubPath Addition");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path mainPath;
		AuxPort::Graphics::SVG::Path subPath;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		mainPath.moveTo(0.0f, 0.0f);
		mainPath.lineTo(100.0f, 100.0f);
		
		subPath.moveTo(50.0f, 0.0f);
		subPath.lineTo(150.0f, 50.0f);
		
		mainPath.addSubPath(subPath);
		mainPath.generateString();
		std::string result = mainPath.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 0.000000 0.000000 L 100.000000 100.000000 M 50.000000 0.000000 L 150.000000 50.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(100.0f) + " " + AuxPort::Casters::toStdString(100.0f) + 
							   " M " + AuxPort::Casters::toStdString(50.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(150.0f) + " " + AuxPort::Casters::toStdString(50.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Multiple SubPaths
	test.setTestID("AuxUTSVGPathSUBPATH002");
	test.setTestName("Path with Multiple SubPaths");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path mainPath;
		AuxPort::Graphics::SVG::Path subPath1;
		AuxPort::Graphics::SVG::Path subPath2;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		mainPath.moveTo(10.0f, 10.0f);
		mainPath.lineTo(90.0f, 10.0f);
		
		subPath1.moveTo(10.0f, 30.0f);
		subPath1.lineTo(90.0f, 30.0f);
		
		subPath2.moveTo(10.0f, 50.0f);
		subPath2.lineTo(90.0f, 50.0f);
		
		mainPath.addSubPath(subPath1);
		mainPath.addSubPath(subPath2);
		mainPath.generateString();
		std::string result = mainPath.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 10.000000 10.000000 L 90.000000 10.000000 M 10.000000 30.000000 L 90.000000 30.000000 M 10.000000 50.000000 L 90.000000 50.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(10.0f) + " " + AuxPort::Casters::toStdString(10.0f) + 
							   " L " + AuxPort::Casters::toStdString(90.0f) + " " + AuxPort::Casters::toStdString(10.0f) + 
							   " M " + AuxPort::Casters::toStdString(10.0f) + " " + AuxPort::Casters::toStdString(30.0f) + 
							   " L " + AuxPort::Casters::toStdString(90.0f) + " " + AuxPort::Casters::toStdString(30.0f) + 
							   " M " + AuxPort::Casters::toStdString(10.0f) + " " + AuxPort::Casters::toStdString(50.0f) + 
							   " L " + AuxPort::Casters::toStdString(90.0f) + " " + AuxPort::Casters::toStdString(50.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Multiple MoveTo Commands
	test.setTestID("AuxUTSVGPathSUBPATH003");
	test.setTestName("Multiple MoveTo Commands");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		path.moveTo(10.0f, 10.0f);
		path.lineTo(50.0f, 10.0f);
		path.moveTo(70.0f, 30.0f); // New subpath
		path.lineTo(110.0f, 30.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 10.000000 10.000000 L 50.000000 10.000000 M 70.000000 30.000000 L 110.000000 30.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(10.0f) + " " + AuxPort::Casters::toStdString(10.0f) + 
							   " L " + AuxPort::Casters::toStdString(50.0f) + " " + AuxPort::Casters::toStdString(10.0f) + 
							   " M " + AuxPort::Casters::toStdString(70.0f) + " " + AuxPort::Casters::toStdString(30.0f) + 
							   " L " + AuxPort::Casters::toStdString(110.0f) + " " + AuxPort::Casters::toStdString(30.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);
}

// Helper function to setup coordinate validation and boundary tests (Edge Cases)
void setupCoordinateAndBoundaryTests(std::vector<AuxPort::Case>& testcases) {
	AuxPort::Case test;

	// Test: Empty Path
	test.setTestID("AuxUTSVGPathEDGE001");
	test.setTestName("Edge Case - Empty Path Generation");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path emptyPath;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		emptyPath.generateString();
		std::string result = emptyPath.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Floating Point Precision
	test.setTestID("AuxUTSVGPathEDGE002");
	test.setTestName("Edge Case - Floating Point Precision");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		path.moveTo(3.14159f, 2.71828f);
		path.lineTo(1.41421f, 1.73205f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 3.141590 2.718280 L 1.414210 1.732050" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(3.14159f) + " " + AuxPort::Casters::toStdString(2.71828f) + 
							   " L " + AuxPort::Casters::toStdString(1.41421f) + " " + AuxPort::Casters::toStdString(1.73205f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Negative Coordinates
	test.setTestID("AuxUTSVGPathEDGE003");
	test.setTestName("Edge Case - Negative Coordinates");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		path.moveTo(-100.0f, -50.0f);
		path.lineTo(-200.0f, -150.0f);
		path.lineTo(50.0f, -75.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M -100.000000 -50.000000 L -200.000000 -150.000000 L 50.000000 -75.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(-100.0f) + " " + AuxPort::Casters::toStdString(-50.0f) + 
							   " L " + AuxPort::Casters::toStdString(-200.0f) + " " + AuxPort::Casters::toStdString(-150.0f) + 
							   " L " + AuxPort::Casters::toStdString(50.0f) + " " + AuxPort::Casters::toStdString(-75.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Zero Coordinates
	test.setTestID("AuxUTSVGPathEDGE004");
	test.setTestName("Edge Case - Zero Coordinates");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		path.moveTo(0.0f, 0.0f);
		path.lineTo(0.0f, 100.0f);
		path.lineTo(100.0f, 0.0f);
		path.closePath();
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 0.000000 0.000000 L 0.000000 100.000000 L 100.000000 0.000000 Z" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " L " + AuxPort::Casters::toStdString(0.0f) + " " + AuxPort::Casters::toStdString(100.0f) + 
							   " L " + AuxPort::Casters::toStdString(100.0f) + " " + AuxPort::Casters::toStdString(0.0f) + 
							   " Z\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);

	// Test: Large Coordinates
	test.setTestID("AuxUTSVGPathEDGE005");
	test.setTestName("Edge Case - Large Coordinates");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::Graphics::SVG::Path path;
		AuxPort::Graphics::SVG::Colour defaultColour;
		
		path.moveTo(999999.0f, 888888.0f);
		path.lineTo(777777.0f, 666666.0f);
		path.generateString();
		std::string result = path.getSVGString();
		
		// Generate default color string
		defaultColour.generateString();
		
		// Expected Path String:
		// 	<path d="M 999999.000000 888888.000000 L 777777.000000 666666.000000" stroke="rgba(255,255,255,1.000000)" fill="rgba(255,255,255,1.000000)" />
		std::string expected = "<path d=\"M " + AuxPort::Casters::toStdString(999999.0f) + " " + AuxPort::Casters::toStdString(888888.0f) + 
							   " L " + AuxPort::Casters::toStdString(777777.0f) + " " + AuxPort::Casters::toStdString(666666.0f) + 
							   "\" stroke=" + defaultColour.getSVGString() + " fill=" + defaultColour.getSVGString() + " />";
		return result == expected;
	};
	testcases.push_back(test);
}

void AuxTest::UnitTests::SVGPath::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& commands)
{
	// Setup all test categories
	setupBasicPathTests(testcases);
	setupStrokeAndFillTests(testcases);
	setupSubPathTests(testcases);
	setupCoordinateAndBoundaryTests(testcases);
	// TODO: Add test to cover cases when assertion failures are expected
}
