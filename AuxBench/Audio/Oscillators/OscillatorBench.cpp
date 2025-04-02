#include "OscillatorBench.h"
#include "OscillatorBench.h"
#include "OscillatorBench.h"

void AuxPort::Benchmarks::OscillatorBench::setOscillators(const std::vector<AuxPort::Audio::Oscillator> oscillators, const std::vector<std::string> names)
{
	this->oscillators = oscillators;
	this->oscillatorNames = names;
	benchmarkTimes.resize(oscillators.size());
	std::fill(benchmarkTimes.begin(), benchmarkTimes.end(), 0.0f);
}

void AuxPort::Benchmarks::OscillatorBench::benchmark()
{
	auto sample = 0.0f;
	for (uint32_t i = 0; i < oscillators.size(); i++)
	{
		for (uint32_t j = 0; j < numberOfIterations; j++)
		{
			start();
			for (uint32_t k = 0; k < bufferSize; k++)
			{
				sample = oscillators[i].process();
			}
			stop();
			benchmarkTimes[i] += getEllapsedTime();

		}
	}
}

void AuxPort::Benchmarks::OscillatorBench::setParameters(size_t bufferSize, size_t numberOfIterations)
{
	this->bufferSize = bufferSize;
	this->numberOfIterations = numberOfIterations;
}

void AuxPort::Benchmarks::OscillatorBench::Log()
{
	setColour(AuxPort::ColourType::Green);
	std::cout << "\n\n*************Benchmarks**********\n";
	std::cout << "Buffer Size : " << bufferSize << "\n";
	std::cout << "Number of Iterations : " << numberOfIterations << "\n\n";
	for (uint32_t i = 0; i < oscillators.size(); i++)
	{
		std::cout << "Oscillator Name : " << oscillatorNames[i] << "\n";
		std::cout << "Average Benchmark Time : " << benchmarkTimes[i] << "\n\n";
	}
	setColour(AuxPort::ColourType::White);
}
