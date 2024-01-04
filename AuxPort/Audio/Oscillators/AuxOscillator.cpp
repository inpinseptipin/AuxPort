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
	else
		return 0.0f;
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
	else
		return 0.0f;
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
		sample = mod > pulseWidth ? -1.0f : 1.0f;
		mod += inc;
		return sample;
	}
	else
		return 0.0f;
}

float AuxPort::Audio::BipolarSawtooth::process()
{
	if (isPlaying())
	{
		if (mod >= 1.0)
			mod = 0;
		sample = 2.0f * mod - 1.0f;
		mod += inc;
		return sample;
	}
	else
		return 0.0f;
}

float AuxPort::Audio::Triangle::process()
{
	if (isPlaying())
	{
		if (mod >= 1.0f)
			mod = 0.0f;
		sample = 2.0f * fabs(2.0f * mod - 1.0f) - 1.0f;
		mod += inc;
		return sample;
	}
	else
		return 0.0f;
}

float AuxPort::Audio::PBSaw::process()
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
	else
		return 0.0f;
}

float AuxPort::Audio::PBWSaw::process()
{
	if (isPlaying())
	{
		if (mod >= 1)
			mod = 0;
		sample = tanh(satLevel * (2 * mod - 1)) / tanh(satLevel);
		mod += inc;
		return sample;
	}
	else
		return 0.0f;
}

void AuxPort::Audio::PBWSaw::setSaturationLevel(float sat)
{
	this->satLevel = sat;
}

AuxPort::Audio::WhiteNoise::WhiteNoise()
{
	gen.reset(new std::mt19937(randomDevice()));
	distribution.reset(new std::uniform_real_distribution<>(-1, 1));
}

float AuxPort::Audio::WhiteNoise::process()
{
	if (isPlaying())
	{
		return distribution->operator()(*gen);
	}
	return 0;
}

AuxPort::Audio::ADSR::ADSR()
{
	this->parameters.resize(8);
	this->mods.resize(4);
}

void AuxPort::Audio::ADSR::setParameters(const std::vector<float>& parameters)
{
	this->parameters = parameters;
	this->mods[Attack] = this->parameters[Attack] / (this->parameters[AttackTime] * this->sampleRate);
	this->mods[Decay] = this->parameters[Decay] / (this->parameters[DecayTime] * this->sampleRate);
	this->mods[Sustain] = this->parameters[Sustain] / (this->parameters[SustainTime] * this->sampleRate);
	this->mods[Release] = this->parameters[Release] / (this->parameters[ReleaseTime] * this->sampleRate);

}

void AuxPort::Audio::ADSR::setSampleRate(uint32_t sampleRate)
{
	this->sampleRate = sampleRate;
}

bool AuxPort::Audio::ADSR::isPlaying()
{
	return this->state != State::OFF;
}

void AuxPort::Audio::ADSR::start()
{
	this->state = State::Attack;
	envelope = 0;
}

void AuxPort::Audio::ADSR::stop()
{
	this->state = State::OFF;
}

float AuxPort::Audio::ADSR::process()
{
	if (this->state == State::Attack)
	{
		envelope += mods[Attack];
		if (envelope >= parameters[Attack])
			this->state = State::Decay;
	}
	if (this->state == State::Decay)
	{
		envelope -= mods[Decay];
		if (envelope <= parameters[Decay])
			this->state = State::Sustain;
	}
	if (this->state == State::Sustain)
	{
		envelope -= mods[Sustain];
		count++;
		if (envelope < parameters[Sustain])
			envelope = parameters[Sustain];
		if (count >= parameters[SustainTime] * sampleRate)
		{
			count = 0;
			this->state = State::Release;
		}	
	}
	if (this->state == State::Release)
	{
		envelope -= mods[Release];
		if (envelope <= 0)
		{
			this->state = Attack;
		}

	}
	return envelope;
}
