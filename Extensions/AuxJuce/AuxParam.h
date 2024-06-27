#ifndef AUXPORT_PARAM_H
#define AUXPORT_PARAM_H
#include "JuceHeader.h"
#include "AuxPort.h"
namespace AuxPort
{
	namespace Extensions
	{
		class ParameterMap
		{
		public:
			ParameterMap() = default;
			ParameterMap(juce::AudioProcessor* audioProcessor);
			~ParameterMap() = default;
			ParameterMap(const ParameterMap& parameterMap) = default;
			void addParameter(juce::AudioParameterBool* boolParam);
			void addParameter(juce::AudioParameterFloat* floatParam);
			void addParameter(juce::AudioParameterInt* intParam);
			juce::AudioParameterFloat* getFloatParameter(const std::string& parameterName);
			juce::AudioParameterBool* getBoolParameter(const std::string& parameterName);
			juce::AudioParameterInt* getIntParameter(const std::string& parameterName);
			void save();
			enum type
			{
				aBool, aFloat, aInt
			};
		private:
			class Parameter
			{
			public:
				Parameter() = default;
				~Parameter() = default;
				Parameter(const Parameter& param) = default;
				Parameter(size_t index, const AuxPort::Extensions::ParameterMap::type& paramType, const std::string& paramName);
				std::string getParameterName();
				uint32_t getParameterPosition();
				AuxPort::Extensions::ParameterMap::type getParameterType();
			private:
				uint32_t parameterPosition;
				AuxPort::Extensions::ParameterMap::type parameterType;
				std::string parameterName;
			};
			juce::AudioProcessor* audioProcessor;
			std::vector<juce::AudioParameterBool*> boolParameters;
			std::vector<juce::AudioParameterFloat*> floatParameters;
			std::vector<juce::AudioParameterInt*> intParameters;
			std::vector<AuxPort::Extensions::ParameterMap::Parameter> map;

		};
	}
}
#endif
