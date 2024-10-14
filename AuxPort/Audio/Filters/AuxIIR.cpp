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


#include "AuxIIR.h"

AuxPort::Audio::IIR::Butterworth::Butterworth()
{
    z1 = 0;
    z2 = 0;
    output = 0;
    coefficients.resize(5);
    for (uint32_t i = 0; i < coefficients.size(); i++)
        coefficients[i] = 0;
}




AuxPort::Audio::IIR::Engine::Engine(Filter filter)
{
    this->filter = filter;
    if (filter == ButterLPF6dB || filter == ButterHPF6dB || filter == ButterBPF6dB)
        butter1.resize(2);
    if (filter == ButterLPF12dB || filter == ButterHPF12dB || filter == ButterBPF12dB)
    {
        butter1.resize(2);
        butter2.resize(2);
    }
    if (filter == ParametericEQ)
    {
        paramEQ.resize(2);
    }
    if (filter == Shelf)
        general1.resize(2);

    if (filter == Shelfx2)
    {
        general1.resize(2);
        general2.resize(2);
    }

    if (filter == APF1 || filter == LPF1 || filter == HPF1)
        firstOrder1.resize(2);
    if (filter == APF2 || filter == LPF2 || filter == HPF2)
    {
        firstOrder1.resize(2);
        firstOrder2.resize(2);
    }
}

void AuxPort::Audio::IIR::Engine::prepareToPlay(float fc, float q, float sampleRate,float boost, uint32_t channels)
{
    if (filter == ButterLPF6dB)
    {
        if (channels > butter1.size())
            butter1.resize(channels);
        for (uint32_t i = 0; i < butter1.size(); i++)
        {
            butter1[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Lowpass);
            butter1[i].setSampleRate(sampleRate);
            butter1[i].prepareToPlay({fc,q});
        }
    }


    if (filter == ButterHPF6dB)
    {
        if (channels > butter1.size())
            butter1.resize(channels);
        for (uint32_t i = 0; i < butter1.size(); i++)
        {
            butter1[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Highpass);
            butter1[i].setSampleRate(sampleRate);
            butter1[i].prepareToPlay({ fc,q });
        }
    }

    if (filter == ButterBPF6dB)
    {
        if (channels > butter1.size())
            butter1.resize(channels);
        for (uint32_t i = 0; i < butter1.size(); i++)
        {
            butter1[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Bandpass);
            butter1[i].setSampleRate(sampleRate);
            butter1[i].prepareToPlay({ fc,q });
        }
    }


    if (filter == ButterHPF12dB)
    {
        if (channels > butter1.size())
        {
            butter1.resize(channels);
            butter2.resize(channels);
        }
            
        for (uint32_t i = 0; i < butter1.size(); i++)
        {
            butter1[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Highpass);
            butter1[i].setSampleRate(sampleRate);
            butter1[i].prepareToPlay({ fc,q });
            butter2[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Highpass);
            butter2[i].setSampleRate(sampleRate);
            butter2[i].prepareToPlay({ fc,q });
        }
    }

    if (filter == ButterLPF12dB)
    {
        if (channels > butter1.size())
        {
            butter1.resize(channels);
            butter2.resize(channels);
        }
        for (uint32_t i = 0; i < butter1.size(); i++)
        {
            butter1[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Lowpass);
            butter1[i].setSampleRate(sampleRate);
            butter1[i].prepareToPlay({ fc,q });
            butter2[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Lowpass);
            butter2[i].setSampleRate(sampleRate);
            butter2[i].prepareToPlay({ fc,q });
        }
    }

    if (filter == ButterBPF12dB)
    {
        if (channels > butter1.size())
        {
            butter1.resize(channels);
            butter2.resize(channels);
        }
        for (uint32_t i = 0; i < butter1.size(); i++)
        {
            butter1[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Bandpass);
            butter1[i].setSampleRate(sampleRate);
            butter1[i].prepareToPlay({ fc,q });
            butter2[i].setFilterType(AuxPort::Audio::IIR::IIRFilter::Bandpass);
            butter2[i].setSampleRate(sampleRate);
            butter2[i].prepareToPlay({ fc,q });
        }
    }

    if (filter == ParametericEQ)
    {
        if (channels > paramEQ.size())
            paramEQ.resize(channels);
        for (uint32_t i = 0; i < paramEQ.size(); i++)
            paramEQ[i].prepareToPlay({ fc, q, boost });
    }


    if (filter == Shelf)
    {
        if (channels > general1.size())
            general1.resize(channels);
        for (uint32_t i = 0; i < general1.size(); i++)
            general1[i].prepareToPlay(fc, q, boost, sampleRate, AuxPort::Audio::IIR::General::HighShelf);
    }

    if (filter == Shelfx2)
    {
        if (channels > general1.size())
        {
            general1.resize(channels);
            general2.resize(channels);
        }
        for (uint32_t i = 0; i < general1.size(); i++)
        {
            general1[i].prepareToPlay(fc, q, boost, sampleRate, AuxPort::Audio::IIR::General::HighShelf);
            general2[i].prepareToPlay(fc, q, boost, sampleRate, AuxPort::Audio::IIR::General::HighShelf);
        }
            
    }

    if (filter == APF1)
    {
        if (channels > firstOrder1.size())
            firstOrder1.resize(channels);
        for (uint32_t i = 0; i < firstOrder1.size(); i++)
            firstOrder1[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Allpass);
    }

    if (filter == LPF1)
    {
        if (channels > firstOrder1.size())
            firstOrder1.resize(channels);
        for (uint32_t i = 0; i < firstOrder1.size(); i++)
            firstOrder1[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Lowpass);
    }

    if (filter == HPF1)
    {
        if (channels > firstOrder1.size())
            firstOrder1.resize(channels);
        for (uint32_t i = 0; i < firstOrder1.size(); i++)
            firstOrder1[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Highpass);
    }

    if (filter == APF2)
    {
        if (channels > firstOrder1.size())
        {
            firstOrder1.resize(channels);
            firstOrder2.resize(channels);
        }
        for (uint32_t i = 0; i < firstOrder1.size(); i++)
        {
            firstOrder1[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Allpass);
            firstOrder2[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Allpass);
        }
    }

    if (filter == LPF2)
    {
        if (channels > firstOrder1.size())
        {
            firstOrder1.resize(channels);
            firstOrder2.resize(channels);
        }
        for (uint32_t i = 0; i < firstOrder1.size(); i++)
        {
            firstOrder1[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Lowpass);
            firstOrder2[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Lowpass);
        }
    }

    if (filter == HPF2)
    {
        if (channels > firstOrder1.size())
        {
            firstOrder1.resize(channels);
            firstOrder2.resize(channels);
        }
        for (uint32_t i = 0; i < firstOrder1.size(); i++)
        {
            firstOrder1[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Highpass);
            firstOrder2[i].prepareToPlay(fc, sampleRate, AuxPort::Audio::IIR::FirstOrder::Highpass);
        }
    }

    

    


}


