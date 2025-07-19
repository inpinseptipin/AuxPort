#include "AuxAudioFile.h"



void AuxPort::Extensions::WaveReader::attachFile(AudioFile<float>* file)
{
	this->file = file;
	this->sampleCounter = 0;
}

void AuxPort::Extensions::WaveReader::attachStreamBuffer(std::vector<std::vector<float>>* streamingBuffer)
{
	AuxAssert(streamingBuffer->size() > 0, "Cannot attach a buffer with 0 channels");
	AuxAssert(streamingBuffer->at(0).size() > 0, "Cannot attach a buffer with a buffer size of 0");
	this->streamingBuffer = streamingBuffer;
	this->numberOfStreamChannels = streamingBuffer->size();
	this->streamSize = streamingBuffer->at(0).size();
}

void AuxPort::Extensions::WaveReader::readBuffer()
{
	for (uint32_t i = 0; i < streamSize; i++)
	{
		for (uint32_t j = 0; j < numberOfStreamChannels; j++)
			streamingBuffer->at(j)[i] = file->samples[j][i];
		sampleCounter++;
		if (sampleCounter == file->samples.size()-1)
			sampleCounter = 0;
	}
}



void AuxPort::Extensions::WaveWriter::attachFile(AudioFile<float>* file, uint32_t numberOfChannels, uint32_t numberOfSamples)
{
	this->file = file;
	this->file->samples.resize(numberOfChannels);
	for (uint32_t i = 0; i < numberOfChannels; i++)
		file->samples[i].resize(numberOfSamples);
	this->sampleCounter = 0;
}

void AuxPort::Extensions::WaveWriter::attachStreamBuffer(std::vector<std::vector<float>>* streamingBuffer)
{
	AuxAssert(streamingBuffer->size() > 0, "Cannot attach a buffer with 0 channels");
	AuxAssert(streamingBuffer->at(0).size() > 0, "Cannot attach a buffer with a buffer size of 0");
	this->streamingBuffer = streamingBuffer;
	this->numberOfStreamChannels = streamingBuffer->size();
	this->streamSize = streamingBuffer->at(0).size();
}

void AuxPort::Extensions::WaveWriter::writeBuffer()
{
	for (uint32_t i = 0; i < streamSize; i++)
	{
		if (sampleCounter == this->file->samples[0].size() - 1)
			break;
		for (uint32_t j = 0; j < this->numberOfStreamChannels; j++)
		{
			this->file->samples[j][sampleCounter] = streamingBuffer->at(j)[i];
		}
		sampleCounter++;
	}
}
