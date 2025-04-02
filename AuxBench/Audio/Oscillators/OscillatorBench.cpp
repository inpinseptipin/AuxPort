#include "OscillatorBench.h"

void AuxPort::Benchmarks::Oscillator::attachOscillator(AuxPort::Audio::Oscillator* oscillator)
{
	this->oscillator = oscillator;
}

void AuxPort::Benchmarks::Oscillator::benchmark(size_t bufferSize, size_t numberOfIterations)
{
	this->bufferSize = bufferSize;
	this->numberOfIterations = numberOfIterations;
	for (uint32_t i = 0;i < numberOfIterations;i++)
	{
		benchmarkTime = 0;
		start();
		for (uint32_t j = 0;j < bufferSize;j++)
		{
			auto x = oscillator->process();
		}
		stop();
		benchmarkTime += getEllapsedTime(AuxPort::Timer::nano);
		show();
	}
}

void AuxPort::Benchmarks::Oscillator::Log()
{
	setColour(AuxPort::ColourType::Green);
	std::cout << "Number of Iterations : " << numberOfIterations << "\n";
	std::cout << "Buffer Size : " << bufferSize << "\n";
	std::cout << "Benchmark : " << benchmarkTime  << " ns" << "\n";
	setColour(AuxPort::ColourType::White);
}
