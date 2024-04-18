#include "AuxTest.h"

std::vector<AuxPort::Case> AuxTest::testcases = {};

void AuxTest::addTestCase(std::vector<AuxPort::Case>& testcases, const std::string& testId, const std::string& testName, std::function<bool(const std::vector<std::string>&)> testCase)
{
	AuxPort::Case test;
	test.setTestID(testId);
	test.setTestName(testName);
	test.testCase = testCase;
	testcases.push_back(test);
}

void AuxTest::runTestCases(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& commands)
{
	uint32 passedCount = 0;
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
		{
			AuxPort::Logger::Log("Test Result : Passed", AuxPort::LogType::Success, AuxPort::ColourType::Green);
			passedCount++;
		}
		else
		{
			AuxPort::Logger::Log("Test Result : Failed", AuxPort::LogType::Error, AuxPort::ColourType::Red);
		}
		std::cout << "------------------------------------------------------------------------------------" << std::endl;
	}
	AuxPort::Logger::Log(AuxPort::Casters::toStdString(passedCount) + "/" + AuxPort::Casters::toStdString(testcases.size()) + " Passed!", AuxPort::LogType::Info, AuxPort::ColourType::Yellow);
}
