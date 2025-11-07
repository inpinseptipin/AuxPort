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
		writeIndex = 0;
}

void AuxPort::CircularBufferEngine::push(float* buffer, size_t bufferSize)
{
	AuxAssert(this->buffer != nullptr, "You need to attach a valid floating-point buffer to the engine, Use the attach pointer to attach a pointer");
	AuxAssert(buffer != nullptr, "The data you want to add has to be stored in a valid floating point buffer");
	for (uint32_t i = 0; i < bufferSize; i++)
	{
		this->buffer[writeIndex++] = buffer[i];
		if (writeIndex >= this->bufferSize)
			writeIndex = 0;
	}
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


