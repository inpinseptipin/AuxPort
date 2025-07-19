#ifndef AUXPORT_EXTENSIONS_AUDIOFILE_H
#define AUXPORT_EXTENSIONS_AUDIOFILE_H

#include "AuxPort.h"
#include "AudioFile.h"

namespace AuxPort
{
	namespace Extensions
	{
		class WaveReader
		{
		public:
			WaveReader() = default;
			~WaveReader() = default;
			WaveReader(const WaveReader& waveReader) = default;
			void attachFile(AudioFile<float>* file);
			void attachStreamBuffer(std::vector<std::vector<float>>* streamingBuffer);
			void readBuffer();
		protected:
			AudioFile<float>* file;
			uint32_t streamSize;
			uint32_t numberOfStreamChannels;
			std::vector<std::vector<float>>* streamingBuffer;
			uint32_t sampleCounter;
		};


		class WaveWriter
		{
		public:
			WaveWriter() = default;
			~WaveWriter() = default;
			WaveWriter(const WaveWriter& waveWriter) = default;
			void attachFile(AudioFile<float>* file,uint32_t numberOfChannels,uint32_t numberOfSamples);
			void attachStreamBuffer(std::vector<std::vector<float>>* streamingBuffer);
			void writeBuffer();
		protected:
			AudioFile<float>* file;
			uint32_t streamSize;
			uint32_t numberOfStreamChannels;
			std::vector<std::vector<float>>* streamingBuffer;
			uint32_t sampleCounter;
		};

	}
}


#endif
