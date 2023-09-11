#ifndef AUXPORT_OSCILLATOR_H
#define AUXPORT_OSCILLATOR_H

#include "../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
namespace AuxPort
{
	namespace Audio
	{
		class Oscillator
		{
		public:
			Oscillator() = default;
			~Oscillator() = default;
			Oscillator(const Oscillator& osc) = default;
			virtual void setSampleRate(uint32_t sampleRate);
			virtual void setFrequency(uint32_t frequency);
			virtual float process();
			virtual void stop();
			virtual bool isPlaying();
		protected:
			uint32_t sampleRate;
			uint32_t frequency;
			float sample;
			float mod = 0;
			float inc = 0;
		};

		class Sine : public Oscillator
		{
		public:
			Sine() = default;
			~Sine() = default;
			Sine(const Sine& sine) = default;
			float process() override;
		};

		class UnipolarSawtooth : public Oscillator
		{
		public:
			UnipolarSawtooth() = default;
			~UnipolarSawtooth() = default;
			UnipolarSawtooth(const UnipolarSawtooth& saw) = default;
			float process() override;
		};

		class BipolarSawtooth : public Oscillator
		{
		public:
			BipolarSawtooth() = default;
			~BipolarSawtooth() = default;
			BipolarSawtooth(const BipolarSawtooth& bsaw) = default;
			float process() override;
		};

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

		class Triangle : public Oscillator
		{
		public:
			Triangle() = default;
			~Triangle() = default;
			Triangle(const Triangle& triangle) = default;
			float process() override;
		};

		class PolyBlepSaw : public Oscillator
		{
		public:
			PolyBlepSaw() = default;
			~PolyBlepSaw() = default;
			PolyBlepSaw(const PolyBlepSaw& pbs) = default;
			float process() override;
		};

		class PBSSaw : public Oscillator
		{
		public:
			PBSSaw() = default;
			~PBSSaw() = default;
			PBSSaw(const PBSSaw& pbs) = default;
			float process() override;
			void setSaturationLevel(float sat);
		private:
			float satLevel;
		};

	}
}

#endif