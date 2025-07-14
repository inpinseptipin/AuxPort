#include "AuxStimulus.h"

std::vector<float> AuxPort::Audio::Stimulus::generateImpulse(float lengthInTime,float sampleRate)
{
    AuxAssert(lengthInTime > 0.0f, "Length in Time cannot be negative");
    size_t numberOfSamples = static_cast<size_t>(lengthInTime * sampleRate);
    std::vector<float> impulse;
    impulse.resize(numberOfSamples);
    impulse[0] = 1.0f;
    return impulse;
    
}
