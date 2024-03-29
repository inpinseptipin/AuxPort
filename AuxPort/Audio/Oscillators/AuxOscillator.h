#ifndef AUXPORT_OSCILLATOR_H
#define AUXPORT_OSCILLATOR_H

#include "../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
#include "../Filters/AuxIIR.h"
#include <random>
namespace AuxPort
{
	namespace Audio
	{
///////////////////////////////////////////////////////////////////////////////////////
/// [Abstract Class] Inheritable function that provides common functions for all Digital Oscillators 
///////////////////////////////////////////////////////////////////////////////////////
		class Oscillator
		{
		public:
			Oscillator() = default;
			~Oscillator() = default;
			Oscillator(const Oscillator& osc) = default;
///////////////////////////////////////////////////////////////////////////////////////
/// Use this function to set the sample rate of the oscillator [Overridable]
///////////////////////////////////////////////////////////////////////////////////////
			virtual void setSampleRate(uint32_t sampleRate);
///////////////////////////////////////////////////////////////////////////////////////
/// Use this function to set the frequency of the oscillator [Overridable]
///////////////////////////////////////////////////////////////////////////////////////
			virtual void setFrequency(float frequency);
///////////////////////////////////////////////////////////////////////////////////////
/// This function generates the sample from the Oscillator [Overridable]
///////////////////////////////////////////////////////////////////////////////////////
			virtual float process();
///////////////////////////////////////////////////////////////////////////////////////
/// Use this function to stop the Oscillator from generating samples [Overridable]
///////////////////////////////////////////////////////////////////////////////////////
			virtual void stop();
///////////////////////////////////////////////////////////////////////////////////////
/// Checks whether the Oscillator is still generating samples [Overridable]
///////////////////////////////////////////////////////////////////////////////////////
			virtual bool isPlaying();
		protected:
			uint32_t sampleRate = 44100;
			float frequency = 100;
			float sample = 0;
			float mod = 0;
			float inc = 0;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] Sinusoidal Osciallator 
///////////////////////////////////////////////////////////////////////////////////////
		class Sine : public Oscillator
		{
		public:
			Sine() = default;
			~Sine() = default;
			Sine(const Sine& sine) = default;
			float process() override;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] Unipolar Sawtooth
///////////////////////////////////////////////////////////////////////////////////////
		class UnipolarSawtooth : public Oscillator
		{
		public:
			UnipolarSawtooth() = default;
			~UnipolarSawtooth() = default;
			UnipolarSawtooth(const UnipolarSawtooth& saw) = default;
			float process() override;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] Bipolar Sawtooth
///////////////////////////////////////////////////////////////////////////////////////
		class BipolarSawtooth : public Oscillator
		{
		public:
			BipolarSawtooth() = default;
			~BipolarSawtooth() = default;
			BipolarSawtooth(const BipolarSawtooth& bsaw) = default;
			float process() override;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] Square
///////////////////////////////////////////////////////////////////////////////////////
		class Square : public Oscillator
		{
		public:
			Square() = default;
			~Square() = default;
			Square(const Square& square) = default;
			void setPulseWidth(float pulseWidth);
			float process() override;
		private:
			float pulseWidth;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] Triangle
///////////////////////////////////////////////////////////////////////////////////////
		class Triangle : public Oscillator
		{
		public:
			Triangle() = default;
			~Triangle() = default;
			Triangle(const Triangle& triangle) = default;
			float process() override;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] PolyBlep Saw
///////////////////////////////////////////////////////////////////////////////////////
		class PBSaw : public Oscillator
		{
		public:
			PBSaw() = default;
			~PBSaw() = default;
			PBSaw(const PBSaw& pbs) = default;
			float process() override;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] Poly BLEP Waveshape Saw
///////////////////////////////////////////////////////////////////////////////////////
		class PBWSaw : public Oscillator
		{
		public:
			PBWSaw() = default;
			~PBWSaw() = default;
			PBWSaw(const PBWSaw& pbs) = default;
			float process() override;
			void setSaturationLevel(float sat);
		private:
			float satLevel;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] WhiteNoise Oscillator
///////////////////////////////////////////////////////////////////////////////////////
		class WhiteNoise : public Oscillator
		{
		public:
			WhiteNoise();
			~WhiteNoise() = default;
			WhiteNoise(const WhiteNoise& wn) = default;
			float process() override;
		private:
			std::random_device randomDevice;
			std::unique_ptr<std::mt19937> gen;
			std::unique_ptr<std::uniform_real_distribution<>> distribution;
			
		};

		class KPString : public Oscillator
		{
		public:
			enum Parameters
			{
				Pick
			};
			KPString();
			~KPString() = default;
			KPString(const KPString& kpstring) = default;
			float process() override;
			void setSampleRate(uint32_t sampleRate) override;
			void setFrequency(float frequency) override;
		private:
			std::vector<float> seedBuffer;
			uint32_t r1 = 0;
			uint32_t r2 = 0;
			uint32_t seedSize = 0;
		};

///////////////////////////////////////////////////////////////////////////////////////
/// [Class] ADSR Oscillator
///////////////////////////////////////////////////////////////////////////////////////
		class ADSR
		{
		public:
			ADSR();
			~ADSR() = default;
			ADSR(const ADSR& adsr) = default;
			void setParameters(const std::vector<float>& parameters);
			void setSampleRate(uint32_t sampleRate);
			bool isPlaying();
			void start();
			void stop();
			float process();
		private:
			enum State
			{
				Attack,Decay,Sustain,Release,AttackTime,DecayTime,SustainTime,ReleaseTime,OFF
			};
			std::vector<float> parameters;
			std::vector<float> mods;
			uint32_t sampleRate;
			float envelope;
			State state = State::OFF;
			uint32_t count = 0;
		};

		

	}
}

#endif