#include "AuxOscillator.h"

void AuxPort::Audio::Oscillator::setSampleRate(uint32_t sampleRate)
{
	this->sampleRate = sampleRate;
	init();
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
	init();
}

bool AuxPort::Audio::Oscillator::isPlaying()
{
	return inc != 0;
}

void AuxPort::Audio::Oscillator::setStartingPhase(float phaseInDegrees)
{
	startingPhase = AuxPort::Utility::degreesToRadians<float>(phaseInDegrees);
}

void AuxPort::Audio::Oscillator::init()
{
	mod = 0;
}

void AuxPort::Audio::TunableOscillator::setDetune(float semitones, float cents)
{
	inc = this->frequency * (powf(2, (semitones * 100 + cents) / 1200));
	inc /= static_cast<float>(this->sampleRate);
}

void AuxPort::Audio::TunableOscillator::setPhaseOffset(float phaseOffset)
{
	AuxAssert(phaseOffset < -1.0f || phaseOffset > 1.0f, "Phase offsets can't be greater than -1 and 1");
	AuxAssert(1 == 1, "Implement this method");
}

void AuxPort::Audio::Sine::Sine::init()
{
	mod = startingPhase * 0.159155f;
}


float AuxPort::Audio::Sine::Sine::process()
{
	sample = isPlaying() ? sinf(2*pi*mod) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}



