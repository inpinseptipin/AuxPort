#include "AuxTest/AuxTest.h"

int main(int argc, char* argv[])
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

	auto vec = AuxPort::Utility::generateRandomVals(1024);
	auto vec2 = AuxPort::Utility::generateRandomVals(1024);
	std::vector<float> resultIter(vec.size());
	AuxPort::Simd::Float256 simdEngine;

	AuxPort::Timer timer;
	timer.start();
	for (uint32_t i = 0; i < vec.size(); i++)
		resultIter[i] = vec[i] + vec2[i];
	timer.stop();
	timer.show(AuxPort::Timer::nano);

	timer.start();
	for (uint32_t i = 0; i < vec.size(); i++)
		resultIter[i] = vec[i] * vec2[i];
	timer.stop();
	timer.show(AuxPort::Timer::nano);

	timer.start();
	simdEngine.add(resultIter, vec, vec2);
	timer.stop();
	timer.show(AuxPort::Timer::nano);

	timer.start();
	simdEngine.multiply(resultIter, vec, vec2);
	timer.stop();
	timer.show(AuxPort::Timer::nano);
}


