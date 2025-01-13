#include "AuxOscillator.h"

void AuxPort::Audio::Oscillator::setSampleRate(uint32_t sampleRate)
{
	this->sampleRate = sampleRate;
}

void AuxPort::Audio::Oscillator::setFrequency(float frequency)
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
	sample = isPlaying() ? sinf(2 * pi * mod) : 0.0f;
	mod = mod >= 1 ? 0 : mod + inc;
	return sample;
}

float AuxPort::Audio::UnipolarSawtooth::process()
{
	sample = isPlaying() ? mod : 0.0f;
	mod = mod >= 1 ? 0.0 : mod + inc;
	return sample;
}

void AuxPort::Audio::Square::setPulseWidth(float pulseWidth)
{
	this->pulseWidth = pulseWidth / 100;
}

float AuxPort::Audio::Square::process()
{
	sample = isPlaying() ? ((mod > pulseWidth) ? -1.0f : 1.0f) : 0.0f;
	mod = mod >= 1 ? 0.0 : mod + inc;
	return sample;
}

float AuxPort::Audio::BipolarSawtooth::process()
{
	sample = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod = mod >= 1.0f ? 0.0f : mod + inc;
	return sample;
}

float AuxPort::Audio::Triangle::process()
{
	sample = isPlaying() ? 2.0f * fabs(2.0f * mod - 1.0f) - 1.0f : 0.0f;
	mod = mod >= 1.0f ? 0.0f : mod + inc;
	return sample;
}

float AuxPort::Audio::PBSaw::process()
{
	sample = isPlaying() ? ((mod >= -1 && mod <= 0) ? (mod * mod) + 2.0f * mod + 1.0f : 2.0f * mod - powf(mod, 2) - 1.0f) : 0.0f;
	mod = mod >= 1 ? -1 : mod + inc;
	return sample;
}

void AuxPort::Audio::DPWSaw::setFrequency(float frequency)
{
	this->frequency = frequency;
	this->inc = static_cast<float>(this->frequency) / static_cast<float>(this->sampleRate);
	c = static_cast<float>(sampleRate) / (4 * frequency * (1 - inc));
}

void AuxPort::Audio::DPWTriangle::setDetune(float semitones, float cents)
{
	inc = this->frequency * (powf(2, (semitones * 100 + cents) / 1200));
	inc /= static_cast<float>(this->sampleRate);
	square.setDetune(semitones, cents);
}

void AuxPort::Audio::DPWTriangle::setFrequency(float frequency)
{
	this->frequency = frequency;
	this->inc = static_cast<float>(this->frequency) / static_cast<float>(this->sampleRate);
	c = static_cast<float>(sampleRate) / (4 * frequency * (1 - inc));
	square.setFrequency(inc);
	square.setPulseWidth(50);
}

float AuxPort::Audio::DPWTriangle::process()
{
	x = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod = mod >= 1.0f ? 0.0f : mod + inc;
	x *= x;
	x = 1 - x;
	x *= square.process();
	sample = x - x1;
	x1 = x;
	return sample * c;
}

float AuxPort::Audio::DPWSaw::process()
{
	x = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod = mod >= 1.0f ? 0.0f : mod + inc;
	x *= x;
	sample = x - x1;
	x1 = x;
	return sample * c;
}



float AuxPort::Audio::PBWSaw::process()
{
	sample = isPlaying() ? tanhf(satLevel * (2.0f * mod - 1.0f)) / tanhf(satLevel) : 0.0f;
	mod = mod >= 1.0f ? 0.0f : mod + inc;
	return sample;
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
	return isPlaying() ? static_cast<float>(distribution->operator()(*gen)) : 0.0f;
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

AuxPort::Audio::KPString::KPString()
{
	seedBuffer.resize(sampleRate);
}

float AuxPort::Audio::KPString::process()
{
	if (isPlaying())
	{
		r2 = r1 + 1;
		r2 = r2 > seedSize ? r2 = 0 : r2;
		seedBuffer[r1] = 0.95f * (seedBuffer[r1] + seedBuffer[r2]) / 2.0f;
		r1++;
		r1 = r1 > seedSize ? r1 = 0 : r1;
		return seedBuffer[r1];
	}
	return 0.0f;
}

void AuxPort::Audio::KPString::setSampleRate(uint32_t sampleRate)
{
	if (this->sampleRate != sampleRate)
	{
		this->sampleRate = sampleRate;
		seedBuffer.resize(sampleRate);
		std::fill(seedBuffer.begin(), seedBuffer.end(), 0.0);
	}
}

void AuxPort::Audio::KPString::setFrequency(float frequency)
{
	seedSize = static_cast<uint32_t>(this->sampleRate / frequency);
	inc = frequency / sampleRate;
	AuxPort::Utility::generateRandomValues<float>(seedBuffer);
}

void AuxPort::Audio::FastSine::setFrequency(float frequency)
{
	this->frequency = frequency;
	a = 2 * cosf(2 * pi * this->frequency / this->sampleRate);
	x1 = sinf(2 * pi * this->frequency / this->sampleRate);
	inc = this->frequency / this->sampleRate;
}

float AuxPort::Audio::FastSine::process()
{
	if (isPlaying())
	{
		sample = x1;
		x0 = x1 * a - x2;
		x2 = x1;
		x1 = x0;
		return sample;
	}
	return 0.0f;
}

void AuxPort::Audio::FastSine::stop()
{
	x0 = 0;
	x1 = 0;
	x2 = 0;
	inc = 0;
}

void AuxPort::Audio::TunableOscillator::setDetune(float semitones, float cents)
{
	inc = this->frequency * (powf(2, (semitones*100 + cents) / 1200));
	inc /= static_cast<float>(this->sampleRate);
}

void AuxPort::Audio::TunableOscillator::setPhaseOffset(float phaseOffset)
{
	AuxAssert(phaseOffset < -1.0f || phaseOffset > 1.0f, "Phase offsets can't be greater than -1 and 1");
	AuxAssert(1 == 1, "Implement this method");
}


