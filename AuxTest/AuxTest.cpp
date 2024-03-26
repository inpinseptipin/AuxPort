#include "AuxTest.h"

void AuxTest::addTestCase(std::vector<AuxPort::Case>& testcases, const std::string& testName, std::function<bool(const std::vector<std::string>&)> testCase)
{
	AuxPort::Case test;
	test.setTestName(testName);
	test.testCase = testCase;
	testcases.push_back(test);
}

void AuxTest::runTestCases(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& commands)
{
	for (AuxPort::Case& test : testcases)
	{
		test.Log();
		
		bool passed;
		try
		{
			passed = test.testCase(commands);
		}
		catch (...)
		{
			passed = false;
		}

		if (passed)
			AuxPort::Logger::Log("Test Result : Passed", AuxPort::LogType::Success, AuxPort::ColourType::Green);
		else
			AuxPort::Logger::Log("Test Result : Failed", AuxPort::LogType::Error, AuxPort::ColourType::Red);

		std::cout << "------------------------------------------------------------------------------------" << std::endl;
	}
}
