#include "AuxAudioFile.h"




void AuxPort::Extensions::WaveFile::attachFile(AudioFile<float>* file)
{
	this->file = file;
	this->sampleCounter = 0;
}

void AuxPort::Extensions::WaveFile::attachStreamBuffer(std::vector<std::vector<float>>* streamingBuffer)
{
	AuxAssert(streamingBuffer->size() > 0, "Cannot attach a buffer with 0 channels");
	AuxAssert(streamingBuffer->at(0).size() > 0, "Cannot attach a buffer with a buffer size of 0");
	this->streamingBuffer = streamingBuffer;
	this->numberOfStreamChannels = streamingBuffer->size();
	this->streamSize = streamingBuffer->at(0).size();
}


void AuxPort::Extensions::WaveReader::readBuffer(bool toLoop)
{
	AuxAssert(file != nullptr, "Need a pointer to the AudioFile object to access the samples");
	for (uint32_t i = 0; i < streamSize; i++)
	{
		for (uint32_t j = 0; j < numberOfStreamChannels; j++)
		{
			streamingBuffer->at(j)[i] = sampleCounter == UINT_MAX ? 0.0f : file->samples[j][sampleCounter];
		}
		sampleCounter = sampleCounter == UINT_MAX ? UINT_MAX : sampleCounter++;
		if (sampleCounter == file->samples[0].size() - 1)
			sampleCounter = toLoop ? UINT_MAX : 0;
	}
}

void AuxPort::Extensions::WaveReader::seek(double timeInSeconds)
{
	AuxAssert(timeInSeconds > file->getLengthInSeconds(), "Seek Time greater than length of song");
	sampleCounter = timeInSeconds * file->getSampleRate();
}

void AuxPort::Extensions::WaveReader::reset()
{
	sampleCounter = 0;
}

void AuxPort::Extensions::WaveWriter::attachFile(AudioFile<float>* file, uint32_t numberOfChannels, uint32_t numberOfSamples)
{
	this->file = file;
	this->file->samples.resize(numberOfChannels);
	for (uint32_t i = 0; i < numberOfChannels; i++)
		file->samples[i].resize(numberOfSamples);
	this->sampleCounter = 0;
}



void AuxPort::Extensions::WaveWriter::writeBuffer()
{
	AuxAssert(file != nullptr, "Need a pointer to the AudioFile object to access the samples");
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

