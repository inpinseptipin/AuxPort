#include "AuxScope.h"



AuxPort::Graphics::DrawBuffer::DrawBuffer()
{
    drawBufferSize = 1024;
    buffer.resize(drawBufferSize);
    std::fill(buffer.begin(), buffer.end(), 0.0f);
    writeIndex = 0;
}


void AuxPort::Graphics::DrawBuffer::setSize(size_t bufferSize)
{
    this->drawBufferSize = bufferSize;
    this->buffer.resize(drawBufferSize);
    writeIndex = 0;
    std::fill(buffer.begin(), buffer.end(), 0.0f);
}

void AuxPort::Graphics::DrawBuffer::append(const float* buffer, size_t numberOfSamples)
{
    for (uint32_t i = 0; i < numberOfSamples; i++)
    {
        this->buffer[writeIndex++] = buffer[i];
        writeIndex = writeIndex == this->buffer.size() ? 0 : writeIndex;
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


void AuxPort::Graphics::ScopeBuffers::setBufferSize(const std::vector<std::string>& bufferIDS, const std::vector<size_t> bufferSizes)
{
    AuxAssert(bufferIDS.size() == bufferSizes.size(), "Number of Buffer IDS should match Number of Buffer Sizes passed");
    for (size_t i = 0; i < bufferIDS.size(); i++)
    {
        std::pair<std::string, AuxPort::Graphics::DrawBuffer> pair;
        pair.first = bufferIDS[i];
        pair.second = AuxPort::Graphics::DrawBuffer();
        pair.second.setSize(bufferSizes[i]);
        bufferMap.insert(pair);
    }
}

void AuxPort::Graphics::ScopeBuffers::appendToBuffer(const std::string& bufferID, const float* buffer, size_t numberOfSamples)
{
    auto found = bufferMap.find(bufferID);
    AuxAssert(found != bufferMap.end(), "Invalid BufferID");
    found->second.append(buffer, numberOfSamples);
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

std::vector<std::string> AuxPort::Graphics::ScopeBuffers::getNames()
{
    std::vector<std::string> bufferIDS;
    for (auto const& element : bufferMap)
    {
        bufferIDS.push_back(element.first);
    }
    return bufferIDS;
}
