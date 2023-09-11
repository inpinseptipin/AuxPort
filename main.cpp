#include "AuxTest/AuxTest.h"

int main(int argc,char* argv[])
{
	
#ifdef AUXPORT_64
	AuxPort::Logger::Log("AuxPort Alpha Build, x64", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
#endif
#ifdef AUXPORT_32
	AuxPort::Logger::Log("AuxPort Alpha Build, x32", AuxPort::LogType::Success, AuxPort::ColourType::Light_Purple);
#endif
	

	AuxTest::UnitTests::String::init(AuxTest::testcases, { "Test" });

	AuxTest::testcases[0].Log();
	AuxTest::testcases[0].testCase({ "Test" });	
}



