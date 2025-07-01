#ifndef AUXPORT_SYNTH_H
#define AUXPORT_SYNTH_H
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
#include "AuxParam.h"
namespace AuxPort
{
	namespace Extensions
	{
/// @brief This class implements a Polyphonic Synthesizer (Uses the Juce AudioBuffer Object)
		class JuceSynthesizer : public AuxPort::Audio::Synthesizer
		{
		public:
			JuceSynthesizer() = default;
			~JuceSynthesizer() = default;
			JuceSynthesizer(const JuceSynthesizer& juceSynthesizer) = default;
			void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer);
			void attachParameterMap(AuxPort::Extensions::ParameterMap* parameterMap);
		protected:
			virtual void handleMidiEvent(void* midiMessage) override;
			/**
			 @brief [Pure Virtual] Renders a Juce::AudioBuffer with Synthesizer output
			 @param buffer
			 @param startSample
			 @param endSample
			 @details
			 Example Definition
			\code{.cpp}
				void render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample)
				{
					auto firstChannel = buffer.getWritePointer(0);
					for (uint32_t i = 0; i < oscillator.size(); i++)
					{
						if (oscillator[i].isPlaying())
						{
							for (uint32_t k = startSample; k < endSample; k++)
							{
								firstChannel[k] += oscillator[i].process();
							}
						}
					}
				}
			\endcode
			 */
			virtual void render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample) = 0;
			/**
			   @brief Copies the first channel (Mono) to all valid channels in the Juce::AudioBuffer grid
			   @param buffer
			   @param startSample
			   @param endSample
			   @details
			   Example Definition/Implementation
			   Following is an example on if you want copy [0,N] samples from the first channel to l
			   \code{.cpp}
			   
			   \endcode 
			*/
			void copyMonoToAll(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample);
			/**
			   @brief [Overridable] Reimplement this function to handle how you want to mix the channels.
			   @param buffer
			   @details
			   Example Definition/Implementation
			   \code{.cpp}
			   
			   \endcode 
			*/
			virtual void mix(juce::AudioBuffer<float>& buffer);
			AuxPort::Extensions::ParameterMap* parameterMap = nullptr;
		};


		class SimplePolyphony : public JuceSynthesizer
		{
		public:
			/**
			   @brief [Constructor] Use this constructor to initialize your oscillators or any objects related to your Synthesizer
			   @details
			   Example Definition/Implementation
			   Following code snippet initalizes 128 objects of the oscillator (Polyphony mode : MIDI 1.0 Compatibility)
			   \code{.cpp}
				SimplePolyphony()
				{
					oscillator.resize(128);
				}
			   \endcode 
			*/
			SimplePolyphony();
			~SimplePolyphony() = default;
			SimplePolyphony(const SimplePolyphony& simplePolyphony) = default;
			/**
			   @brief [Overridable] Reimplement this function to set the sample rate to your oscillators
			   @param sampleRate
			   @details
			   Example Definition/Implementation
			   \code{.cpp}
			   void setSampleRate(float sampleRate)
			   {
					this->sampleRate = sampleRate;
					for (uint32_t i = 0; i < oscillator.size(); i++)
						this->oscillator[i].setSampleRate(sampleRate);
			   }
			   \endcode 
			*/
			void setSampleRate(float sampleRate) override;
			/**
			   @brief [Overridable] Attach a parameter map or an audio processor that has access to parameters.
			   @param parameterMap
			   @details
			   Example Definition/Implementation
			   Attach an AuxPort::ParameterMap to the Synthesizer by casting the void*
			   \code{.cpp}
			   void handleAudioProcessor(void* parameterMap) override
			   {
					this->parameterMap = static_cast<AuxPort::Extensions::ParameterMap*>(parameterMap);
			   }
			   \endcode 
			*/
			void handleAudioProcessor(void* parameterMap) override;
		protected:
			/**
			 @brief [Pure Virtual] Renders a Juce::AudioBuffer with Synthesizer output
			 @param buffer
			 @param startSample
			 @param endSample
			 @details
			 Example Definition
			\code{.cpp}
				void render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample)
				{
					auto firstChannel = buffer.getWritePointer(0);
					for (uint32_t i = 0; i < oscillator.size(); i++)
					{
						if (oscillator[i].isPlaying())
						{
							for (uint32_t k = startSample; k < endSample; k++)
							{
								firstChannel[k] += oscillator[i].process();
							}
						}
					}
				}
			\endcode
			 */
			void render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample) override;
			void handleNoteOn(void* midiMessage) override;
			void handleNoteOff(void* midiMessage) override;
			void handleAllNotesOff(void* midiMessage) override;
			std::vector<AuxPort::Audio::Sine::Sine> oscillator;
		};

	}
}


#endif