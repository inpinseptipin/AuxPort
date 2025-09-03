#ifndef AUXPORT_PARAM_H
#define AUXPORT_PARAM_H
#include <juce_audio_plugin_client/juce_audio_plugin_client.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_events/juce_events.h>
#include <juce_core/juce_core.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_devices/juce_audio_devices.h>
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
			enum PType
			{
				Integer,Floating,Boolean,Choice
			};
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
			void addParameter(juce::AudioProcessorParameter* parameter,PType ptype = PType::Floating);
/// ///	@brief Retrives the audio parameter corrosponding to the parameter ID and casts it to an AudioParameterFloat*
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
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Stores the parameter map into the memory block for the DAW to access
///////////////////////////////////////////////////////////////////////////////////////
			void getStateInformation(juce::MemoryBlock& destData);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Retrieves the memory block from the DAW and update the parameter map
///////////////////////////////////////////////////////////////////////////////////////
			void setStateInformation(const void* data, int sizeInBytes);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Saves the parameter space into a file
///////////////////////////////////////////////////////////////////////////////////////
			void saveToFile(const std::string& fileName);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Reads the parameter space from a file
///////////////////////////////////////////////////////////////////////////////////////
			void readFromFile(const std::string& fileName);
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Implement this function to update the UI of the plugin whenever a preset is loaded.
///////////////////////////////////////////////////////////////////////////////////////
			std::function<void()> updatePluginUI;
		private:
			struct ParameterData
			{
				float minValue;
				float maxValue;
				float interval;
			};
			std::unordered_map<std::string, uint32_t> parameters;
			std::unordered_map<std::string, ParameterData> parameterDataMap;
			juce::AudioProcessor* audioProcessor;
			juce::AudioProcessorParameter* getParameter(const std::string& parameterName);
			std::unique_ptr<AuxPort::CSV> csv;

		};
///////////////////////////////////////////////////////////////////////////////////////
///	@brief UI Component for Preset Loading and Saving.
///////////////////////////////////////////////////////////////////////////////////////
		class PresetMenu : public juce::Component
		{
		public:
			PresetMenu();
			~PresetMenu();
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Implement this function to update the UI of the plugin whenever a preset is loaded.
///////////////////////////////////////////////////////////////////////////////////////
			void handleParameterMap(AuxPort::Extensions::ParameterMap* parameterMap);
			void paint(juce::Graphics& g) override;
			void resized() override;
///////////////////////////////////////////////////////////////////////////////////////
///	@brief Set the file extension for the preset
///////////////////////////////////////////////////////////////////////////////////////
			void setPresetExtension(const std::string& presetExtension);
			std::function<void()> updatePluginUI;
		protected:
			AuxPort::Extensions::ParameterMap* parameterMap;
			juce::Label label;
			juce::TextButton loadPresetButton;
			juce::TextButton savePresetButton;
			std::unique_ptr<juce::FileChooser> fileChooser;
			std::string presetExtension;
		private:
			JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetMenu)
		};
	}



}
#endif
