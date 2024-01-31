#include "AuxFIR.h"
#include "AuxFIR.h"

void AuxPort::Audio::FIR::setSampleRate(uint32_t sampleRate)
{
	this->sampleRate = sampleRate;
}

void AuxPort::Audio::FIR::replace(const std::vector<float>& impulseResponse)
{
	this->impulseResponse = impulseResponse;
}

void AuxPort::Audio::FIR::replace(float* impulseResponse, uint32_t size)
{
	AuxAssert(impulseResponse != nullptr, "Impulse Response can't be a nullptr");
	AuxAssert(size > 0, "IR size should be greater than 0");
	this->impulseResponse.resize(size);
	for (uint32_t i = 0; i < this->impulseResponse.size(); i++)
		this->impulseResponse[i] = impulseResponse[i];
}

void AuxPort::Audio::FIR::normalize()
{
	AuxAssert(this->impulseResponse.size() > 0, "Impulse Response Vector Size can't be zero");
	auto gain = AuxPort::Utility::abssum(impulseResponse);
	gain = 1.0f / gain;
	AuxPort::Utility::multiply(impulseResponse, gain);
}

void AuxPort::Audio::FIR::spectralReversal()
{
	for (size_t i = 1; i < order; i += 2)
	{
		impulseResponse[i] = -impulseResponse[i];
	}
}

void AuxPort::Audio::FIR::Log()
{
	setColour(AuxPort::ColourType::Green);
	std::cout << "Impulse Response : [";
	for (uint32_t i = 0; i < impulseResponse.size(); i++)
		std::cout << impulseResponse[i] << " ";
	std::cout << "]";
	setColour(AuxPort::ColourType::White);
}

std::vector<float>* AuxPort::Audio::FIR::getImpulseResponse()
{
	return &impulseResponse;
}

void AuxPort::Audio::FIR::compute(float passband, float stopband, uint32_t order, Type filterType)
{
	AuxAssert(this->sampleRate > 0, "Call setSampleRate() before calling compute");
	AuxAssert(stopband > 0 && passband > 0, "Passband and Stopband should be greater than 0");
	AuxAssert(stopband > passband, "Stopband should be greater than the passband");
	AuxAssert(order < 1000, "Why are you creating a 1000 tap FIR?... What's wrong with you");
	this->passband = (2 * AuxPort::pi * passband) / this->sampleRate;
	this->stopband = (2 * AuxPort::pi * stopband) / this->sampleRate;
	this->cutoff = (this->passband + this->stopband) / 2;
	this->normFreq = this->cutoff;
	order = order % 2 == 1 ? order : order+1;
	this->order = order;
	impulseResponse.resize(order);
	this->filterType = filterType;

	filterAlgo();
	normalize();
}

void AuxPort::Audio::FIR::compute(float cutoffFrequency, uint32_t order, Type filterType)
{
	AuxAssert(this->sampleRate > 0, "Call setSampleRate() before calling compute");
	AuxAssert(order < 1000, "Why are you creating a 1000 tap FIR?... What's wrong with you");
	AuxAssert(cutoffFrequency < (this->sampleRate / 2) && cutoffFrequency > 0, "Cutoff can't be greater than Nyquist or less than 0");
	AuxAssert(filterType == LowPass || filterType == HighPass, "Use the other overloaded function to compute BandPass or BandReject FIR Filter");
	this->cutoff = (2 * AuxPort::pi * cutoffFrequency) / this->sampleRate;
	this->normFreq = this->cutoff / 2;
	order = order % 2 == 1 ? order : order+1;
	this->order = order;
	impulseResponse.resize(order);
	this->filterType = filterType;

	filterAlgo();
	normalize();
}

void AuxPort::Audio::RectangleFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size()-1);

	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = (cutoff / pi) * AuxPort::Utility::sinc<float>((cutoff / pi) * v);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = (stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband / pi)* v);
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::HammingFIR::filterAlgo()
{
	auto hamming = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::HammWin);
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);

	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N/2);
			impulseResponse[i] = hamming[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v)/pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = hamming[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::HannFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto hann = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::HannWin);

	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = hann[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v)/pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = hann[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::BlackmanFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto blackman = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BlackmanWin);
	
	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = blackman[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v) / pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = blackman[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::BartlettFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto bartlett = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BartlettWin);
	
	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = bartlett[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v) / pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = bartlett[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::BartlettHannFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto bartlettHann = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BartlettHannWin);
	
	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = bartlettHann[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v) / pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = bartlettHann[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::NuttallFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto nuttall = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::NuttallWin);
	
	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = nuttall[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v) / pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = nuttall[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::FlatFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto flat = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::FlatWin);
	
	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = flat[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v) / pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = flat[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::BlackmanHarrisFIR::filterAlgo()
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	auto blackmanHarris = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BlackmanHarrisWin);
	
	if (filterType == LowPass || filterType == HighPass)
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = blackmanHarris[i] * (cutoff / AuxPort::pi) * AuxPort::Utility::sinc((cutoff * v) / pi);
		}
	}
	else
	{
		for (uint32_t i = 0; i < impulseResponse.size(); i++)
		{
			int32_t v = i - (N / 2);
			impulseResponse[i] = blackmanHarris[i] * ((stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband * v) / pi));
		}
	}

	if (filterType == HighPass || filterType == BandReject)
	{
		spectralReversal();
	}
}

void AuxPort::Audio::Convolution::setImpulseResponse(const std::vector<float>& impulseResponse)
{
	AuxAssert(impulseResponse.size() > 0, "Impulse Response cannot be empty!");
	irSize = impulseResponse.size();
	this->impulseResponse = impulseResponse;
	inputBuffer.resize(irSize);
}

void AuxPort::Audio::Convolution::setImpulseResponse(float* impulseResponse, uint32_t size)
{
	AuxAssert(impulseResponse != nullptr, "Impulse Response can't be a nullptr");
	AuxAssert(size > 0, "IR size should be greater than 0");
	irSize = size;
	this->impulseResponse.resize(size);
	for (uint32_t i = 0; i < size; i++)
		this->impulseResponse[i] = impulseResponse[i];
	inputBuffer.resize(size);
}

void AuxPort::Audio::Convolution::setImpulseResponse(std::vector<float>* impulseResponse, uint32_t size)
{
	AuxAssert(impulseResponse != nullptr, "Impulse Response can't be a nullptr");
	AuxAssert(size > 0, "IR size should be greater than 0");
	irSize = size;
	this->impulseResponse.resize(size);
	for (uint32_t i = 0; i < size; i++)
		this->impulseResponse[i] = (*impulseResponse)[i];
	inputBuffer.resize(size);
}

float AuxPort::Audio::Convolution::process(float sample)
{
	float outputSample = 0;
	inputBuffer.push(sample);
	for (uint32_t i = 0; i < irSize; i++)
	{
		outputSample += impulseResponse[i] * inputBuffer.getShiftedElement(-i);
	}
	inputBuffer.pop();
	return outputSample;
}
