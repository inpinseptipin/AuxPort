#include "AuxStimulus.h"
#include "../../Core/Utility/AuxUtility.h"

std::vector<float> AuxPort::Audio::Stimulus::generateImpulse(float lengthInTime,float sampleRate)
{
    AuxAssert(lengthInTime > 0.0f, "Length in Time cannot be negative");
    size_t numberOfSamples = static_cast<size_t>(lengthInTime * sampleRate);
    std::vector<float> impulse;
    impulse.resize(numberOfSamples);
    impulse[0] = 1.0f;
    return impulse;
    
}

std::vector<float> AuxPort::Audio::Stimulus::generateImpulse(uint32_t numberOfSamples)
{
    AuxAssert(numberOfSamples > 0 && numberOfSamples < 132000, "Number of Samples has to be greater than zero");
    std::vector<float> impulse;
    impulse.resize(numberOfSamples);
    impulse[0] = 1.0f;
    return impulse;
}

std::vector<float> AuxPort::Audio::Stimulus::generateWhiteNoise(float lengthInTime, float sampleRate)
{
    AuxAssert(lengthInTime > 0.0f, "Length in Time cannot be negative");
    size_t numberOfSamples = static_cast<size_t>(lengthInTime * sampleRate);
    return AuxPort::Utility::generateRandomValues<float>(numberOfSamples);
}

std::vector<float> AuxPort::Audio::Stimulus::generateWhiteNoise(uint32_t numberOfSamples)
{
    AuxAssert(numberOfSamples > 0 && numberOfSamples < UINT_LEAST32_MAX, "Number of Samples has to be greater than zero");
    return AuxPort::Utility::generateRandomValues<float>(numberOfSamples);
}

std::vector<float> AuxPort::Audio::Stimulus::generateExponentialSineSweep(float lengthInTime, float startFrequency,float endFrequency,float sampleRate)
{
    AuxAssert(lengthInTime > 0.0f, "Length in time cannot be negative");
    size_t numberOfSamples = static_cast<size_t>(lengthInTime * sampleRate);
    std::vector<float> stimulus;
    stimulus.resize(numberOfSamples);
    auto L = lengthInTime / log(endFrequency / startFrequency);
    auto mod = 0.0f;
    auto inc = 1.0f / sampleRate;
    for (uint32_t i = 0; i < numberOfSamples; i++)
    {
        stimulus[i] = sin(2 * pi * startFrequency * L * (expf(mod / L) - 1));
        mod += inc;
    }
    return stimulus;
}

