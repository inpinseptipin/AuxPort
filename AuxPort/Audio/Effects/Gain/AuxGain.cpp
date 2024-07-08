#include "AuxGain.h"

AuxPort::Audio::Gain::Gain(float defaultGain)
{
	smoothedGain = defaultGain;
	if (AuxPort::Env::supportsAVX())
	{
		inputSamples.resize(8);
		smoothedGains.resize(8);
		outputSamples.resize(8);
	}
	else if (AuxPort::Env::supportsSSE())
	{
		inputSamples.resize(4);
		smoothedGains.resize(4);
		outputSamples.resize(4);
	}
}

void AuxPort::Audio::Gain::process(float* leftChannel, float* rightChannel, size_t bufferSize, float currGain)
{
	smoothedGain = smoothedGain - 0.05 * (smoothedGain - currGain);
	size_t index = 0;
#ifdef AUXSIMD
	if (AuxPort::Env::supportsAVX())
	{
		auto smoothedGainRegister = _mm256_set1_ps(smoothedGain);
		for (int i = 0; i < bufferSize / 8; i++, index += 8)
		{
			auto leftChannelRegister = _mm256_load_ps(leftChannel + index);
			auto rightChannelRegister = _mm256_load_ps(rightChannel + index);
			leftChannelRegister = _mm256_mul_ps(leftChannelRegister, smoothedGainRegister);
			rightChannelRegister = _mm256_mul_ps(rightChannelRegister, smoothedGainRegister);

			_mm256_store_ps(leftChannel, leftChannelRegister);
			_mm256_store_ps(rightChannel, rightChannelRegister);
		}
	}
	else if (AuxPort::Env::supportsSSE())
	{
		auto smoothedGainRegister = _mm_set1_ps(smoothedGain);
		for (int i = 0; i < bufferSize / 4; i++, index += 4)
		{
			auto leftChannelRegister = _mm_load_ps(leftChannel + index);
			auto rightChannelRegister = _mm_load_ps(rightChannel + index);
			leftChannelRegister = _mm_mul_ps(leftChannelRegister, smoothedGainRegister);
			rightChannelRegister = _mm_mul_ps(rightChannelRegister, smoothedGainRegister);

			_mm_store_ps(leftChannel, leftChannelRegister);
			_mm_store_ps(rightChannel, rightChannelRegister);
		}
	}
#endif
	for (size_t i = index; i < bufferSize; i++)
	{
		leftChannel[i] *= smoothedGain;
		rightChannel[i] *= smoothedGain;
	}
}

float AuxPort::Audio::Gain::process(float sample, float currGain)
{
	if (currWriteIndex == inputSamples.size())
	{
		processInputSamples();
		currReadIndex = currWriteIndex = 0;
	}

	smoothedGain = smoothedGain - 0.05 * (smoothedGain - currGain);
	smoothedGains[currWriteIndex] = smoothedGain;
	inputSamples[currWriteIndex] = sample;
	currWriteIndex++;
	return outputSamples[currReadIndex++];
}

void AuxPort::Audio::Gain::processInputSamples()
{
	if (AuxPort::Env::supportsAVX())
	{
		auto inputRegister = _mm256_load_ps(inputSamples.data());
		auto smoothGainRegister = _mm256_load_ps(smoothedGains.data());
		auto outputRegister = _mm256_mul_ps(inputRegister, smoothGainRegister);
		_mm256_store_ps(outputSamples.data(), outputRegister);
	}
	else if(AuxPort::Env::supportsSSE())
	{
		auto inputRegister = _mm_load_ps(inputSamples.data());
		auto smoothGainRegister = _mm_load_ps(smoothedGains.data());
		auto outputRegister = _mm_mul_ps(inputRegister, smoothGainRegister);
		_mm_store_ps(outputSamples.data(), outputRegister);
	}
	else
	{
		for (int i = 0; i < inputSamples.size(); i++)
		{
			outputSamples[i] = inputSamples[i] * smoothedGains[i];
		}
	}
}