AuxPort::Audio::IIR::ParametricEQ::ParametricEQ()
{
    z1 = 0;
    z2 = 0;
    output = 0;
    coefficients.resize(5);
    for (uint32_t i = 0; i < coefficients.size(); i++)
        coefficients[i] = 0;
}

void AuxPort::Audio::IIR::ParametricEQ::prepareToPlay(const std::vector<float>& parameters)
{
    this->parameters = parameters;
    float k = tanf(AuxPort::pi * parameters[fc] / sampleRate);
    float vo = powf(10.0f, parameters[boost] / 20.0f);
    bool toBoost = parameters[boost] >= 0 ? true : false;

    float d0 = 1.0f + (1.0f / parameters[q]) * k + powf(k, 2);
    float e0 = 1.0f + (1.0f / (vo * parameters[q])) * k + powf(k, 2);
    float alpha = 1.0f + (vo / parameters[q]) * k + powf(k, 2);
    float beta = 2.0f * (powf(k, 2) - 1.0f);
    float gamma = 1.0f - (vo / parameters[q]) * k + powf(k, 2);
    float delta = 1.0f - (1.0f / parameters[q]) * k + powf(k, 2);
    float eta = 1.0f - (1.0f / (vo * parameters[q])) * k + powf(k, 2);

    coefficients[index::a0] = toBoost ? alpha / d0 : d0 / e0;
    coefficients[index::a1] = toBoost ? beta / d0 : beta / e0;
    coefficients[index::a2] = toBoost ? gamma / d0 : delta / e0;
    coefficients[index::b1] = toBoost ? beta / d0 : beta / e0;
    coefficients[index::b2] = toBoost ? delta / d0 : eta / e0;
}

