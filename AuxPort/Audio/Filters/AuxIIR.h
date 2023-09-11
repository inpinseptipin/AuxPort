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
        namespace IIR
        {
            ///////////////////////////////////////////////////////////////////////////////////////            
            /// Consist of Lowpass, Highpass and Bandpass 2nd order IIR filters based on the Butterworth Formula
            ///////////////////////////////////////////////////////////////////////////////////////            
            class Butterworth
            {
            public:
                enum class Type
                {
                    Lowpass, Highpass, Bandpass
                };
                Butterworth();
                ~Butterworth() = default;
                Butterworth(const Butterworth& butterworth) = default;
                void prepareToPlay(float fc, float q, float sampleRate, Type type = Type::Lowpass);
                float processSample(float sample);
            private:
                std::vector<float> coefficients;
                enum index
                {
                    a0, a1, a2, b1, b2
                };
                float z1;
                float z2;
                const float sqrt2 = sqrtf(2);
                float output;
            };

            ///////////////////////////////////////////////////////////////////////////////////////
            /// A 2nd Order Parameteric EQ to generate bandpeak and bandreject filters
            ///////////////////////////////////////////////////////////////////////////////////////
            class ParametricEQ
            {
            public:
                ParametricEQ();
                ~ParametricEQ() = default;
                ParametricEQ(const ParametricEQ& peq) = default;
                void prepareToPlay(float fc, float q, float boost, float sampleRate);
                float processSample(float sample);
            private:
                std::vector<float> coefficients;
                enum index
                {
                    a0, a1, a2, b1, b2
                };
                float z1;
                float z2;
                float output;
            };

            ///////////////////////////////////////////////////////////////////////////////////////
            /// A set of First Order IIR filters
            ///////////////////////////////////////////////////////////////////////////////////////
            class FirstOrder
            {
            public:
                enum Type
                {
                    Allpass, Lowpass, Highpass
                };
                FirstOrder();
                ~FirstOrder() = default;
                FirstOrder(const FirstOrder& firstOrder) = default;
                void prepareToPlay(float fc, float sampleRate, const Type& type);
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
            /// IIR Filter Algorithms that are not part of a filterbank
            ///////////////////////////////////////////////////////////////////////////////////////
            class General
            {
            public:
                enum Type
                {
                    HighShelf
                };
                General();
                ~General() = default;
                General(const General& general) = default;
                void prepareToPlay(float fc, float q, float boost, float sampleRate, Type type = Type::HighShelf);
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
            /// Engine implements all the IIR filters and can be used to process audio right away. It is also compatible with Juce::AudioBuffer<float>
            ///////////////////////////////////////////////////////////////////////////////////////
            class Engine
            {
            public:
                enum Filter
                {
                    ButterLPF6dB, ButterHPF6dB, ButterLPF12dB, ButterHPF12dB, ButterBPF6dB, ButterBPF12dB, ParametericEQ, Shelf, Shelfx2, APF1, LPF1, HPF1, APF2, LPF2, HPF2
                };
                Engine() = default;
                Engine(Filter filter);
                ~Engine() = default;
                Engine(const Engine& engine) = default;
                void prepareToPlay(float fc, float q, float sampleRate, float boost = 0, uint32_t channels = 2);
#ifdef JUCE           
                void process(juce::AudioBuffer<float>& buffer);
#endif
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