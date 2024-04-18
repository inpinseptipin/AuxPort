#include "AuxFFTTest.h"

void AuxTest::UnitTests::FourierTransform::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty())
	{
		// Default Initialization if no commands are given!
		addConstructorTests(testcases);
		addAccuracyTests(testcases);
		addInverseTests(testcases);
	}
	else
	{
		for (const auto& command : initCommands)
		{
			if (command == "Constructor")
				addConstructorTests(testcases);
			else if (command == "Accuracy")
				addAccuracyTests(testcases);
			else if (command == "Inverse")
				addInverseTests(testcases);
		}
	}
}

void AuxTest::UnitTests::FourierTransform::addConstructorTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_FourierTransform_Constructor_001",
		"FourierTransform Constructor Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(1024);
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Constructor_002",
		"FourierTransform Constructor Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(2);
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Constructor_003",
		"FourierTransform Constructor Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(1);
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Constructor_004",
		"FourierTransform Constructor Test",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(0);
			return true;
		}
	);
}

void AuxTest::UnitTests::FourierTransform::addAccuracyTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_001",
		"FourierTransform Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input = { 0.079733, -0.642474, -0.334520, 0.385309, -0.376017, 0.582191, -0.373978, 0.123768 };
			std::vector<float> output(8);
			fft.computeTransform(input, output);

			std::vector<float> expectedOutput = { -0.55599, -0.59516, 0.41221, 1.5067, -1.4536, 1.5067, 0.41221, -0.59516 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_002",
		"FourierTransform Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input = { -0.14578, -0.9136, -0.67029, -0.48299, 0.31762, -0.95769, 0.90469, -0.89047 };
			std::vector<float> output(8);
			fft.computeTransform(input, output);

			std::vector<float> expectedOutput = { -2.8385, -0.72036, -0.062559, -0.20644, 3.651, -0.20644, -0.062559, -0.72036 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_003",
		"FourierTransform Accuracy Test With size 2",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(2);
			std::vector<float> input = { -0.48324, 0.88068 };
			std::vector<float> output(2);
			fft.computeTransform(input, output);

			std::vector<float> expectedOutput = { 0.39744, -1.3639 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_004",
		"FourierTransform Accuracy Test With size 1 (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(1);
			std::vector<float> input = { -0.48627 };
			std::vector<float> output(1);
			fft.computeTransform(input, output);

			if (output[0] != input[0])
			{
				return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_005",
		"FourierTransform Test With all zeros",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input(8, 0);
			std::vector<float> output(8);
			fft.computeTransform(input, output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_006",
		"FourierTransform Test With all ones (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			fft.computeTransform(input, output);

			if (output[0] != 8) return false;
			for (uint32 i = 1; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Accuracy_007",
		"FourierTransform Test With alternating +1 and -1 (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1};
			std::vector<float> output(8);
			fft.computeTransform(input, output);

			std::vector<float> expectedOutput = { 0, 0, 0, 0, 8, 0, 0, 0};
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != expectedOutput[i])
				{
					return false;
				}
			}
			return true;
		}
	);	
}

void AuxTest::UnitTests::FourierTransform::addInverseTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_001",
		"Inverse Fourier Transform Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input(8);
			AuxPort::Utility::generateRandomValues(input, -1.0f, 1.0f);
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_002",
		"Inverse Fourier Transform Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input = { 0.079733, -0.642474, -0.334520, 0.385309, -0.376017, 0.582191, -0.373978, 0.123768 };
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_003",
		"Inverse Fourier Transform Accuracy Test With size 1 (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(1);
			std::vector<float> input = { -0.48627 };
			std::vector<float> output(1);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			if (output[0] != input[0])
			{
				return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_004",
		"Inverse Fourier Transform Test With all zeros",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input(8, 0);
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_005",
		"Inverse Fourier Transform Test With all ones samples (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 1)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_006",
		"Inverse Fourier Transform Test With all ones samples",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - 1) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_007",
		"Inverse Fourier Transform Test With alternating +1 and -1 (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1 };
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != input[i])
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_FourierTransform_Inverse_008",
		"Inverse Fourier Transform Test With alternating +1 and -1",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::FourierTransform fft(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1 };
			std::vector<float> output(8);
			fft.computeTransform(input, output);
			fft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);
}

