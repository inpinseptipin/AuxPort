#include "AuxStringTest.h"

void AuxTest::UnitTests::String::init(std::vector<AuxPort::Case>& testcases, const std::vector<std::string>& commands)
{
	AuxPort::Case test;
	test.setTestID("AuxUTString001");
	test.setTestName("General Behavior of a String");
	test.testCase = [&](const std::vector<std::string>& commands)
	{
		AuxPort::String string = "Hello";
		string.replaceCharacter('o', 'a');
		string.Log();
		return true;
	};
	testcases.push_back(test);
}
