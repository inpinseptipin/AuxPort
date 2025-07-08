#include "AuxCircularBuffer.h"

AuxPort::CircularBufferEngine::CircularBufferEngine()
{
	readIndex = 0;
	writeIndex = 0;
	buffer = nullptr;
	bufferSize = 0;
	poppedSample = 0;
}

void AuxPort::CircularBufferEngine::attachPointer(float* attachedBuffer,size_t bufferSize)
{
	this->buffer = attachedBuffer;
	this->bufferSize = bufferSize;
}

void AuxPort::CircularBufferEngine::push(float sample)
{
	AuxAssert(buffer != nullptr, "You need to attach a valid floating-point buffer to circular buffer it");
	buffer[writeIndex++] = sample;
	if (writeIndex >= bufferSize)
		writeIndex %= bufferSize;
}

float AuxPort::CircularBufferEngine::pop()
{
	poppedSample = buffer[readIndex++];
	readIndex %= bufferSize;
	return poppedSample;
}

void AuxPort::CircularBufferEngine::Log()
{
	setColour(AuxPort::ColourType::Blue);
	std::cout << "[";
	for (uint32_t i = 0; i < bufferSize; i++)
		i == bufferSize - 1 ? std::cout << buffer[i] : std::cout << buffer[i] << " , ";
	std::cout << "]\n";
	setColour(AuxPort::ColourType::White);	
}