void AuxTest::UnitTests::DFT::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty())
	{
		// Default Initialization if no commands are given!
		addAccuracyTests(testcases);
		addInverseTests(testcases);
	}
	else
	{
		for (const auto& command : initCommands)
		{
			if (command == "Accuracy")
				addAccuracyTests(testcases);
			else if (command == "Inverse")
				addInverseTests(testcases);
		}
	}
}

void AuxTest::UnitTests::DFT::addAccuracyTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_001",
		"DiscreteFourierTransform Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input = { 0.079733, -0.642474, -0.334520, 0.385309, -0.376017, 0.582191, -0.373978, 0.123768 };
			std::vector<float> output(8);
			dft.computeTransform(input, output);

			std::vector<float> expectedOutput = { -0.55599, -0.59516, 0.41221, 1.5067, -1.4536, 1.5067, 0.41221, -0.59516 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_002",
		"DiscreteFourierTransform Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input = { -0.14578, -0.9136, -0.67029, -0.48299, 0.31762, -0.95769, 0.90469, -0.89047 };
			std::vector<float> output(8);
			dft.computeTransform(input, output);

			std::vector<float> expectedOutput = { -2.8385, -0.72036, -0.062559, -0.20644, 3.651, -0.20644, -0.062559, -0.72036 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_003",
		"DiscreteFourierTransform Accuracy Test With size 2",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(2);
			std::vector<float> input = { -0.48324, 0.88068 };
			std::vector<float> output(2);
			dft.computeTransform(input, output);

			std::vector<float> expectedOutput = { 0.39744, -1.3639 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_004",
		"DiscreteFourierTransform Accuracy Test With size 1 (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::DiscreteFourierTransform dft(1);
			std::vector<float> input = { -0.48627 };
			std::vector<float> output(1);
			dft.computeTransform(input, output);

			if (output[0] != input[0])
			{
				return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_005",
		"DiscreteFourierTransform Test With all zeros",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input(8, 0);
			std::vector<float> output(8);
			dft.computeTransform(input, output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_006",
		"DiscreteFourierTransform Test With all ones",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			dft.computeTransform(input, output);

			std::vector<float> expectedOutput = {8, 0, 0, 0, 0, 0, 0, 0};
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Accuracy_007",
		"DiscreteFourierTransform Test With alternating +1 and -1",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1 };
			std::vector<float> output(8);
			dft.computeTransform(input, output);

			std::vector<float> expectedOutput = { 0, 0, 0, 0, 8, 0, 0, 0 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);
}

void AuxTest::UnitTests::DFT::addInverseTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_DFT_Inverse_001",
		"Inverse DFT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input(8);
			AuxPort::Utility::generateRandomValues(input, -1.0f, 1.0f);
			std::vector<float> output(8);
			dft.computeTransform(input, output);
			dft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Inverse_002",
		"Inverse DFT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input = { 0.079733, -0.642474, -0.334520, 0.385309, -0.376017, 0.582191, -0.373978, 0.123768 };
			std::vector<float> output(8);
			dft.computeTransform(input, output);
			dft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Inverse_003",
		"Inverse DFT Accuracy Test With size 1 (Exact Match)",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::DiscreteFourierTransform dft(1);
			std::vector<float> input = { -0.48627 };
			std::vector<float> output(1);
			dft.computeTransform(input, output);
			dft.computeInverseTransform(output);

			if (output[0] != input[0])
			{
				return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Inverse_004",
		"Inverse DFT Test With all zeros",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input(8, 0);
			std::vector<float> output(8);
			dft.computeTransform(input, output);
			dft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Inverse_005",
		"Inverse DFT Test With all ones samples",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			dft.computeTransform(input, output);
			dft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - 1) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DFT_Inverse_006",
		"Inverse DFT Test With alternating +1 and -1",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteFourierTransform dft(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1 };
			std::vector<float> output(8);
			dft.computeTransform(input, output);
			dft.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);
}

void AuxTest::UnitTests::DCT::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& initCommands)
{
	if (initCommands.empty())
	{
		// Default Initialization if no commands are given!
		addAccuracyTests(testcases);
		addInverseTests(testcases);
	}
	else
	{
		for (const auto& command : initCommands)
		{
			if (command == "Accuracy")
				addAccuracyTests(testcases);
			else if (command == "Inverse")
				addInverseTests(testcases);
		}
	}
}