float AuxPort::Audio::Sine::AuxSine::process()
{
	x = 2.0f * mod - 1.0f;
	sample = isPlaying() ? x + x*x*x*(0.5f*x*x-1.0f-0.5f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}

float AuxPort::Audio::Sine::AuxSine2::process()
{
	x = 2 * pi * mod;
	sample = isPlaying() ? (x >= 0 && x < 0.5 * pi ? x / pi * (pi - powf((2 * x) / pi, 2) * ((2 * pi - 5) - powf((2 * x) / pi, 2) * (pi - 3))) : sample):0.0f;
	sample = isPlaying() ? (x > 0.5 * pi && x < pi ? - (x-pi) / pi * (pi - powf((2 * (x-pi)) / pi, 2) * ((2 * pi - 5) - powf((2 * (x-pi)) / pi, 2) * (pi - 3))) : sample) : 0.0f;
	sample = isPlaying() ? (x >= pi && x < 1.5*pi ? - (x - pi) / pi * (pi - powf((2 * (x - pi)) / pi, 2) * ((2 * pi - 5) - powf((2 * (x - pi)) / pi, 2) * (pi - 3))) : sample) : 0.0f;
	sample = isPlaying() ? (x >= 1.5*pi && x < 2*pi ? (x-2*pi) / pi * (pi - powf((2 * (x-2*pi)) / pi, 2) * ((2 * pi - 5) - powf((2 * (x-2*pi)) / pi, 2) * (pi - 3))) : sample) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}


float AuxPort::Audio::Sine::ParabolicSine::process()
{
	sample = isPlaying() ? B * mod + C * mod * abs(mod) : 0.0f;
	mod = mod >= pi ? -pi : mod + inc;
	sample = P * (sample * abs(sample) - sample) + sample;
	return sample;
}


float AuxPort::Audio::Sine::BhaskaraSine::process()
{
	modToPi = mod > 0.5f ? 2.0f * pi * (mod - 0.5f) : 2.0f * pi * mod;
	sample = isPlaying() ? (16.0f * modToPi * (pi - modToPi)) / (5.0f * pi * pi - 4.0f * modToPi * (pi - modToPi)):0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return mod > 0.5 ? -sample:sample;
}


float AuxPort::Audio::Sine::JavidX9Sine::process()
{
	sample = isPlaying() ? (mod <= 0.5 ? (-16.0f*mod * mod) + (8.0f * mod) : (16.0f*mod * mod) - (24.0f*mod) + 8.0f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}


float AuxPort::Audio::Sine::JavidX9Sine2::process()
{
	sample = isPlaying() ? 20.785f * mod * (mod-0.5f) * (mod-1.0f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}


void AuxPort::Audio::Sine::FastSine::setFrequency(float frequency)
{
	this->frequency = frequency;
	a = 2 * cosf(2 * pi * this->frequency / this->sampleRate);
	x1 = sinf(2 * pi * this->frequency / this->sampleRate);
	inc = this->frequency / this->sampleRate;
}

float AuxPort::Audio::Sine::FastSine::process()
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

void AuxPort::Audio::Sine::FastSine::stop()
{
	x0 = 0;
	x1 = 0;
	x2 = 0;
	inc = 0;
}

float AuxPort::Audio::Sawtooth::UnipolarSawtooth::process()
{
	sample = isPlaying() ? mod : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}

float AuxPort::Audio::Sawtooth::SawSin2::process()
{
	sample = isPlaying() ? ((mod <=0) ? -sinf(pi * mod) : 2.0f * mod - powf(mod, 2) - 1.0f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}


float AuxPort::Audio::Sawtooth::SawSin1::process()
{
	sample = isPlaying() ? ((mod > 0.5) ? -sinf(2 * pi * mod) : 2.0f * mod - 1.0f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}

void AuxPort::Audio::Square::Square::setPulseWidth(float pulseWidth)
{
	this->pulseWidth = pulseWidth / 100;
}

float AuxPort::Audio::Square::Square::process()
{
	sample = isPlaying() ? ((mod > pulseWidth) ? -1.0f : 1.0f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}

float AuxPort::Audio::Sawtooth::BipolarSawtooth::process()
{
	sample = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}

float AuxPort::Audio::Triangle::Triangle::process()
{
	sample = isPlaying() ? 2.0f * fabs(2.0f * mod - 1.0f) - 1.0f : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	return sample;
}

float AuxPort::Audio::Sawtooth::PBSaw::process()
{
	sample = isPlaying() ? ((mod >= -1 && mod <= 0) ? (mod * mod) + 2.0f * mod + 1.0f : 2.0f * mod - powf(mod, 2) - 1.0f) : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod)-1.0f;
	return sample;
}

#if AUXPORT_EXP
float AuxPort::Audio::Square::PBSquare::process()
{
	square = isPlaying() ? ((mod > pulseWidth) ? -1.0f : 1.0f) : 0.0f;
	sample = isPlaying() ? ((mod >= -1 && mod <= 0) ? (mod * mod) + 2.0f * mod + 1.0f : 2.0f * mod - powf(mod, 2) - 1.0f) : 0.0f;
	mod = mod >= 1 ? -1 : mod + inc;
	modx1 = (mod + 0.5) >= 1 ? -1 : mod + 0.5;
	x1 = isPlaying() ? ((modx1 >= -1 && modx1 <= 0) ? (modx1 * modx1) + 2.0f * modx1 + 1.0f : 2.0f * modx1 - powf(modx1, 2) - 1.0f) : 0.0f;
	sample = square + (sample - x1);
	return (sample);
}
#endif
void AuxPort::Audio::Sawtooth::DPWSaw::setFrequency(float frequency)
{
	this->frequency = frequency;
	this->inc = static_cast<float>(this->frequency) / static_cast<float>(this->sampleRate);
	c = this->sampleRate / (4 * this->frequency * (1 - inc));
}


float AuxPort::Audio::Triangle::DPWTriangle1::process()
{
	sample = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	sample = abs(sample);
	sample = 0.5f- sample;
	sample = sample * 2;
	return sample;
}

float AuxPort::Audio::Sawtooth::DPWSaw::process()
{
	x = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod += inc;
	mod = mod - static_cast<int>(mod);
	x *= x;
	sample = x - x1;
	x1 = x;
	return sample * c;
}


#if AUXPORT_EXP
float AuxPort::Audio::Triangle::DPWTriangle2::process()
{
	x = isPlaying() ? 2.0f * mod - 1.0f : 0.0f;
	mod = mod >= 1.0f ? 0.0f : mod + inc;
	x *= x;
	sample = x - x1;
	x1 = x;
	return sample * c;
}
#endif

float AuxPort::Audio::Sawtooth::PBWSaw::process()
{
	sample = isPlaying() ? ((mod >= -1 && mod <= 0) ? tanhf(satLevel * (mod * mod) + 2.0f * mod + 1.0f) : tanhf(2.0f * mod - powf(mod, 2) - 1.0f)) : 0.0f;
	sample *= satVal;
	mod += inc;
	mod = mod - static_cast<int>(mod)-1.0f;
	return sample;
}

void AuxPort::Audio::Sawtooth::PBWSaw::setSaturationLevel(float sat)
{
	this->satLevel = sat;
	this->satVal = 1 / tanhf(satLevel);
}



float AuxPort::Audio::Noise::WhiteNoise2::process()
{
	return isPlaying() ? getRandomFloat(-1, 1) : 0.0f;
}






#if AUXPORT_EXP
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

AuxPort::Audio::String::KPString::KPString()
{
	seedBuffer.resize(sampleRate);
}

float AuxPort::Audio::String::KPString::process()
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

void AuxPort::Audio::String::KPString::setSampleRate(uint32_t sampleRate)
{
	if (this->sampleRate != sampleRate)
	{
		this->sampleRate = sampleRate;
		seedBuffer.resize(sampleRate);
		std::fill(seedBuffer.begin(), seedBuffer.end(), 0.0);
	}
}

void AuxPort::Audio::String::KPString::setFrequency(float frequency)
{
	seedSize = static_cast<uint32_t>(this->sampleRate / frequency);
	inc = frequency / sampleRate;
	AuxPort::Utility::generateRandomValues<float>(seedBuffer);
}

#endif


