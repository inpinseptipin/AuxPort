#include "AuxEnvelope.h"

AuxPort::Audio::HilbertTransform::HilbertTransform(size_t overlapSize) : OverlapSaveProcessor<float>(overlapSize)
{
}

void AuxPort::Audio::HilbertTransform::transformBuffer(const std::vector<float>& inputBuffer, std::vector<float>& hilbertTransform)
{
    _currOverlappedBuffer.resize(_prevInputs.size() + inputBuffer.size());
    getOverlappedBuffer(inputBuffer, _currOverlappedBuffer);
    transformSignal(_currOverlappedBuffer, hilbertTransform);
}

void AuxPort::Audio::HilbertTransform::transformSignal(const std::vector<float>& inputSignal, std::vector<float>& hilbertTransform)
{
    size_t N = inputSignal.size();
    size_t fftSize = AuxPort::Utility::nextPowerOfTwo(N);

    // Compute the FFT of the input buffer
    AuxPort::Audio::FourierTransform fft(fftSize);
    std::vector<float> fftInput(fftSize, 0.0f);
    std::copy(inputSignal.begin(), inputSignal.end(), fftInput.begin());
    std::vector<float> fftOutput(fftSize);
    fft.computeTransform(fftInput, fftOutput);

    // Get the complex FFT result and apply Hilbert transform filter
    std::vector<std::complex<float>>* fftValues = fft.getFourierTransformFrame();
    (*fftValues)[0] = std::complex<float>(0.0f, 0.0f);
    for (size_t i = 1; i < fftSize / 2; ++i)
    {
        (*fftValues)[i] *= 2.0f;
    }
    for (size_t i = fftSize / 2 + 1; i < fftSize; ++i)
    {
        (*fftValues)[i] = std::complex<float>(0.0f, 0.0f);
    }

    // Compute the inverse FFT to get the analytic signal
    fft.computeInverseTransform(fftOutput);

    // Extract the imaginary part as the Hilbert transform
    hilbertTransform.resize(N);
    for (size_t i = 0; i < N; ++i)
    {
        hilbertTransform[i] = (*fftValues)[i].imag();
    }
}
