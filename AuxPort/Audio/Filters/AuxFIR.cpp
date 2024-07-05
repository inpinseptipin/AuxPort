#include "AuxFIR.h"
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

void AuxPort::Audio::FIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::RectangleWin);
	AuxPort::Utility::multiply(impulseResponse, window);
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
	applyWindow();
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
	applyWindow();
	normalize();
}

void AuxPort::Audio::RectangleFIR::genIR(float band)
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	for (uint32_t i = 0; i < impulseResponse.size(); i++)
	{
		int32_t v = i - (N / 2);
		impulseResponse[i] = (band / pi) * AuxPort::Utility::sinc((band / pi) * v);
	}
}

void AuxPort::Audio::RectangleFIR::genIR(float passband, float stopband)
{
	int32_t N = static_cast<int32_t>(impulseResponse.size() - 1);
	for (uint32_t i = 0; i < impulseResponse.size(); i++)
	{
		int32_t v = i - (N / 2);
		impulseResponse[i] = (stopband / pi) * AuxPort::Utility::sinc<float>((stopband / pi) * v) - (passband / pi) * AuxPort::Utility::sinc<float>((passband / pi) * v);
	}
}

void AuxPort::Audio::RectangleFIR::filterAlgo()
{
	if (filterType == LowPass)
		genIR(cutoff);
	if (filterType == HighPass)
	{
		genIR(cutoff);
		spectralReversal();
	}
	if (filterType == BandPass)
	{
		genIR(passband, stopband);
	}
	if (filterType == BandReject)
	{
		genIR(passband, stopband);
		spectralReversal();
	}
}

void AuxPort::Audio::HammingFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::HammWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::HannFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::HammWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::BlackmanFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BlackmanWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::BartlettFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BartlettWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::BartlettHannFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BartlettHannWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::NuttallFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BartlettHannWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::FlatFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::FlatWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::BlackmanHarrisFIR::applyWindow()
{
	auto window = AuxPort::Audio::Window::generate<float>(impulseResponse.size(), AuxPort::Audio::Window::BlackmanHarrisWin);
	Utility::multiply(impulseResponse, window);
}

void AuxPort::Audio::Convolution::setSize(size_t size)
{
	this->irSize = size;
#if AUXSIMD
	if (AuxPort::Env::supportsAVX())
		this->perfectSimdSize = floor(size / 8.0f) * 8;
	else if (AuxPort::Env::supportsSSE())
		this->perfectSimdSize = floor(size / 4.0f) * 4;
#endif
}

void AuxPort::Audio::Convolution::setImpulseResponse(const std::vector<float>& impulseResponse)
{
	AuxAssert(impulseResponse.size() > 0, "Impulse Response cannot be empty!");
	setSize(impulseResponse.size());
	this->impulseResponse = impulseResponse;
	inputBuffer.resize(impulseResponse.size());
}

void AuxPort::Audio::Convolution::setImpulseResponse(float* impulseResponse, uint32_t size)
{
	AuxAssert(impulseResponse != nullptr, "Impulse Response can't be a nullptr");
	AuxAssert(size > 0, "IR size should be greater than 0");
	setSize(size);
	this->impulseResponse.resize(size);
	for (uint32_t i = 0; i < size; i++)
		this->impulseResponse[i] = impulseResponse[i];
	inputBuffer.resize(size);
}

void AuxPort::Audio::Convolution::setImpulseResponse(std::vector<float>* impulseResponse, uint32_t size)
{
	AuxAssert(impulseResponse != nullptr, "Impulse Response can't be a nullptr");
	AuxAssert(size > 0, "IR size should be greater than 0");
	setSize(size);
	this->impulseResponse.resize(size);
	for (uint32_t i = 0; i < size; i++)
		this->impulseResponse[i] = (*impulseResponse)[i];
	inputBuffer.resize(size);
}

float AuxPort::Audio::Convolution::process(float sample)
{
	AuxAssert(impulseResponse.size() > 0, "Impluse Response is not provided. Please set Impulse Response first using setImpulseResponse().");
	float outputSample = 0;
	inputBuffer.push(sample);
#ifdef AUXSIMD
	if (AuxPort::Env::supportsAVX())
	{
		if (irSize > 7)
		{
			auto outputs = _mm256_setzero_ps();
			for (size_t i = 0; i < perfectSimdSize; i += 8)
			{
				auto IrRegister = _mm256_load_ps(impulseResponse.data() + i);
				__m256 inputBufferRegister;
				for (size_t j = 0; j < 8; j++)
					inputBufferRegister.m256_f32[j] = inputBuffer.getShiftedElement(-(i + j));

				outputs = _mm256_add_ps(outputs, _mm256_mul_ps(IrRegister, inputBufferRegister));
			}
			outputs = _mm256_hadd_ps(outputs, outputs);
			outputs = _mm256_hadd_ps(outputs, outputs);
			outputs = _mm256_hadd_ps(outputs, outputs);
			outputSample += _mm256_cvtss_f32(outputs);
		}

		for(size_t i = perfectSimdSize; i < irSize; i++)
			outputSample += impulseResponse[i] * inputBuffer.getShiftedElement(-i);
	}
	else if (AuxPort::Env::supportsSSE())
	{
		if (irSize > 3)
		{
			auto outputs = _mm_setzero_ps();
			for (size_t i = 0; i < perfectSimdSize; i += 4)
			{
				auto IrRegister = _mm_load_ps(impulseResponse.data() + i);
				__m128 inputBufferRegister;
				for (size_t j = 0; j < 4; j++)
					inputBufferRegister.m128_f32[j] = inputBuffer.getShiftedElement(-(i + j));

				outputs = _mm_add_ps(outputs, _mm_mul_ps(IrRegister, inputBufferRegister));
			}
			outputs = _mm_hadd_ps(outputs, outputs);
			outputs = _mm_hadd_ps(outputs, outputs);
			outputs = _mm_hadd_ps(outputs, outputs);
			outputSample += _mm_cvtss_f32(outputs);
		}

		for (size_t i = perfectSimdSize; i < irSize; i++)
			outputSample += impulseResponse[i] * inputBuffer.getShiftedElement(-i);		
	}
	else
#endif
	{
		for (size_t i = 0; i < irSize; i++)
		{
			outputSample += impulseResponse[i] * inputBuffer.getShiftedElement(-i);
		}
	}
	inputBuffer.pop();
	return outputSample;
}