void AuxTest::UnitTests::DCT::addAccuracyTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_001",
		"DCT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input = { 0.079733, -0.642474, -0.334520, 0.385309, -0.376017, 0.582191, -0.373978, 0.123768 };
			std::vector<float> output(8);
			dct.computeTransform(input, output);

			std::vector<float> expectedOutput = { -0.19657, -0.3136, -0.15217, 0.24595, 0.34704, 0.34653, 0.62111, -0.68417 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_002",
		"DCT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input = { -0.14578, -0.9136, -0.67029, -0.48299, 0.31762, -0.95769, 0.90469, -0.89047 };
			std::vector<float> output(8);
			dct.computeTransform(input, output);

			std::vector<float> expectedOutput = { -1.0036, -0.389, -0.092498, 0.56842, 0.15389, 0.79373, -0.91455, 1.0898 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_003",
		"DCT Accuracy Test With size 2",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(2);
			std::vector<float> input = { -0.48324, 0.88068 };
			std::vector<float> output(2);
			dct.computeTransform(input, output);

			std::vector<float> expectedOutput = { 0.28103, -0.96444 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_004",
		"DCT Accuracy Test With size 1",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(1);
			std::vector<float> input = { -0.48627 };
			std::vector<float> output(1);
			dct.computeTransform(input, output);
			
			if (abs(output[0] - input[0]) >= threshold)
			{
				return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_005",
		"DCT Test With all zeros",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input(8, 0);
			std::vector<float> output(8);
			dct.computeTransform(input, output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_006",
		"DCT Test With all ones",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			dct.computeTransform(input, output);

			std::vector<float> expectedOutput = { 2.8284, 0, 0, 0, 0, 0, 0, 0 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Accuracy_007",
		"DCT Test With alternating +1 and -1)",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1 };
			std::vector<float> output(8);
			dct.computeTransform(input, output);

			std::vector<float> expectedOutput = { 0, 0.5098, 0, 0.60134, 0, 0.89998, 0, 2.5629 };
			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - expectedOutput[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);
}

void AuxTest::UnitTests::DCT::addInverseTests(std::vector<AuxPort::Case>& testcases)
{
	addTestCase(testcases,
		"AuxUT_DCT_Inverse_001",
		"Inverse DCT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input(8);
			AuxPort::Utility::generateRandomValues(input, -1.0f, 1.0f);
			std::vector<float> output(8);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_002",
		"Inverse DCT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input = { 0.079733, -0.642474, -0.334520, 0.385309, -0.376017, 0.582191, -0.373978, 0.123768 };
			std::vector<float> output(8);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_003",
		"Inverse DCT Accuracy Test",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input = { -0.14578, -0.9136, -0.67029, -0.48299, 0.31762, -0.95769, 0.90469, -0.89047 };
			std::vector<float> output(8);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_004",
		"Inverse DCT Accuracy Test With size 2",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(2);
			std::vector<float> input = { -0.48324, 0.88068 };
			std::vector<float> output(2);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_005",
		"Inverse DCT Accuracy Test With size 1",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(1);
			std::vector<float> input = { -0.48627 };
			std::vector<float> output(1);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			if (abs(output[0] - input[0]) >= threshold)
			{
				return false;
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_006",
		"Inverse DCT Test With all zeros",
		[](const std::vector<std::string>& commands)
		{
			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input(8, 0);
			std::vector<float> output(8);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (output[i] != 0)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_007",
		"Inverse DCT Test With all ones",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input(8, 1);
			std::vector<float> output(8);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - 1) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);

	addTestCase(testcases,
		"AuxUT_DCT_Inverse_008",
		"Inverse DCT Test With alternating +1 and -1",
		[](const std::vector<std::string>& commands)
		{
			float threshold = 0.001; // Default Threshold
			if (!commands.empty()) threshold = AuxPort::Casters::toFloat(commands[0]);

			AuxPort::Audio::DiscreteCosineTransform dct(8);
			std::vector<float> input = { 1, -1, 1, -1, 1, -1, 1, -1 };
			std::vector<float> output(8);
			dct.computeTransform(input, output);
			dct.computeInverseTransform(output);

			for (uint32 i = 0; i < output.size(); i++)
			{
				if (abs(output[i] - input[i]) >= threshold)
				{
					return false;
				}
			}
			return true;
		}
	);
}