float AuxPort::Audio::IIR::ParametricEQ::process(const float& sample)
{
    output = sample * coefficients[index::a0] + z1;
    z1 = sample * coefficients[index::a1] + z2 - coefficients[index::b1] * output;
    z2 = sample * coefficients[index::a2] - coefficients[index::b2] * output;
    return output;
}



#ifdef JUCE


void AuxPort::Audio::IIR::Engine::process(juce::AudioBuffer<float>& buffer)
{
    for (uint32_t i = 0; i < buffer.getNumSamples(); i++)
    {
        for (uint32_t j = 0; j < buffer.getNumChannels(); j++)
        {
            if (filter == ButterLPF6dB || filter == ButterHPF6dB || filter == ButterBPF6dB)
                buffer.setSample(j,i,butter1[j].processSample(buffer.getSample(j, i)));
            if (filter == ButterLPF12dB || filter == ButterHPF12dB || filter == ButterBPF12dB)
                buffer.setSample(j, i, butter2[j].processSample(butter1[j].processSample(buffer.getSample(j, i))));
            if (filter == ParametericEQ)
                buffer.setSample(j, i, paramEQ[j].processSample(buffer.getSample(j,i));
        }
    }
}
#else
float AuxPort::Audio::IIR::Engine::process(const float& sample,uint32_t channelNumber)
{
    if (filter == ButterLPF6dB || filter == ButterHPF6dB || filter == ButterBPF6dB)
        return butter1[channelNumber].process(sample);
    if (filter == ButterLPF12dB || filter == ButterHPF12dB || filter == ButterBPF12dB)
        return butter2[channelNumber].process(butter1[channelNumber].process(sample));
    if (filter == Shelf)
        return general1[channelNumber].processSample(sample);
    if (filter == Shelfx2)
        return general2[channelNumber].processSample(general1[channelNumber].processSample(sample));
    if (filter == ParametericEQ)
        return paramEQ[channelNumber].process(sample);
    if (filter == APF1 || filter == LPF1 || filter == HPF1)
        return firstOrder1[channelNumber].processSample(sample);
    if (filter == APF2 || filter == LPF2 || filter == HPF2)
        return firstOrder2[channelNumber].processSample(firstOrder1[channelNumber].processSample(sample));
    else
        return 0;

}
#endif

AuxPort::Audio::IIR::General::General()
{
    z1 = 0;
    z2 = 0;
    output = 0;
    coefficients.resize(7);
    for (uint32_t i = 0; i < coefficients.size(); i++)
        coefficients[i] = 0;
}

void AuxPort::Audio::IIR::General::prepareToPlay(float fc, float q, float boost, float sampleRate, Type type)
{

    if (type == Type::HighShelf)
    {
        float theta_c = 2.0f * AuxPort::pi * fc / sampleRate;
        float mu = powf(10.0f, boost / 20.0f);
        float beta = (1.0f + mu) / 4.0f;
        float delta = beta * tanf(theta_c / 2.0f);
        float gamma = (1.0f - delta) / (1.0f + delta);


        coefficients[index::a0] = (1.0f + gamma) / 2.0f;
        coefficients[index::a1] = -coefficients[index::a0];
        coefficients[index::a2] = 0.0f;
        coefficients[index::b1] = -gamma;
        coefficients[index::b2] = 0.0f;
        coefficients[index::c0] = mu - 1.0f;
        coefficients[index::d0] = 1.0f;
    }
}

float AuxPort::Audio::IIR::General::processSample(float sample)
{
    output = sample * coefficients[index::a0] + z1;
    z1 = sample * coefficients[index::a1] + z2 - coefficients[index::b1] * output;
    z2 = sample * coefficients[index::a2] - coefficients[index::b2] * output;
    return coefficients[index::d0] * sample + coefficients[index::c0] * output;
}

AuxPort::Audio::IIR::FirstOrder::FirstOrder()
{
    xh = 0;
    xh_new = 0;
    output = 0;
    c = 0;
    type = Allpass;
}

void AuxPort::Audio::IIR::FirstOrder::prepareToPlay(float fc, float sampleRate,const Type& type)
{
    c = (tanf(AuxPort::pi * fc / sampleRate) - 1) / (tanf(AuxPort::pi * fc / sampleRate) + 1);
    this->type = type;
}

float AuxPort::Audio::IIR::FirstOrder::processSample(float sample)
{
    xh_new = sample - c * xh;
    output = c * xh_new + xh;
    xh = xh_new;
    if (type == Allpass)
        return output;
    if (type == Lowpass)
        return 0.5f * (sample + output);
    if (type == Highpass)
        return 0.5f * (sample - output);
    else
        return 0;
}

void AuxPort::Audio::IIR::IIRFilter::setSampleRate(float sampleRate)
{
    this->sampleRate = sampleRate;
}

void AuxPort::Audio::IIR::IIRFilter::setFilterType(Type type)
{
    this->type = type;
}

void AuxPort::Audio::IIR::IIRFilter::prepareToPlay(const std::vector<float>& parameters)
{
    this->parameters = parameters;
}

void AuxPort::Audio::IIR::IIRFilter::process(float* buffer, uint32_t numberOfSamples)
{
    return;
}

float AuxPort::Audio::IIR::IIRFilter::process(const float& sample)
{
    return sample;
}

void AuxPort::Audio::IIR::Butterworth::prepareToPlay(const std::vector<float>& parameters)
{
    this->parameters = parameters;

    if (type == AuxPort::Audio::IIR::IIRFilter::Lowpass)
    {
        float theta_c = AuxPort::pi * parameters[fc] / sampleRate;
        float c = 1.0f / tanf(theta_c);
        coefficients[index::a0] = 1.0f / (1.0f + sqrt2 * c + powf(c, 2));
        coefficients[index::a1] = 2.0f * coefficients[index::a0];
        coefficients[index::a2] = coefficients[index::a0];
        coefficients[index::b1] = 2.0f * coefficients[index::a0] * (1.0f - powf(c, 2));
        coefficients[index::b2] = coefficients[a0] * (1.0f - sqrt2 * c + powf(c, 2));
    }

    if (type == Type::Highpass)
    {
        float theta_c = AuxPort::pi * parameters[fc] / sampleRate;
        float c = 1.0f / tanf(theta_c);
        coefficients[index::a0] = 1.0f / (1.0f + sqrt2 * c + powf(c, 2));
        coefficients[index::a1] = -2.0f * coefficients[index::a0];
        coefficients[index::a2] = coefficients[index::a0];
        coefficients[index::b1] = 2.0f * coefficients[index::a0] * (powf(c, 2) - 1.0f);
        coefficients[index::b2] = coefficients[index::a0] * (1.0f - sqrt2 * c + powf(c, 2));
    }

    if (type == Type::Bandpass)
    {
        float theta_c = 2.0f * AuxPort::pi * parameters[fc] / sampleRate;
        float bandwidth = parameters[fc] / parameters[q];
        float delta_c = AuxPort::pi * bandwidth / sampleRate;
        if (delta_c >= 0.95f * AuxPort::pi / 2.0f)
            delta_c = 0.95f * AuxPort::pi / 2.0f;
        float c = 1.0f / tanf(delta_c);
        float d = 2.0f * cosf(theta_c);

        coefficients[index::a0] = 1.0f / (1.0f + c);
        coefficients[index::a1] = 0.0f;
        coefficients[index::a2] = -coefficients[index::a0];
        coefficients[index::b1] = -coefficients[index::a0] * (c * d);
        coefficients[index::b2] = coefficients[index::a0] * (c - 1.0f);
    }
}

void AuxPort::Audio::IIR::Butterworth::process(float* buffer, uint32_t numberOfSamples)
{
    for (uint32_t i = 0; i < numberOfSamples; i++)
    {
        output = buffer[i] * coefficients[index::a0] + z1;
        z1 = buffer[i] * coefficients[index::a1] + z2 - coefficients[index::b1] * output;
        z2 = buffer[i] * coefficients[index::a2] - coefficients[index::b2] * output;
        buffer[i] = output;
    }

   
}

float AuxPort::Audio::IIR::Butterworth::process(const float& sample)
{
    output = sample * coefficients[index::a0] + z1;
    z1 = sample * coefficients[index::a1] + z2 - coefficients[index::b1] * output;
    z2 = sample * coefficients[index::a2] - coefficients[index::b2] * output;
    return output;
}
