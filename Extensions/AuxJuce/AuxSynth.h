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


///////////////////////////////////////////////////////////////////////////////////////
/// @brief This class implements a Polyphonic Synthesizer (Uses the JUCE Framework)
///////////////////////////////////////////////////////////////////////////////////////
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
			virtual void render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample) = 0;
			void copyMonoToAll(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample);
			AuxPort::Extensions::ParameterMap* parameterMap;
		};


		class SimplePolyphony : public JuceSynthesizer
		{
		public:
			/**
			///////////////////////////////////////////////////////////////////////////////////////
			 * \brief [Overridable] Sets the Sample Rate to the Synthesizer
			 * 
			 * \param sampleRate
			///////////////////////////////////////////////////////////////////////////////////////
			 */
			void setSampleRate(float sampleRate) override;
			/**
			///////////////////////////////////////////////////////////////////////////////////////
			 * \brief [Overridable] Attaches an Audio Processor or Parameter Map to the Synthesizer
			 * 
			 * \param parameterMap
			///////////////////////////////////////////////////////////////////////////////////////
			 */
			void handleAudioProcessor(void* parameterMap) override;
		protected:
			/**
			///////////////////////////////////////////////////////////////////////////////////////
			 * \brief [Pure Virtual] Renders a Juce::AudioBuffer with Synthesizer output
			 * 
			 * \param buffer
			 * \param startSample
			 * \param endSample
			///////////////////////////////////////////////////////////////////////////////////////
			 */
			void render(juce::AudioBuffer<float>& buffer, uint32_t startSample, uint32_t endSample) override;
			/**
			///////////////////////////////////////////////////////////////////////////////////////
			 * \brief [Pure Virtual] Implement this function to handle midi note on
			 * \param midiMessage - Cast this to the appropriate MidiObject class
			  
			  
			 
			 * \code{.cpp}
			  	auto midi = static_cast<juce::MidiMessage*>(midiMessage);
				oscillator[midi->getNoteNumber()].setFrequency(midiToFreq(midi->getNoteNumber()));
				\endcode
			///////////////////////////////////////////////////////////////////////////////////////
			 */
			void handleNoteOn(void* midiMessage) override;
			void handleNoteOff(void* midiMessage) override;
			void handleAllNotesOff(void* midiMessage) override;
			std::vector<AuxPort::Audio::Sine::Sine> oscillator;
		};

	}
}


#endif