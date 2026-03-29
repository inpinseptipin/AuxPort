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

void AuxPort::Audio::Convolution::setImpulseResponse(const std::vector<float>& impulseResponse)
{
	AuxAssert(impulseResponse.size() > 0, "Impulse Response cannot be empty!");
	irSize = impulseResponse.size();
	this->impulseResponse = impulseResponse;
	inputBuffer.resize(irSize);
}

void AuxPort::Audio::Convolution::setImpulseResponse(const float* impulseResponse, uint32_t size)
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
	AuxAssert(impulseResponse.size() > 0, "Impluse Response is not provided. Please set Impulse Response first using setImpulseResponse().");
	float outputSample = 0;
	inputBuffer.push(sample);
	for (uint32_t i = 0; i < irSize; i++)
	{
		outputSample += impulseResponse[i] * inputBuffer.getShiftedElement(-static_cast<int>(i));
	}
	inputBuffer.pop();
	return outputSample;
}

void AuxPort::Audio::Convolution::process(const float* input, float* output, uint32_t bufferSize)
{
	AuxAssert(input != nullptr,"Input Buffer cannot be a nullptr");
	AuxAssert(output != nullptr, "Output Buffer cannot be a nullptr");
	AuxAssert(bufferSize > 0, "Buffer Size has to be greater than 0");
	float outputSample = 0;
	for (uint32_t i = 0;i < bufferSize;i++)
	{
		inputBuffer.push(input[i]);
		for (uint32_t h = 0;h < irSize;h++)
			outputSample += impulseResponse[h] * inputBuffer.getShiftedElement(-static_cast<int>(h));
		inputBuffer.pop();
		output[i] = outputSample;
	}
}

AuxPort::Audio::FastConvolution::FastConvolution(uint32_t fftSize)
{
	filterFourierTransform.reset(new FourierTransform(fftSize));
	audioFourierTransform.reset(new FourierTransform(fftSize));
	fftFrame = audioFourierTransform->getFourierTransformFrame();
	impulseResponse.resize(fftSize);
	this->states = STFT::initial;

	fftInputBuffer.resize(fftSize);
	fftOutputBuffer.resize(fftSize);
	writeIndex = 0;
	readIndex = 0;
}

void AuxPort::Audio::FastConvolution::setImpulseResponse(const std::vector<float>& impulseResponse)
{
	setImpulseResponse(impulseResponse.data(), impulseResponse.size());
}

void AuxPort::Audio::FastConvolution::setImpulseResponse(const float* impulseResponse, uint32_t size)
{
	AuxAssert(impulseResponse != nullptr, "Impulse response cannot be a nullptr");
	AuxAssert(size > 0, "Impulse response size has to be greater than zero");
	AuxAssert(this->impulseResponse.size() > size, "FFT Size not compatible with filter length, initialize the Fast Convolution Engine with a longer FFT Size ");
	impulseResponseSize = size;
	overlapBuffer.resize(impulseResponseSize-1);
	inputDataBuffer.resize(fftInputBuffer.size() - overlapBuffer.size());
	outputDataBuffer = inputDataBuffer;
	std::fill(overlapBuffer.begin(), overlapBuffer.end(), 0.0f);
	if (size < this->impulseResponse.size())
	{
		std::copy(impulseResponse, impulseResponse + size, this->impulseResponse.begin());
		std::fill(this->impulseResponse.begin() + size, this->impulseResponse.end(), 0.0f);
	}
	else
		std::copy(impulseResponse, impulseResponse + size, this->impulseResponse.begin());
	filterFourierTransform->computeTransform(this->impulseResponse);
	filterFFTFrame = filterFourierTransform->getFourierTransformFrame();
}

void AuxPort::Audio::FastConvolution::process(const float* input, float* output, uint32_t bufferSize)
{
	AuxAssert(input != nullptr, "Input Buffer pointer can't be a nullptr");
	AuxAssert(output != nullptr, "Output Buffer pointer can't be a nullptr ");
	AuxAssert(bufferSize > 0, "Buffer Size has to be greater than zero");
	for (uint32_t i = 0;i < bufferSize;i++)
	{
		inputDataBuffer[writeIndex++] = input[i];
		output[i] = outputDataBuffer[readIndex++];

		if (writeIndex == inputDataBuffer.size())
		{
			compute();
			writeIndex = 0;
		}
		if (readIndex == outputDataBuffer.size())
			readIndex = 0;
	}
}

void AuxPort::Audio::FastConvolution::compute()
{
	std::copy(overlapBuffer.begin(), overlapBuffer.end(), fftInputBuffer.begin());
	std::copy(inputDataBuffer.begin(), inputDataBuffer.end(), fftInputBuffer.begin() + overlapBuffer.size());
	audioFourierTransform->computeTransform(fftInputBuffer.data(), fftInputBuffer.size());
	for (uint32_t i = 0;i < fftInputBuffer.size();i++)
	{
		fftFrame->at(i) *= filterFFTFrame->at(i);
	}
	audioFourierTransform->computeInverseTransform(fftOutputBuffer.data(), fftOutputBuffer.size());
	std::copy(inputDataBuffer.begin() + (inputDataBuffer.size() - overlapBuffer.size()), inputDataBuffer.end(), overlapBuffer.begin());
	std::copy(fftOutputBuffer.begin() + overlapBuffer.size(), fftOutputBuffer.end(), outputDataBuffer.begin());
	for (uint32_t i = 0;i < outputDataBuffer.size();i++)
		outputDataBuffer[i] = outputDataBuffer[i] / fftOutputBuffer.size();
}
