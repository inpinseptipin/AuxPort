#ifndef AUXPORT_IIR_H
#define AUXPORT_IIR_H
/*
*			AuxPort Library
            "Modules for Audio Software Development" - inpinseptipin

            BSD 3-Clause License

            Copyright (c) 2025, Satyarth Arora
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


#ifdef JUCE
#include "JuceHeader.h"
#endif

#define _USE_MATH_DEFINES  // To enable Math constants in MSVC 
#include <math.h>
#include <vector>
#include "../../Core/Utility/AuxUtility.h"

namespace AuxPort
{
    namespace Audio
    {
        /**
         @brief This namespace contains IIR Filter Classes
        */
        namespace IIR
        {  
            /**
             * @brief Base class for all IIR Filters in AuxPort
             */
            class IIRFilter
            {
            public:
                /**
                 @brief Generalized enum for all filter types
                 */
                enum Type
                {
                    Lowpass,Highpass,Bandpass,BandReject,Notch,LowShelf,HighShelf,Allpass
                };
                IIRFilter() = default;
                ~IIRFilter() = default;
                IIRFilter(const IIRFilter& iirFilter) = default;
                /**
                  @brief Use this function to set the sample rate for the filter 
                  @param sampleRate
                 */
                void setSampleRate(float sampleRate);
                /**
                  @brief Use this function to set the type of filter during runtime 
                  @param type
                 */
                void setFilterType(Type type);
                /**
                  @brief Use this function to update the parameters for the filter [Overridable]
                  @param parameters
                 */
                virtual void prepareToPlay(const std::vector<float>& parameters);
                /**
                  @brief Use this function to do in-place buffer processing [Overridable]
                  @param buffer
                  @param numberOfSamples
                 */
                virtual void process(float* buffer, uint32_t numberOfSamples);
                /**
                  @brief Use this function to do out-place buffer processing [Overridable]
                  @param input
                  @param output
                  @param numberOfSamples
                 */
                virtual void process(const float* input, float* output, uint32_t numberOfSamples);
                /**
                  @brief Use this function to filter a sample 
                  @param sample
                  @return 
                 */
                virtual float process(const float sample);
            protected:
                Type type = Type::Lowpass;
                float sampleRate = 44100;
                std::vector<float> parameters;
                std::vector<float> coefficients;
            };


            /**
             @brief Consist of Lowpass, Highpass and Bandpass 2nd Order IIR filters based on the Butterworth Formula
             */
            class Butterworth : public IIRFilter
            {
            public:
                Butterworth();
                ~Butterworth() = default;
                Butterworth(const Butterworth& butterworth) = default;   
                /**
                  @brief Use this function to set the parameters for the filter
                  * Expected Arguments for Prepare To Play
                  
                  * fc : Cutoff Frequency 
                  
                  * q : Q-Factor (Only for Bandpass)
                  
                  * Use the enum Butterworth::Parameters for easy indexing
                  @param parameters
                 */
                void prepareToPlay(const std::vector<float>& parameters) override;
                /**
                  @brief In-Place buffer processing
                  @param buffer
                  @param numberOfSamples
                 */
                void process(float* buffer, uint32_t numberOfSamples) override;
                /**
                  @brief In-Place buffer processing
                  @param buffer
                  @param numberOfSamples
                 */
                float process(const float sample) override;
                /**
                  @brief Out-Place buffer processing 
                  @param inputBuffer
                  @param outputBuffer
                  @param numberOfSamples
                 */
                void process(const float* inputBuffer, float* outputBuffer, uint32_t numberOfSamples) override;
            private:
                enum Parameters
                {
                    fc,q
                };
                enum index
                {
                    a0,a1,a2,b1,b2
                };
                float z1;
                float z2;
                const float sqrt2 = sqrtf(2);
                float output;
            };
        

            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief A 2nd Order Parameteric EQ to generate bandpeak and bandreject filters
            ///////////////////////////////////////////////////////////////////////////////////////
            class ParametricEQ : public IIRFilter
            {
            public:
                ParametricEQ();
                ~ParametricEQ() = default;
                ParametricEQ(const ParametricEQ& peq) = default;
                /**
                  @brief Use this function to set the parameters for the filter
                  * Expected Arguments for Prepare To Play

                  * fc : Cutoff Frequency

                  * q : Q-Factor
                   
                  * boost : Boost in (dB)

                  * Use the enum Butterworth::Parameters for easy indexing
                  @param parameters
                 */
                void prepareToPlay(const std::vector<float>& parameters) override;
                /**
                  @brief Process a Sample through the filter 
                  @param sample
                  @return 
                 */
                float process(const float sample) override;
                /**
                  @brief In-Place buffer processing 
                  @param buffer
                  @param numberOfSamples
                */
                void process(float* buffer, uint32_t numberOfSamples) override;
                /**
                  @brief Out-Place Buffer processing 
                  @param inputBuffer
                  @param outputBuffer
                  @param numberOfSamples
                 */
                void process(const float* inputBuffer, float* outputBuffer, uint32_t numberOfSamples) override;
            private:
                enum index
                {
                    a0, a1, a2, b1, b2
                };
                enum Parameters
                {
                    fc,q,boost
                };
                float z1;
                float z2;
                float output;
            };

            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief A set of First Order IIR filters
            ///////////////////////////////////////////////////////////////////////////////////////
            class FirstOrder : public IIRFilter
            {
            public:
                ///////////////////////////////////////////////////////////////////////////////////////
                /// @brief Default Constructor. Initializes an Allpass filter, by default.
                ///////////////////////////////////////////////////////////////////////////////////////
                FirstOrder();
                ~FirstOrder() = default;
                FirstOrder(const FirstOrder& firstOrder) = default;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Prepares the IIR Filter for playback
                ///////////////////////////////////////////////////////////////////////////////////////
                void prepareToPlay(const std::vector<float>& parameters) override;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Returns the sample after applying IIR Filter to it
                ///////////////////////////////////////////////////////////////////////////////////////
                float process(const float sample) override;
                /**
                  @brief Applies first-order Filter (In-Place Processing)
                  @param buffer
                  @param numberofSamples 
                 */
                void process(float* buffer, uint32_t numberofSamples) override;
                /**
                  @brief Applies first-order Filter (Out-Place buffer processing) 
                  @param inputBuffer
                  @param outputBuffer
                  @param numberOfSamples
                  \code{.cpp}
                  
                  \endcode 
                 */
                void process(const float* inputBuffer, float* outputBuffer, uint32_t numberOfSamples) override;
            private:
                enum Parameters
                {
                    fc
                };
                std::vector<float> coefficients;
                float xh_new;
                float xh;
                float c;
                float output;
            };

            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief IIR Filter Algorithms that are not part of a filterbank
            ///////////////////////////////////////////////////////////////////////////////////////
            class General : public IIRFilter
            {
            public:
                ///////////////////////////////////////////////////////////////////////////////////////
                /// @brief Specifies the type of Filter
                ///////////////////////////////////////////////////////////////////////////////////////
                General();
                ~General() = default;
                General(const General& general) = default;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Prepares the IIR Filter for playback
                ///////////////////////////////////////////////////////////////////////////////////////
                void prepareToPlay(const std::vector<float>& parameters) override;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Returns the sample after applying IIR Filter to it
                ///////////////////////////////////////////////////////////////////////////////////////
                float process(const float sample) override;

                void process(float* buffer, uint32_t numberOfSamples) override;

                void process(const float* inputBuffer, float* outputBuffer, uint32_t numberOfSamples) override;
            private:
                enum index
                {
                    a0, a1, a2, b1, b2, c0, d0
                };
                enum Parameters
                {
                    fc,q,boost
                };
                float z1;
                float z2;
                float output;
            };



            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief Engine implements all the IIR filters and can be used to process audio right away. It is also compatible with Juce::AudioBuffer<float>
            ///////////////////////////////////////////////////////////////////////////////////////
            class Engine
            {
            public:
                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Specifies the Filter Type 
                ///////////////////////////////////////////////////////////////////////////////////////
                enum Filter
                {
                    ButterLPF6dB,    ///< Butterworth Low-Pass Filter with a 6 dB/octave roll-off
                    ButterHPF6dB,    ///< Butterworth High-Pass Filter with a 6 dB/octave roll-off
                    ButterLPF12dB,   ///< Butterworth Low-Pass Filter with a 12 dB/octave roll-off
                    ButterHPF12dB,   ///< Butterworth High-Pass Filter with a 12 dB/octave roll-off
                    ButterBPF6dB,    ///< Butterworth Band-Pass Filter with a 6 dB/octave roll-off
                    ButterBPF12dB,   ///< Butterworth Band-Pass Filter with a 12 dB/octave roll-off
                    ParametericEQ,   ///< A Parameteric EQ to generate bandpeak and bandreject filters
                    Shelf,           ///< Shelving Filter, either low or high shelf, for broad frequency adjustments
                    Shelfx2,         ///< Variant of the Shelving Filter
                    APF1,            ///< First-order All-Pass Filter
                    LPF1,            ///< First-order Low-Pass Filter
                    HPF1,            ///< First-order High-Pass Filter
                    APF2,            ///< Second-order All-Pass Filter
                    LPF2,            ///< Second-order Low-Pass Filter
                    HPF2             ///< Second-order High-Pass Filter
                };

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Default Constructor. Initializes the engine with Butterworth Low Pass Filter with 6 dB roll-off
                ///////////////////////////////////////////////////////////////////////////////////////
                Engine() = default;
                Engine(Filter filter);
                ~Engine() = default;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Default Copy Constructor
                ///////////////////////////////////////////////////////////////////////////////////////
                Engine(const Engine& engine) = default;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Prepares the IIR Filter for playback
                ///////////////////////////////////////////////////////////////////////////////////////
                void prepareToPlay(float fc, float q, float sampleRate, float boost = 0, uint32_t channels = 2);
#ifdef JUCE
                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Applies IIR Filter to the given juce::AudioBuffer
                ///////////////////////////////////////////////////////////////////////////////////////
                void process(juce::AudioBuffer<float>& buffer);
#endif
                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Returns the sample after applying IIR Filter to it
                ///////////////////////////////////////////////////////////////////////////////////////
                float process(const float sample, uint32_t channelNumber);
            private:
                std::vector<Butterworth> butter1;
                std::vector<Butterworth> butter2;
                std::vector<General> general1;
                std::vector<General> general2;
                std::vector<ParametricEQ> paramEQ;
                std::vector<FirstOrder> firstOrder1;
                std::vector<FirstOrder> firstOrder2;
                Filter filter;
            };
        }

        
    }
}

#endif