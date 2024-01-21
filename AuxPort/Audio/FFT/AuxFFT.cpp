#include "AuxFFT.h"

AuxPort::Audio::FourierTransform::FourierTransform(size_t fftSize)
{
	uint32 isPowerOfTwo = (uint32)(fftSize & (fftSize - 1));
	AuxAssert(isPowerOfTwo==0, "Library is compatible for FFT sizes that are multiples of 2");
	_fftValues.resize(fftSize);
	_log2N = uint32(log2(fftSize));
}

void AuxPort::Audio::FourierTransform::computeTransform(const std::vector<float>& inputBuffer, std::vector<float>& outputBuffer)
{
	AuxAssert(inputBuffer.size() == _fftValues.size(), "Size of input buffer not same as the FFT Engine's expectation");
	AuxAssert(outputBuffer.size() == inputBuffer.size(), "FFT output buffer's size should be the same as the input audio buffer");
	for (uint32_t i = 0; i < inputBuffer.size(); i++)
		_fftValues[i] = inputBuffer[i];
	compute();
	for (uint32_t i = 0; i < inputBuffer.size(); i++)
		outputBuffer[i] = _fftValues[i].real();
}

void AuxPort::Audio::FourierTransform::computeInverseTransform(std::vector<float>& outputBuffer)
{
	for (uint32_t i = 0; i < _fftValues.size(); i++)
		_fftValues[i] = std::conj(_fftValues[i]);
	compute();
	for (uint32_t i = 0; i < _fftValues.size(); i++)
		_fftValues[i] = std::conj(_fftValues[i]);
	for (uint32_t i = 0; i < _fftValues.size(); i++)
		outputBuffer[i] = _fftValues[i].real();
}

std::complex<float> AuxPort::Audio::FourierTransform::get(size_t index) const
{
	return _fftValues[index];
}

std::vector<std::complex<float>>* AuxPort::Audio::FourierTransform::getFourierTransformFrame()
{
	return &_fftValues;
}

size_t AuxPort::Audio::FourierTransform::size() const
{
	return size_t();
}

void AuxPort::Audio::FourierTransform::compute()
{
	std::complex<float> temp;
	uint32_t N = static_cast<uint32_t>(_fftValues.size());
	uint32_t K = N;
	uint32_t n;
	float theta = static_cast<float>(pi / N);
	std::complex<float> phi = std::complex<float>(cos(theta), -sin(theta));
	std::complex<float> T = 1.0L;

	while (K > 0)
	{
		n = K;
		K >>= 1;
		phi = phi * phi;
		T = 1.0L;
		for (uint32_t i = 0; i < K; i++)
		{
			for (uint32_t j = i; j < N; j += n)
			{
				uint32_t b = j + K;
				temp = _fftValues[j] - _fftValues[b];
				_fftValues[j] += _fftValues[b];
				_fftValues[b] = temp * T;
			}
			T *= phi;
		}
	}
	int32_t numberOfBits = (int32_t)log2(N);
	for (uint32_t i = 0; i < N; i++)
	{
		uint32_t j = reverseBits(i);
		if (j > i)
		{
			temp = _fftValues[i];
			_fftValues[i] = _fftValues[j];
			_fftValues[j] = temp;
		}
	}
}

uint32 AuxPort::Audio::FourierTransform::reverseBits(uint32 b)
{
	b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
	b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
	b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
	b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
	b = ((b >> 16) | (b << 16)) >> (32 - _log2N);
	return b;
}



AuxPort::Audio::DiscreteFourierTransform::DiscreteFourierTransform(size_t dftSize)
{
	_dftValues.resize(dftSize);
}

void AuxPort::Audio::DiscreteFourierTransform::computeTransform(const std::vector<float>& inputBuffer, std::vector<float>& outputBuffer)
{
	AuxAssert(inputBuffer.size() == _dftValues.size(), "Size of input buffer not same as the DFT Engine's expectation");
	AuxAssert(outputBuffer.size() == inputBuffer.size(), "DFT output buffer's size should be the same as the input audio buffer");

	size_t N = inputBuffer.size();
	float theta;
	for (uint32_t i = 0; i < N; i++)
	{
		_dftValues[i] = std::complex<float>(0, 0);
		for (uint32_t j = 0; j < N; j++)
		{
			theta = 2 * AuxPort::pi * i * j / N;
			_dftValues[i] += inputBuffer[j] * std::complex<float>(cos(theta), -sin(theta));
		}
	}
	for (uint32_t i = 0; i < N; i++)
		outputBuffer[i] = _dftValues[i].real();
}

void AuxPort::Audio::DiscreteFourierTransform::computeInverseTransform(std::vector<float>& outputBuffer)
{
	size_t N = _dftValues.size();
	float theta;
	for (uint32_t i = 0; i < N; i++)
	{
		outputBuffer[i] = 0;
		for (uint32_t j = 0; j < N; j++)
		{
			theta = 2 * AuxPort::pi * i * j / N;
			outputBuffer[i] += (_dftValues[j] * std::complex<float>(cos(theta), sin(theta))).real();
		}
		outputBuffer[i] /= N;
	}
}

std::complex<float> AuxPort::Audio::DiscreteFourierTransform::get(size_t index) const
{
	return _dftValues[index];
}

std::vector<std::complex<float>>* AuxPort::Audio::DiscreteFourierTransform::getDFTFrame()
{
	return &_dftValues;
}

size_t AuxPort::Audio::DiscreteFourierTransform::size() const
{
	return _dftValues.size();
}

AuxPort::Audio::DiscreteCosineTransform::DiscreteCosineTransform(size_t dctSize)
{
	_dctValues.resize(dctSize);
}

void AuxPort::Audio::DiscreteCosineTransform::computeTransform(const std::vector<float>& inputBuffer, std::vector<float>& outputBuffer)
{
	AuxAssert(inputBuffer.size() == _dctValues.size(), "Size of input buffer not same as the DCT Engine's expectation");
	AuxAssert(outputBuffer.size() == inputBuffer.size(), "DCT output buffer's size should be the same as the input audio buffer");

	size_t N = inputBuffer.size();
	float theta;
	float scalingFactor = sqrt(2.0f / N);
	for (uint32_t i = 0; i < N; i++)
	{
		_dctValues[i] = 0;
		for (uint32_t j = 0; j < N; j++)
		{
			theta = AuxPort::pi * (2 * j + 1) * i / (2 * N);
			_dctValues[i] += inputBuffer[j] * cos(theta);
		}
		_dctValues[i] *= scalingFactor;
	}

	for (uint32_t i = 0; i < N; i++)
		outputBuffer[i] = _dctValues[i];
}

void AuxPort::Audio::DiscreteCosineTransform::computeInverseTransform(std::vector<float>& outputBuffer)
{
	size_t N = _dctValues.size();
	float theta;
	float scalingFactor = sqrt(2.0f / N);
	for (uint32_t i = 0; i < N; i++)
	{
		outputBuffer[i] = 0.5f * _dctValues[0];
		for (uint32_t j = 1; j < N; j++)
		{
			theta = AuxPort::pi * j * (2 * i + 1) / (2 * N);
			outputBuffer[i] += _dctValues[j] * cos(theta);
		}
		outputBuffer[i] *= scalingFactor;
	}
}

float AuxPort::Audio::DiscreteCosineTransform::get(size_t index) const
{
	return _dctValues[index];
}

std::vector<float>* AuxPort::Audio::DiscreteCosineTransform::getDCTFrame()
{
	return &_dctValues;
}

size_t AuxPort::Audio::DiscreteCosineTransform::size() const
{
	return _dctValues.size();
}