#include "OscillatorBench.h"
#include "OscillatorBench.h"
#include "OscillatorBench.h"

void AuxPort::Benchmarks::Oscillator::setOscillators(const std::vector<AuxPort::Audio::Oscillator> oscillators, const std::vector<std::string> names)
{
	this->oscillators = oscillators;
	this->oscillatorNames = names;
	benchmarkTimes.resize(oscillators.size());
	std::fill(benchmarkTimes.begin(), benchmarkTimes.end(), 0.0f);
}

void AuxPort::Benchmarks::Oscillator::benchmark()
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
			benchmarkTimes[i] += getEllapsedTime(AuxPort::Timer::nano);
		}
		benchmarkTimes[i] /= numberOfIterations;
	}
}

void AuxPort::Benchmarks::Oscillator::setParameters(size_t bufferSize, size_t numberOfIterations)
{
	this->bufferSize = bufferSize;
	this->numberOfIterations = numberOfIterations;
}

void AuxPort::Benchmarks::Oscillator::Log()
{
	setColour(AuxPort::ColourType::Green);
	std::cout << "\n\n*************Benchmarks**********\n\n";
	std::cout << "Buffer Size : " << bufferSize << "\n";
	std::cout << "Number of Iterations : " << numberOfIterations << "\n\n";
	for (uint32_t i = 0; i < oscillators.size(); i++)
	{
		std::cout << "Oscillator Name : " << oscillatorNames[i] << "\n";
<<<<<<< HEAD
		std::cout << "Average Benchmark Time : " << benchmarkTimes[i] << "ns" << "\n\n";
=======
		std::cout << "Average Benchmark Time : " << benchmarkTimes[i] << " ns" << "\n\n";
>>>>>>> cccf14e74ce9cf565751dc2cba35579da0bed9ef
	}
	setColour(AuxPort::ColourType::White);
}

void AuxPort::Benches::OscillatorBench::benchmarkSines(size_t bufferSize, size_t numberOfIterations)
{
	AuxPort::Benchmarks::Oscillator oscillatorBench;
	std::vector<AuxPort::Audio::Oscillator> oscillators;
	oscillators.push_back(AuxPort::Audio::Sine::FastSine());
	oscillators.push_back(AuxPort::Audio::Sine::Sine());
	oscillators.push_back(AuxPort::Audio::Sine::AuxSine());
	oscillators.push_back(AuxPort::Audio::Sine::AuxSine2());
	oscillators.push_back(AuxPort::Audio::Sine::BhaskaraSine());
	oscillators.push_back(AuxPort::Audio::Sine::JavidX9Sine());
	oscillators.push_back(AuxPort::Audio::Sine::JavidX9Sine2());
	oscillators.push_back(AuxPort::Audio::Sine::ParabolicSine());

	oscillatorBench.setParameters(bufferSize, numberOfIterations);
	oscillatorBench.setOscillators(oscillators, { "fastsine","std::sin","AuxSine","AuxSine2","Bhasakara Sine","JavidX9","Javidx92","Parabolic"});
	oscillatorBench.benchmark();
	oscillatorBench.Log();
}

void AuxPort::Benches::OscillatorBench::benchmarkSawtooths(size_t bufferSize, size_t numberOfIterations)
{
	AuxPort::Benchmarks::Oscillator oscillatorBench;
	std::vector<AuxPort::Audio::Oscillator> oscillators;
	oscillators.push_back(AuxPort::Audio::Sawtooth::BipolarSawtooth());
	oscillators.push_back(AuxPort::Audio::Sawtooth::DPWSaw());
	oscillators.push_back(AuxPort::Audio::Sawtooth::PBSaw());
	oscillators.push_back(AuxPort::Audio::Sawtooth::PBWSaw());
	oscillators.push_back(AuxPort::Audio::Sawtooth::SawSin1());
	oscillators.push_back(AuxPort::Audio::Sawtooth::SawSin2());
	oscillators.push_back(AuxPort::Audio::Sawtooth::UnipolarSawtooth());
	oscillatorBench.setParameters(bufferSize, numberOfIterations);
	oscillatorBench.setOscillators(oscillators, { "Bipolar Sawtooth","DPW","PBSaw","PBWSaw","SawSin1","SawSin2","Unipolar Sawtooth" });
	oscillatorBench.benchmark();
	oscillatorBench.Log();


}

void AuxPort::Benches::OscillatorBench::benchmarkTriangle(size_t bufferSize, size_t numberOfIterations)
{
	AuxPort::Benchmarks::Oscillator oscillatorBench;
	std::vector<AuxPort::Audio::Oscillator> oscillators;
	oscillators.push_back(AuxPort::Audio::Triangle::DPWTriangle1());
	oscillators.push_back(AuxPort::Audio::Triangle::Triangle());

	oscillatorBench.setParameters(bufferSize, numberOfIterations);
	oscillatorBench.setOscillators(oscillators, { "DPW","Triangle" });
	oscillatorBench.benchmark();
	oscillatorBench.Log();
}
