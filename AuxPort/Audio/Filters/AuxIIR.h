#ifndef AUXPORT_IIR_H
#define AUXPORT_IIR_H
/*
*			AuxPort Library
            "Modules for Audio Software Development" - inpinseptipin

            BSD 3-Clause License

            Copyright (c) 2023, Satyarth Arora
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
        ///////////////////////////////////////////////////////////////////////////////////////           
        /// @brief This namespace contains IIR Filter Classes
        ///////////////////////////////////////////////////////////////////////////////////////
        namespace IIR
        {
            ///////////////////////////////////////////////////////////////////////////////////////           
            /// @brief Base class for all IIR Filters in AuxPort
            ///////////////////////////////////////////////////////////////////////////////////////   
            class IIRFilter
            {
            public:
                enum Type
                {
                    Lowpass,Highpass,Bandpass,BandReject,Notch,LowShelf,HighShelf,
                };
                IIRFilter() = default;
                ~IIRFilter() = default;
                IIRFilter(const IIRFilter& iirFilter) = default;
                void setSampleRate(float sampleRate);
                void setFilterType(Type type);
                virtual void prepareToPlay(const std::vector<float>& parameters);
                virtual void process(float* buffer, uint32_t numberOfSamples);
                virtual float process(const float& sample);
            protected:
                Type type = Type::Lowpass;
                float sampleRate;
                std::vector<float> parameters;
                std::vector<float> coefficients;
            };

            ///////////////////////////////////////////////////////////////////////////////////////           
            /// @brief Consist of Lowpass, Highpass and Bandpass 2nd order IIR filters based on the Butterworth Formula
            ///////////////////////////////////////////////////////////////////////////////////////   
            class Butterworth : public IIRFilter
            {
            public:
                Butterworth();
                ~Butterworth() = default;
                Butterworth(const Butterworth& butterworth) = default;
                ///////////////////////////////////////////////////////////////////////////////////////           
                ///@brief
                /// Expected Arguments for PrepareToPlay
                /// fc : Cutoff Frequency
                /// q : Q-Factor (Only for Bandpass)
                ///////////////////////////////////////////////////////////////////////////////////////           
                void prepareToPlay(const std::vector<float>& parameters) override;
                void process(float* buffer, uint32_t numberOfSamples) override;
                float process(const float& sample) override;
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

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Prepares the Filter for playback
                ///////////////////////////////////////////////////////////////////////////////////////
                void prepareToPlay(const std::vector<float>& parameters) override;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Returns the sample after applying Filter to it
                ///////////////////////////////////////////////////////////////////////////////////////
                float process(const float& sample) override;
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
            class FirstOrder
            {
            public:
                ///////////////////////////////////////////////////////////////////////////////////////
                /// @brief Specifies the type of Filter
                ///////////////////////////////////////////////////////////////////////////////////////
                enum Type
                {
                    Allpass, Lowpass, Highpass
                };

                ///////////////////////////////////////////////////////////////////////////////////////
                /// @brief Default Constructor. Initializes an Allpass filter, by default.
                ///////////////////////////////////////////////////////////////////////////////////////
                FirstOrder();
                ~FirstOrder() = default;
                FirstOrder(const FirstOrder& firstOrder) = default;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Prepares the IIR Filter for playback
                ///////////////////////////////////////////////////////////////////////////////////////
                void prepareToPlay(float fc, float sampleRate, const Type& type);

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Returns the sample after applying IIR Filter to it
                ///////////////////////////////////////////////////////////////////////////////////////
                float processSample(float sample);
            private:
                std::vector<float> coefficients;
                float xh_new;
                float xh;
                float c;
                float output;
                Type type;
            };

            ///////////////////////////////////////////////////////////////////////////////////////
            /// @brief IIR Filter Algorithms that are not part of a filterbank
            ///////////////////////////////////////////////////////////////////////////////////////
            class General
            {
            public:
                ///////////////////////////////////////////////////////////////////////////////////////
                /// @brief Specifies the type of Filter
                ///////////////////////////////////////////////////////////////////////////////////////
                enum Type
                {
                    HighShelf
                };

                General();
                ~General() = default;
                General(const General& general) = default;

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Prepares the IIR Filter for playback
                ///////////////////////////////////////////////////////////////////////////////////////
                void prepareToPlay(float fc, float q, float boost, float sampleRate, Type type = Type::HighShelf);

                ///////////////////////////////////////////////////////////////////////////////////////            
                /// @brief Returns the sample after applying IIR Filter to it
                ///////////////////////////////////////////////////////////////////////////////////////
                float processSample(float sample);
            private:
                std::vector<float> coefficients;
                enum index
                {
                    a0, a1, a2, b1, b2, c0, d0
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
                float process(const float& sample, uint32_t channelNumber);
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