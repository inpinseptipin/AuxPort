#ifndef AUXPORT_OSCILLATOR_H
#define AUXPORT_OSCILLATOR_H
#include "../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
#include "../Filters/AuxIIR.h"
#include <random>
#include <memory>
namespace AuxPort
{
	namespace Audio
	{
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Inheritable Class that provides common functions for all Digital Oscillators 
		///////////////////////////////////////////////////////////////////////////////////////
		class Oscillator
		{
		public:
			Oscillator() = default;
			~Oscillator() = default;
			Oscillator(const Oscillator& osc) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Use this function to set the sample rate of the oscillator [Overridable]
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void setSampleRate(uint32_t sampleRate);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Use this function to set the frequency of the oscillator [Overridable]
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void setFrequency(float frequency);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator [Overridable]
			///////////////////////////////////////////////////////////////////////////////////////
			virtual float process();

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Use this function to stop the Oscillator from generating samples [Overridable]
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void stop();

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Checks whether the Oscillator is still generating samples [Overridable]
			///////////////////////////////////////////////////////////////////////////////////////
			virtual bool isPlaying();
		protected:
			uint32_t sampleRate = 44100;
			float frequency = 100;
			float sample = 0;
			float mod = 0;
			float inc = 0;
		};


		class DetunableOscillator : public Oscillator
		{
		public:
			DetunableOscillator() = default;
			~DetunableOscillator() = default;
			DetunableOscillator(const DetunableOscillator& detunableOscillator) = default;
			virtual void setDetune(float semitones, float cents);
		};
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Sinusoidal Osciallator 
		///////////////////////////////////////////////////////////////////////////////////////
		class Sine : public DetunableOscillator
		{
		public:
			Sine() = default;
			~Sine() = default;
			Sine(const Sine& sine) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Unipolar Sawtooth
		///////////////////////////////////////////////////////////////////////////////////////
		class UnipolarSawtooth : public DetunableOscillator
		{
		public:
			UnipolarSawtooth() = default;
			~UnipolarSawtooth() = default;
			UnipolarSawtooth(const UnipolarSawtooth& saw) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Bipolar Sawtooth
		///////////////////////////////////////////////////////////////////////////////////////
		class BipolarSawtooth : public DetunableOscillator
		{
		public:
			BipolarSawtooth() = default;
			~BipolarSawtooth() = default;
			BipolarSawtooth(const BipolarSawtooth& bsaw) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Square Oscillator
		///////////////////////////////////////////////////////////////////////////////////////
		class Square : public DetunableOscillator
		{
		public:
			Square() = default;
			~Square() = default;
			Square(const Square& square) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Sets the pulse width for the Square Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			void setPulseWidth(float pulseWidth);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		private:
			float pulseWidth;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Triangle Oscillator
		///////////////////////////////////////////////////////////////////////////////////////
		class Triangle : public DetunableOscillator
		{
		public:
			Triangle() = default;
			~Triangle() = default;
			Triangle(const Triangle& triangle) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief PolyBlep Saw
		///////////////////////////////////////////////////////////////////////////////////////
		class PBSaw : public DetunableOscillator
		{
		public:
			PBSaw() = default;
			~PBSaw() = default;
			PBSaw(const PBSaw& pbs) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Poly BLEP Waveshape Saw
		///////////////////////////////////////////////////////////////////////////////////////
		class PBWSaw : public DetunableOscillator
		{
		public:
			PBWSaw() = default;
			~PBWSaw() = default;
			PBWSaw(const PBWSaw& pbs) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Sets the saturation level for the oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			void setSaturationLevel(float sat);
		private:
			float satLevel = 1;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief WhiteNoise Oscillator
		///////////////////////////////////////////////////////////////////////////////////////
		class WhiteNoise : public Oscillator
		{
		public:
			WhiteNoise();
			~WhiteNoise() = default;
			WhiteNoise(const WhiteNoise& wn) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;
		private:
			std::random_device randomDevice;
			std::unique_ptr<std::mt19937> gen;
			std::unique_ptr<std::uniform_real_distribution<>> distribution;
			
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief KPString Oscillator
		///////////////////////////////////////////////////////////////////////////////////////
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

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			float process() override;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function sets the sample rate
			///////////////////////////////////////////////////////////////////////////////////////
			void setSampleRate(uint32_t sampleRate) override;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function set the frequency of the oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			void setFrequency(float frequency) override;
		private:
			std::vector<float> seedBuffer;
			uint32_t r1 = 0;
			uint32_t r2 = 0;
			uint32_t seedSize = 0;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief ADSR Oscillator
		///////////////////////////////////////////////////////////////////////////////////////
		class ADSR
		{
		public:
			ADSR();
			~ADSR() = default;
			ADSR(const ADSR& adsr) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function sets the ADSR Oscillator Parameters
			///////////////////////////////////////////////////////////////////////////////////////
			void setParameters(const std::vector<float>& parameters);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function sets the sample rate
			///////////////////////////////////////////////////////////////////////////////////////
			void setSampleRate(uint32_t sampleRate);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns true if the oscillator is currently not in OFF State
			///////////////////////////////////////////////////////////////////////////////////////
			bool isPlaying();

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Starts the oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			void start();

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Stops the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
			void stop();

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief This function generates the sample from the Oscillator
			///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
/// @brief Fast Sine Approximation using a second-order FeedForward Filters
///////////////////////////////////////////////////////////////////////////////////////
		class FastSine : public Oscillator
		{
		public:
			FastSine() = default;
			~FastSine() = default;
			FastSine(const FastSine& fastSine) = default;
			void setFrequency(float frequency) override;
			float process() override;
			void stop() override;
		private:
			float x1 = 0;
			float x0 = 0;
			float x2 = 0;
			float a = 0;
		};
	}
}

#endif