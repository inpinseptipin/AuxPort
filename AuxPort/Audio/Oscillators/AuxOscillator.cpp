#include "AuxOscillator.h"

void AuxPort::Audio::Oscillator::setSampleRate(uint32_t sampleRate)
{
	this->sampleRate = sampleRate;
}

void AuxPort::Audio::Oscillator::setFrequency(uint32_t frequency)
{
	this->frequency = frequency;
	this->inc = static_cast<float>(this->frequency) / static_cast<float>(this->sampleRate);
}

float AuxPort::Audio::Oscillator::process()
{
	return 0.0f;
}

void AuxPort::Audio::Oscillator::stop()
{
	inc = 0;
}

bool AuxPort::Audio::Oscillator::isPlaying()
{
	return inc != 0;
}

float AuxPort::Audio::Sine::process()
{
	if (isPlaying())
	{
		if (mod >= 1)
			mod = 0;
		sample = sin(2 * pi * mod);
		mod += inc;
		return sample;
	}
}

float AuxPort::Audio::UnipolarSawtooth::process()
{
	if (isPlaying())
	{
		if (mod >= 1)
			mod = 0;
		sample = mod;
		mod += inc;
		return sample;
	}
}

void AuxPort::Audio::Square::setPulseWidth(float pulseWidth)
{
	this->pulseWidth = pulseWidth / 100;
}

float AuxPort::Audio::Square::process()
{
	if (isPlaying())
	{
		if (mod >= 1.0)
			mod = 0;
		sample = mod > pulseWidth ? -1.0 : 1.0;
		mod += inc;
		return sample;
	}	
}

float AuxPort::Audio::BipolarSawtooth::process()
{
	if (isPlaying())
	{
		if (mod >= 1.0)
			mod = 0;
		sample = 2.0 * mod - 1.0;
		mod += inc;
		return sample;
	}
}

float AuxPort::Audio::Triangle::process()
{
	if (isPlaying())
	{
		if (mod >= 1.0)
			mod = 0.0;
		sample = 2.0 * fabs(2.0 * mod - 1.0) - 1.0;
		mod += inc;
		return sample;
	}
}

float AuxPort::Audio::PolyBlepSaw::process()
{
	if (isPlaying())
	{
		if (mod >= 1)
			mod = -1;

		if (mod >= -1 && mod <= 0)
			sample = powf(mod, 2) + 2 * mod + 1;
		else
			sample = 2 * mod - powf(mod, 2) - 1;
		mod += inc;

		return sample;
	}
}

float AuxPort::Audio::PBSSaw::process()
{
	if (isPlaying())
	{
		if (mod >= 1)
			mod = 0;
		sample = tanh(satLevel * (2 * mod - 1)) / tanh(satLevel);
		mod += inc;
		return sample;
	}
}

void AuxPort::Audio::PBSSaw::setSaturationLevel(float sat)
{
	this->satLevel = sat;
}
