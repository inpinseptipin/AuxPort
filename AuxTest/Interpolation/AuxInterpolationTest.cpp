#include "AuxInterpolationTest.h"

void AuxTest::UnitTests::Interpolation::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty())
	{
		// Default Initialization if no commands are given!
		addLinearInterpolatorTests(testcases);
		addCubicInterpolatorTests(testcases);
		addCosineInterpolatorTests(testcases);
		addLagrangeInterpolatorTests(testcases);
		addNewtonInterpolatorTests(testcases);
	}
	else
	{
		for (const auto& command : initCommands)
		{
			if (command == "Linear")
				addLinearInterpolatorTests(testcases);
			else if (command == "Cubic")
				addCubicInterpolatorTests(testcases);
			else if (command == "Cosine")
				addCosineInterpolatorTests(testcases);
			else if (command == "Lagrange")
				addLagrangeInterpolatorTests(testcases);
			else if (command == "Newton")
				addNewtonInterpolatorTests(testcases);
		}
	}
}

void AuxTest::UnitTests::Interpolation::addLinearInterpolatorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_LinearInterpolator_001",
		"Linear Interpolator Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Linear, TestFunctionType::Sin, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_LinearInterpolator_002",
		"Linear Interpolator Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Linear, TestFunctionType::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_LinearInterpolator_003",
		"Linear Interpolator Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Linear, TestFunctionType::Quadratic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_LinearInterpolator_004",
		"Linear Interpolator Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Linear, TestFunctionType::Cubic, commands);
		}
	);
}

void AuxTest::UnitTests::Interpolation::addCubicInterpolatorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_CubicInterpolator_001",
		"Cubic Interpolator Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cubic, TestFunctionType::Sin, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_CubicInterpolator_002",
		"Cubic Interpolator Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cubic, TestFunctionType::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_CubicInterpolator_003",
		"Cubic Interpolator Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cubic, TestFunctionType::Quadratic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_CubicInterpolator_004",
		"Cubic Interpolator Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cubic, TestFunctionType::Cubic, commands);
		}
	);
}

void AuxTest::UnitTests::Interpolation::addCosineInterpolatorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_CosineInterpolator_001",
		"Cosine Interpolator Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cosine, TestFunctionType::Sin, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_CosineInterpolator_002",
		"Cosine Interpolator Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cosine, TestFunctionType::Linear, commands);
		}
	);
	
	addTestCase(testcases,
		"AuxUT_CosineInterpolator_003",
		"Cosine Interpolator Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cosine, TestFunctionType::Quadratic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_CosineInterpolator_004",
		"Cosine Interpolator Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Cosine, TestFunctionType::Cubic, commands);
		}
	);

}

void AuxTest::UnitTests::Interpolation::addLagrangeInterpolatorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_LagrangeInterpolator_001",
		"Lagrange Interpolator Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Lagrange, TestFunctionType::Sin, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_LagrangeInterpolator_002",
		"Lagrange Interpolator Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Lagrange, TestFunctionType::Linear, commands);
		}
	);
	
	addTestCase(testcases,
		"AuxUT_LagrangeInterpolator_003",
		"Lagrange Interpolator Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Lagrange, TestFunctionType::Quadratic, commands);
		}
	);
	
	addTestCase(testcases,
		"AuxUT_LagrangeInterpolator_004",
		"Lagrange Interpolator Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Lagrange, TestFunctionType::Cubic, commands);
		}
	);

}

void AuxTest::UnitTests::Interpolation::addNewtonInterpolatorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_NewtonInterpolator_001",
		"Newton Interpolator Test for sin function",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Newton, TestFunctionType::Sin, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_NewtonInterpolator_002",
		"Newton Interpolator Test for Linear function f(x) = (5x  - 9)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Newton, TestFunctionType::Linear, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_NewtonInterpolator_003",
		"Newton Interpolator Test for Quadratic function f(x) = (9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Newton, TestFunctionType::Quadratic, commands);
		}
	);

	addTestCase(testcases,
		"AuxUT_NewtonInterpolator_004",
		"Newton Interpolator Test for Cubic function f(x) = (5x^3 - 9x^2 + 5x - 7)",
		[](const std::vector<std::string>& commands)
		{
			return testInterpolator(InterpolatorType::Newton, TestFunctionType::Cubic, commands);
		}
	);
}

bool AuxTest::UnitTests::Interpolation::testInterpolator(const InterpolatorType& interpolatorType, const TestFunctionType& testFuncType, const std::vector<std::string>& commands)
{
	// Deducing Interpolator
	std::unique_ptr<AuxPort::Interpolator> interpolator;
	switch (interpolatorType)
	{
	case InterpolatorType::Linear:
		interpolator = std::unique_ptr<AuxPort::Interpolator>(new AuxPort::LinearInterpolator);
		break;

	case InterpolatorType::Cubic:
		interpolator = std::unique_ptr<AuxPort::Interpolator>(new AuxPort::CubicInterpolator);
		break;

	case InterpolatorType::Cosine:
		interpolator = std::unique_ptr<AuxPort::Interpolator>(new AuxPort::CosineInterpolator);
		break;

	case InterpolatorType::Lagrange:
		interpolator = std::unique_ptr<AuxPort::Interpolator>(new AuxPort::LagrangeInterpolator);
		break;

	case InterpolatorType::Newton:
		interpolator = std::unique_ptr<AuxPort::Interpolator>(new AuxPort::NewtonInterpolator);
		break;
	}

	// Deducing Test Function
	std::function<float(float)> testFunction;
	switch (testFuncType)
	{
	case TestFunctionType::Sin:
		testFunction = (float(*)(float))sin;
		break;

	case TestFunctionType::Linear:
		testFunction = [](float val) { return 5 * val - 9;  };
		break;

	case TestFunctionType::Quadratic:
		testFunction = [](float val) { return 9 * val * val + 5 * val - 7;  };
		break;

	case TestFunctionType::Cubic:
		testFunction = [](float val) { return 5 * val * val * val - 9 * val * val + 5 * val - 7;  };
		break;
	}

	// Default parameters in case commands are not given to the testcase
	size_t sampleCount = 1000;
	uint32 sampleRate = 1000;
	float errorThreshold = 0.01;
	// Parsing the commands for parameters (if given)
	if (!commands.empty())
	{
		sampleCount = AuxPort::Casters::toFloat(commands[0]);
		sampleRate = AuxPort::Casters::toFloat(commands[1]);
		errorThreshold = AuxPort::Casters::toFloat(commands[2]);
	}

	// Performing test
	std::vector<float> interpolatedSamples;
	interpolatedSamples.reserve(sampleCount);
	std::vector<float> expectedSamples;
	expectedSamples.reserve(sampleCount);

	float currSample;
	for (size_t i = 0; i < sampleCount; i++)
	{
		currSample = testFunction(static_cast<float>(i) / sampleRate);
		interpolatedSamples.push_back(interpolator->interpolate(currSample));
		expectedSamples.push_back(testFunction((static_cast<float>(i) - 0.5f) / sampleRate));
	}

	// Finding Relative Error
	AuxPort::Error<float> err;
	err.setType(AuxPort::Error<float>::Type::Relative);
	float resError = err.compute(interpolatedSamples, expectedSamples);
	std::cout << resError << "\n";
	if (resError < errorThreshold)
		return true;
	return false;
}
