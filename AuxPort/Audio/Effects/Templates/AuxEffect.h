#ifndef AUXEFFECT_H
#define AUXEFFECT_H

/*
*			AuxPort Library
            "Modules for Audio Software Development" - inpinseptipin

            BSD 3-Clause License

            Copyright (c) 2026, Satyarth Arora
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

/*===================================================================================*/



#include "../../../Core/Env/AuxEnv.h"
#include "../../../Core/Log/AuxLog.h"
#include "../../../Core/Utility/AuxUtility.h"
#include <vector>
#include <functional>

namespace AuxPort
{
	namespace Audio
	{
///////////////////////////////////////////////////////////////////////////////////////
/// @brief This class can be inherited in the design,development,analysis and benchmark an audio plugin
///////////////////////////////////////////////////////////////////////////////////////
        class Effect
        {
        public:
            Effect() = default;
            ~Effect() = default;
            Effect(const Effect& effect) = default;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief Provides the sample rate to the audio plugin
///////////////////////////////////////////////////////////////////////////////////////
            virtual void setSampleRate(float sampleRate);
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Virtual Function] Provides the parameters to the audio plugin
///////////////////////////////////////////////////////////////////////////////////////
            virtual void setParameters(const std::vector<float>& parameters);
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Virtual Function] Override this function to do analysis on the audio buffer
///////////////////////////////////////////////////////////////////////////////////////
            virtual void handleAudioProcessor(void* audioProcessor);
        protected:
            float sampleRate;
            std::vector<float> parameters;
        };


		class MonoEffect : public Effect
		{
		public:
///////////////////////////////////////////////////////////////////////////////////////
/// @brief This function processes a Mono Buffer
///////////////////////////////////////////////////////////////////////////////////////
            virtual void process(float* buffer, uint32_t bufferSize);
		protected:
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Pure Virtual Function] Override this function to write your DSP for a buffer filled with audio.
///////////////////////////////////////////////////////////////////////////////////////
			virtual void processBlock(float* buffer,uint32_t bufferSize) = 0;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Pure Virtual Function] Override this function to benchmark the DSP code...argument provides the computational time of the latest buffer
///////////////////////////////////////////////////////////////////////////////////////
			virtual void benchmarkBlock(float time) = 0;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Pure Virtual Function] Override this function to do analysis on the audio buffer
///////////////////////////////////////////////////////////////////////////////////////
			virtual void analysisBlock(const float* buffer, uint32_t bufferSize) = 0;
			AuxPort::Timer timer;
		};




        class StereoEffect : public Effect
        {
        public:
///////////////////////////////////////////////////////////////////////////////////////
/// @brief This function processes a Stereo Buffer
///////////////////////////////////////////////////////////////////////////////////////
            virtual void process(float* leftChannel,float* rightChannel, uint32_t bufferSize);
        protected:
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Pure Virtual Function] Implement this function and write the DSP for a stereo audio buffer
///////////////////////////////////////////////////////////////////////////////////////
            virtual void processBlock(float* leftChannel,float* rightChannel, uint32_t bufferSize) = 0;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Pure Virtual Function] Implement this function to handle benchmarking
///////////////////////////////////////////////////////////////////////////////////////
            virtual void benchmarkBlock(float time) = 0;
///////////////////////////////////////////////////////////////////////////////////////
/// @brief [Pure Virtual Function] Implement this function to analyse the processed audio buffer
///////////////////////////////////////////////////////////////////////////////////////
            virtual void analysisBlock(const float* leftChannel,const float* rightChannel,uint32_t bufferSize) = 0;
            AuxPort::Timer timer;
        };

        /**
         * This is an Abstract class with all methods that you can use to create your Digital Synthesizer Module.
         *  Subclass this and implement the virtual methods to implement your synthesizer
         */
        class Synthesizer : public AuxPort::Audio::Effect
        {
        public:
            Synthesizer() = default;
            ~Synthesizer() = default;
            Synthesizer(const Synthesizer& juceSynthesizer) = default;
        protected:
            /**
              @brief Converts a midi note number to the frequency it maps to.
              A4 = 69 = 440Hz is taken as reference to map all the midi notes with.
              @param midiNote
              @return 
              \code{.cpp}
              auto frequency = midiToFreq(69)
              \endcode 
             */
            float midiToFreq(uint32_t midiNote);
            /**
              @brief Sets the reference midi note and frequency combination 
              @param midiNote
              @param frequency
              \code{.cpp}
              configureMidiToFreq(69,440);
              \endcode 
             */
            void configureMidiToFreq(uint32_t midiNote, float frequency);
            /**
              @brief [Overridable] Implement this function to handle a particular midi event  
             */
            virtual void handleMidiEvent(void* midiMessage);
            /**
              @brief [Overridable] Implement this function to handle a midi note "on" event 
              @param midiMessage
             */
            virtual void handleNoteOn(void* midiMessage);
            /**
              @brief [Overridable] Implement this function to handle a midi note "off" event
              @param midiMessage
             */
            virtual void handleNoteOff(void* midiMessage);
             /**
              @brief [Overridable] Implement this function to handle a midi "All notes off" event
              @param midiMessage
             */
            virtual void handleAllNotesOff(void* midiMessage);
            float referenceFrequency = 440.0f;
            uint32_t referenceMidiNote = 69;
        };

        /**
            Inherit this class to your Effect and use it to find the optimal delay for Parallel FX Processing
         */
        class DelayTuner
        {    
        public:
            /**
              @brief Finds the location of the impulse in samples after it goes through a FX chain 
             */
            void findDelayPeak();

            void setNumberOfBlocks(int n);

            void setBlockBufferSize(size_t blockSize);
        protected:
            /**
                Implement this Lambda with your FX logic for the Delay Tuner to work.
             */
            std::vector<std::function<void()>> parallelBlockVector;
            std::vector<std::vector<float>> delayTunerBuffers;
            std::vector<float> delayValues;
        };
	}
}


#endif