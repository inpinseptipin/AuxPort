#include "AuxAudioFile.h"

void AuxPort::Extensions::WaveFile::attachFile(AudioFile<float>* file)
{
	this->file = file;
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
		if (userLoop)
			sampleCounter = sampleCounter >= loopEndIndex ? loopStartIndex : sampleCounter;
		sampleCounter = sampleCounter == UINT_MAX ? UINT_MAX : sampleCounter+1;
		if (sampleCounter == file->samples[0].size() - 1)
			sampleCounter = toLoop ? UINT_MAX : 0;
	}
}

void AuxPort::Extensions::WaveReader::seek(double timeInSeconds)
{
	AuxAssert(timeInSeconds < file->getLengthInSeconds(), "Seek Time greater than length of song");
	sampleCounter = timeInSeconds * file->getSampleRate();
}

void AuxPort::Extensions::WaveReader::reset()
{
	sampleCounter = 0;
}

void AuxPort::Extensions::WaveReader::setLoopInSeconds(double loopStartInSeconds, double loopEndInSeconds)
{
	AuxAssert(loopEndInSeconds >= 0, "Loop End in seconds cannot be less than 0");
	AuxAssert(loopStartInSeconds >= 0, "Loop Start in seconds cannot be less than 0");
	AuxAssert(loopEndInSeconds <= file->getLengthInSeconds(), "Loop End has to be less than file length");
	AuxAssert(loopStartInSeconds <= file->getLengthInSeconds(), "Loop Start has to be less than file length");
	AuxAssert(loopEndInSeconds > loopStartInSeconds, "Loop End cannot be less than loop start");
	this->loopStartIndex = loopStartInSeconds * file->getSampleRate();
	this->loopEndIndex = loopEndInSeconds * file->getSampleRate();
}

void AuxPort::Extensions::WaveReader::setLoop(double loopStart, double loopEnd)
{
	AuxAssert(loopStart >= 0 && loopStart < 1, "Loop Start has to be within the bounds of [0,LoopEnd]");
	AuxAssert(loopEnd >= loopStart && loopEnd <= 1, "Loop End has to be within the bounds of [LoopStart,1]");
	this->loopStartIndex = static_cast<uint32_t>(loopStart * file->getNumSamplesPerChannel());
	this->loopEndIndex = static_cast<uint32_t>(loopEnd * file->getNumSamplesPerChannel());
}

void AuxPort::Extensions::WaveReader::enableLoop(bool loop)
{
	this->userLoop = loop;
	sampleCounter = loopStartIndex;
}

double AuxPort::Extensions::WaveReader::getCurrentTime()
{
	return AuxPort::Utility::remap<double>(sampleCounter, 0, file->getLengthInSeconds(), 0, file->getNumSamplesPerChannel());
}

void AuxPort::Extensions::WaveReader::setCurrentTime(double time)
{
	AuxAssert(time >= 0 && time <= 1, "Time has to be in the range of [0,1]");
	this->sampleCounter = static_cast<uint32_t>(time * file->getNumSamplesPerChannel());
}

void AuxPort::Extensions::WaveReader::setCurrentTimeInSeconds(double time)
{
	AuxAssert(time >= 0 && time <= file->getLengthInSeconds(), "Time has to be in the range of [0,Time Length]");
	this->sampleCounter = AuxPort::Utility::remap<double>(time, 0, file->getNumSamplesPerChannel(), 0, file->getLengthInSeconds());
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

