#include "AuxUtility.h"

AuxPort::Expansions::Expansions()
{
    sum = 0;
    leftAccumulator.reserve(50);
    rightAccumulator.reserve(50);
    terms.reserve(100);
    type = ADAA;
}

void AuxPort::Expansions::setType(const Type& type)
{
    this->type = type;
}


void AuxPort::Expansions::setMaxSize(uint32_t N)
{
    auto NewN = static_cast<float>(N);
    leftAccumulator.reserve(static_cast<size_t>(floorf((NewN + 1) / 2)));
    rightAccumulator.reserve(static_cast<size_t>(floorf((NewN + 1) / 2)));
    terms.reserve(static_cast<size_t>(N));
}

std::vector<float>& AuxPort::Expansions::compute(const std::vector<float>& xPowers, const std::vector<float>& yPowers, uint32_t N)
{
    if (leftAccumulator.size() != xPowers.size())
    {
        leftAccumulator.resize(xPowers.size());
        rightAccumulator.resize(yPowers.size());
    }
    if (terms.size() != N)
        terms.resize(N);

    for (uint32_t i = 0; i < leftAccumulator.size(); i++)
    {
        leftAccumulator[i] = xPowers[i] * yPowers[i];
    }
    rightAccumulator = leftAccumulator;


    for (uint32_t M = 1; M <= N; M++)
    {
        sum = 0;
        for (uint32_t i = 1; i <= floor((M + 1) / 2); i++)
        {
            leftAccumulator[i - 1] *= yPowers[1];
            rightAccumulator[i - 1] *= xPowers[1];
            sum += leftAccumulator[i - 1];
            sum += rightAccumulator[i - 1];
        }
        if (M % 2 == 0)
            sum += leftAccumulator[(M / 2) - 1];
        terms[M - 1] = sum;
    }
    return terms;

}


AuxPort::Terms::Terms()
{
    termPowers.reserve(10);
}

void AuxPort::Terms::computePowers(float sample, uint32_t powers)
{
    if (termPowers.size() != powers)
        termPowers.resize(powers);
    termPowers[0] = 1;
    for (uint32_t i = 1; i < termPowers.size(); i++)
        termPowers[i] = termPowers[i - 1] * sample;
}

void AuxPort::Terms::computeAdditionalPowers(uint32_t start, uint32_t end)
{
    if (termPowers.size() != end)
        termPowers.resize(end);
    for (uint32_t i = start; i < end; i++)
        termPowers[i] = termPowers[i - 1] * termPowers[1];
}

std::vector<float>& AuxPort::Terms::getInternalVector()
{
    return termPowers;
}

void AuxPort::Terms::swap(Terms& term)
{
    this->termPowers.swap(term.termPowers);
}


AuxPort::FastRandomFloat::FastRandomFloat()
{
    randomSeed = 1;
}

AuxPort::FastRandomFloat::FastRandomFloat(const int& randomSeed)
{
    AuxAssert(randomSeed != 0, "randomSeed should be non-zero!");
    this->randomSeed = randomSeed;
}

float AuxPort::FastRandomFloat::getRandomFloat()
{
    randomSeed *= 16807;
    return (float)randomSeed * 4.6566129e-010f;
}

float AuxPort::FastRandomFloat::getRandomFloat(float start, float end)
{
    AuxAssert(start <= end, "start should be <= end.");
    return start + (end - start) * (getRandomFloat() + 1.0f) / 2.0f;
}

AuxPort::Graphics::DrawBuffer::DrawBuffer()
{
    drawBufferSize = 1024;
    buffer.resize(drawBufferSize);
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    writeIndex = 0;
}

void AuxPort::Graphics::DrawBuffer::setDrawBufferSize(size_t bufferSize)
{
    this->drawBufferSize = bufferSize;
    this->buffer.resize(drawBufferSize);
    writeIndex = 0;
    std::fill(buffer.begin(), buffer.end(), 0.0f);
}

void AuxPort::Graphics::DrawBuffer::addToBuffer(const float* buffer, size_t numberOfSamples)
{
    for (uint32_t i = 0; i < numberOfSamples; i++)
    {
        this->buffer[writeIndex++] = buffer[i];
        writeIndex %= this->buffer.size();
    }
}

size_t AuxPort::Graphics::DrawBuffer::size()
{
    return drawBufferSize;
}

const float* AuxPort::Graphics::DrawBuffer::getPointerToBuffer()
{
    return buffer.data();
}


void AuxPort::Graphics::ScopeBuffers::setDrawBufferSize(const std::vector<std::string>& bufferIDS, const std::vector<size_t> bufferSizes)
{
    AuxAssert(bufferIDS.size() == bufferSizes.size(), "Number of Buffer IDS should match Number of Buffer Sizes passed");
    for (size_t i = 0; i < bufferIDS.size(); i++)
    {
        std::pair<std::string, AuxPort::Graphics::DrawBuffer> pair;
        pair.first = bufferIDS[i];
        pair.second = AuxPort::Graphics::DrawBuffer();
        pair.second.setDrawBufferSize(bufferSizes[i]);
        bufferMap.insert(pair);
    }
}

void AuxPort::Graphics::ScopeBuffers::addToBuffer(const std::string& bufferID,const float* buffer, size_t numberOfSamples)
{
    auto found = bufferMap.find(bufferID);
    AuxAssert(found != bufferMap.end(), "Invalid BufferID");
    found->second.addToBuffer(buffer, numberOfSamples);
}

size_t AuxPort::Graphics::ScopeBuffers::size(const std::string& bufferID)
{
    auto found = bufferMap.find(bufferID);
    AuxAssert(found != bufferMap.end(), "Invalid BufferID");
    return found->second.size();
}

const float* AuxPort::Graphics::ScopeBuffers::getPointerToBuffer(const std::string& bufferID)
{
    auto found = bufferMap.find(bufferID);
    AuxAssert(found != bufferMap.end(), "Invalid BufferID");
    return found->second.getPointerToBuffer();
}

std::vector<std::string> AuxPort::Graphics::ScopeBuffers::getBufferIDS()
{
    std::vector<std::string> bufferIDS;
    for (auto const& element : bufferMap)
    {
        bufferIDS.push_back(element.first);
    }
    return bufferIDS;
}



