#include "AuxInterpolationTest.h"

void AuxTest::UnitTests::Interpolation::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty())
	{
		// Default Initialization if no commands are given!
		addSinTests(testcases);
		addLinearTests(testcases);
		addQuadraticTests(testcases);
		addCubicTests(testcases);
	}
	else
	{
		for (const auto& command : initCommands)
		{
			if (command == "sin")
				addSinTests(testcases);
			else if (command == "linear")
				addLinearTests(testcases);
			else if (command == "quadratic")
				addQuadraticTests(testcases);
			else if (command == "cubic")
				addCubicTests(testcases);
		}
	}
}

void AuxTest::UnitTests::Interpolation::addSinTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_Interpolation_001",
		"Linear Interpolation Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolation((float(*)(float))sin, AuxPort::Interpolation::Type::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_002",
		"Cubic Interpolation Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolation((float(*)(float))sin, AuxPort::Interpolation::Type::Cubic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_003",
		"Cosine Interpolation Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolation((float(*)(float))sin, AuxPort::Interpolation::Type::Cosine, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_004",
		"Lagrange Interpolation Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolation((float(*)(float))sin, AuxPort::Interpolation::Type::Lagrange, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_005",
		"Newton Interpolation Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolation((float(*)(float))sin, AuxPort::Interpolation::Type::Newton, commands);
		}
	);
}

void AuxTest::UnitTests::Interpolation::addLinearTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_Interpolation_006",
		"Linear Interpolation Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val - 9;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_007",
		"Cubic Interpolation Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val - 9;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Cubic, commands);
		}
	);


	addTestCase(testcases,
		"AuxUT_Interpolation_008",
		"Cosine Interpolation Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val - 9;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Cosine, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_009",
		"Lagrange Interpolation Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val - 9;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Lagrange, commands);
		}
	);


	addTestCase(testcases,
		"AuxUT_Interpolation_010",
		"Newton Interpolation Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val - 9;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Newton, commands);
		}
	);
}

void AuxTest::UnitTests::Interpolation::addQuadraticTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_Interpolation_011",
		"Linear Interpolation Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_012",
		"Cubic Interpolation Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Cubic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_013",
		"Cosine Interpolation Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Cosine, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_014",
		"Lagrange Interpolation Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Lagrange, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_015",
		"Newton Interpolation Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Newton, commands);
		}
	);
}

void AuxTest::UnitTests::Interpolation::addCubicTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_Interpolation_16",
		"Linear Interpolation Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val * val * val - 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_17",
		"Cubic Interpolation Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val * val * val - 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Cubic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_018",
		"Cosine Interpolation Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val * val * val - 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Cosine, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_019",
		"Lagrange Interpolation Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val * val * val - 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Lagrange, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_Interpolation_020",
		"Newton Interpolation Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			auto testFunction = [](float val) { return 5 * val * val * val - 9 * val * val + 5 * val - 7;  };
			return testInterpolation(testFunction, AuxPort::Interpolation::Type::Newton, commands);
		}
	);
}

bool AuxTest::UnitTests::Interpolation::testInterpolation(std::function<float(float)> testFunction, const AuxPort::Interpolation::Type& type, const std::vector<std::string>& commands)
{
	// Default parameters in case commands are not given to the testcase
	float start = 0, end = 10, delta = 0.5, errorThreshold = 0.01;
	// Parsing the commands for parameters (if given)
	if (!commands.empty())
	{
		float start = AuxPort::Casters::toFloat(commands[0]);
		float end = AuxPort::Casters::toFloat(commands[1]);
		float delta = AuxPort::Casters::toFloat(commands[2]);

		float errorThreshold = AuxPort::Casters::toFloat(commands[3]);
	}

	// Performing test
	size_t valuesCount = (end - start) / delta + 1;
	std::vector<float> yValues;
	yValues.reserve(valuesCount);
	for (float val = start; val <= end; val += delta)
		yValues.push_back(testFunction(val));

	AuxPort::Interpolation interpolation;
	interpolation.setType(type);
	interpolation.setXValues(start, end, delta);
	interpolation.setYValues(yValues);

	float startTestValue = start + delta / 2;
	float testValuesCount = (end - startTestValue) / delta;
	std::vector<float> interpolatedValues;
	interpolatedValues.reserve(testValuesCount);
	std::vector<float> expectedValues;
	expectedValues.reserve(testValuesCount);
	for (float val = startTestValue; val < end; val += delta)
	{
		interpolatedValues.push_back(interpolation.interpolate(val));
		expectedValues.push_back(testFunction(val));
	}

	// Finding Error
	AuxPort::Error<float> err;
	err.setType(AuxPort::Error<float>::Type::Relative);
	float resError = err.compute(interpolatedValues, expectedValues);
	std::cout << resError << "\n";
	if (resError < errorThreshold)
		return true;
	return false;
}
