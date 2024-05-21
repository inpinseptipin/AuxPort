#include <iostream>
#include "AuxRtAudio.h"

int main()
{
    AuxPort::Extensions::AuxRtAudio<float> x;
    float data[2] = { 0, 0 };
    x.callback = [&data](float* outputBuffer, float* inputBuffer, unsigned int nBufferFrames, double streamTime)
    {
        unsigned int i, j;
        float* buffer = outputBuffer;
        float* lastValues = data;

        // Write sawtooth audio data to outputBuffer.
        for (i = 0; i < nBufferFrames; i++) {
            for (j = 0; j < 2; j++) {
                *buffer++ = lastValues[j];

                lastValues[j] += 0.005 * (j + 1 + (j * 0.1));
                if (lastValues[j] >= 1.0) lastValues[j] -= 2.0;
            }
        }
        return 0;
    };

    x.startStream();
    std::cout << "Stream Started! Press any key to end!\n";
    std::cin.get();

    x.closeStream();
    std::cout << "Press any key to exit!\n";
    std::cin.get();

    return 0;
}