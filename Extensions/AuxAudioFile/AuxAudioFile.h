#ifndef AUXPORT_EXTENSIONS_AUDIOFILE_H
#define AUXPORT_EXTENSIONS_AUDIOFILE_H

#include "AuxPort.h"
#include "AudioFile.h"

namespace AuxPort
{
	namespace Extensions
	{
		/**
		 * WaveFile is an extension to the AudioFile Wave Writing/Reading Library
		 */
		class WaveFile
		{
		public:
			WaveFile() = default;
			~WaveFile() = default;
			WaveFile(const WaveFile& waveFile) = default;
			/**
			  @brief Use this function to attach a streaming buffer to write to read/write from a file 
			  @param streamingBuffer
			 */
			virtual void attachStreamBuffer(std::vector<std::vector<float>>* streamingBuffer);
			/**
			  @brief Use this function to attach an AudioFile pointer for reading/writing to a file.
			  @param file
			 */
			virtual void attachFile(AudioFile<float>* file);
		protected:

			AudioFile<float>* file;
			uint32_t streamSize;
			uint32_t numberOfStreamChannels;
			std::vector<std::vector<float>>* streamingBuffer;
			uint32_t sampleCounter = 0;
		};

		/**
			WaveReader is a buffer based wave reader class
		*/
		class WaveReader : public WaveFile
		{
		public:
			WaveReader() = default;
			~WaveReader() = default;
			WaveReader(const WaveReader& waveReader) = default;
			/**
			  @brief Fill in the next n-samples in your streaming buffer 
			  @param toLoop
			 */
			void readBuffer(bool toLoop = true);
			/**
			   @brief Seeks the track to particular time
			   @param timeInSeconds
			*/
			void seek(double timeInSeconds);
			/**
			   @brief Resets the track to start
			*/
			void reset();

			void setLoop(double loopStartInSeconds,double loopEndInSeconds);
			void enableLoop(bool loop);
		protected:
			size_t loopStartIndex;
			size_t loopEndIndex;
			bool userLoop = false;
		};


		/**
			WaveWriter is a buffer based wave writer class
		*/
		class WaveWriter : public WaveFile
		{
		public:
			WaveWriter() = default;
			~WaveWriter() = default;
			WaveWriter(const WaveWriter& waveWriter) = default;
			/**
			  @brief Attach a pointer to an AudioFile object and provided expected number of channels and samples to be written 
			  @param file
			  @param numberOfChannels
			  @param numberOfSamples
			 */
			void attachFile(AudioFile<float>* file,uint32_t numberOfChannels,uint32_t numberOfSamples);
			/**
			  @brief Fill in the current n-samples from your streaming buffer into the file. 
			 */
			void writeBuffer();
		};

	}
}


#endif
