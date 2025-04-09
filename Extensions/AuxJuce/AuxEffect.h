#ifndef AUXJUCE_EFFECT_H
#define AUXJUCE_EFFECT_H

#include <juce_audio_processors/juce_audio_processors.h>
#include "AuxPort.h"
#include "AuxParam.h"

namespace AuxPort
{
	namespace Extensions
	{
		class JuceEffect : public AuxPort::Audio::Effect
		{
		public:
			JuceEffect() = default;
			~JuceEffect() = default;
			JuceEffect(const JuceEffect& juceEffect) = default;
			virtual void process(juce::AudioBuffer<float>& buffer) = 0;
			void setParameterNames(const std::vector<std::string>& parameterNames);
			void handleAudioProcessor(void* audioProcessor) override;
		protected:
			AuxPort::Extensions::ParameterMap* parameterMap;
			std::vector<std::string> parameterNames;
		};
	}
}

namespace JuceExamples
{
	class Gain : public AuxPort::Extensions::JuceEffect
	{
	public:
		enum Parameters
		{
			outputGain
		};
		Gain() = default;
		~Gain() = default;
		Gain(const Gain& gain) = default;
		void process(juce::AudioBuffer<float>& buffer) override;
	};
}


#endif
