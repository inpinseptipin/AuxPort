#ifndef AUXPORT_PARAM_H
#define AUXPORT_PARAM_H
#include "JuceHeader.h"
#include "AuxPort.h"

/*
			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2024, Satyarth Arora
			All rights reserved.

			Redistribution and use in source and binary forms, with or without
			modification, are permitted provided that the following conditions are met:

			1. Redistributions of source code must retain the above copyright notice, this
			   list of conditions and the following disclaimer.

			2. Redistributions in binary form must reproduce the above copyright notice,
			   this list of conditions and the following disclaimer in the documentation
			   and/or other materials provided with the distribution.

			3. Neither the name of the copyright holder nor the names of its
			   contributors may be used to endorse or promote products derived from
			   this software without specific prior written permission.

			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
			AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
			FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
			DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


namespace AuxPort
{
///////////////////////////////////////////////////////////////////////////////////////
///	@brief This namespace contain extensions to other C++ Libraries
///////////////////////////////////////////////////////////////////////////////////////
	namespace Extensions
	{
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Parameter Map is an extension to JUCE, and provides Audio Parameter management for Audio Plugins
///////////////////////////////////////////////////////////////////////////////////////
		class ParameterMap
		{
		public:
			ParameterMap() = default;
			~ParameterMap() = default;
			ParameterMap(const ParameterMap& parameterMap) = default;
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Links the Parameter map with the Audio processor which owns the parameters
///////////////////////////////////////////////////////////////////////////////////////
			void addAudioProcessor(juce::AudioProcessor* audioProcessor);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Adds the parameter to the map, this function also adds it to the linked audio processor
///////////////////////////////////////////////////////////////////////////////////////
			void addParameter(juce::AudioProcessorParameter* parameter);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Retrives the audio parameter corrosponding to the parameter ID and casts it to an AudioParameterFloat*
///////////////////////////////////////////////////////////////////////////////////////
			juce::AudioParameterFloat* getFloatParameter(const std::string& parameterID);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Retrives the audio parameter corrosponding to the parameter ID and casts it to an AudioParameterInt*
///////////////////////////////////////////////////////////////////////////////////////
			juce::AudioParameterInt* getIntParameter(const std::string& parameterID);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Retrives the audio parameter corrosponding to the parameter ID and casts it to an AudioParameterBool*
///////////////////////////////////////////////////////////////////////////////////////
			juce::AudioParameterBool* getBoolParameter(const std::string& parameterID);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Retrives the audio parameter corrosponding to the parameter ID and casts it to an AudioParameterChoice*
///////////////////////////////////////////////////////////////////////////////////////
			juce::AudioParameterChoice* getChoiceParameter(const std::string& parameterID);
		private:
			std::unordered_map<std::string, uint32_t> parameters;
			juce::AudioProcessor* audioProcessor;
			juce::AudioProcessorParameter* getParameter(const std::string& parameterName);
		};
	}
}
#endif
