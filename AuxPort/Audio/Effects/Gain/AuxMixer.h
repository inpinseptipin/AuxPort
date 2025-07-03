#ifndef AUXPORT_AUXMIXER_H
#define AUXPORT_AUXMIXER_H

#include "../../../Core/Env/AuxEnv.h"
#include "../../../Core/Log/AuxLog.h"
#include "../../../Core/SIMD/AuxSimd.h"
#include "../../../Core/Utility/AuxCircularBuffer.h"


namespace AuxPort
{
	namespace Audio
	{
		class DownMixer
		{
		public:
			static void stereoToMono(float* outputMonoChannel, float* leftChannel, float* rightChannel,size_t numberOfSamples);
		};

		class UpMixer
		{
		public:
			static void monoToStereo(float* outputLeftChannel, float* outputRightChannel, float* inputMonoChannel, size_t numberofSamples);
		};

		/**
		 Static Delay Implementation
		 */
		class Delay : public AuxPort::CircularBufferEngine
		{
		public:
			Delay();
			~Delay() = default;
			Delay(const Delay& delay) = default;
			/**
			  @brief Set the max delay time 
			  @param sampleRate
			  @param maxDelayTime
			 */
			void setMaxDelayTime(size_t sampleRate,float maxDelayTime);
			/**
			  @brief Set the delay time 
			  @param delayTime
			 */
			void setDelay(float delayTime);
			/**
			  @brief Gets the delayed sample 
			  @return 
			 */
			float pop() override;
		protected:
			/**
			  @brief Push the sample into the delay buffer 
			  @param sample
			 */
			void push(float sample) override;
			float maxDelayTime;
			size_t sampleRate;
			std::vector<float> delayBuffer;
			float delayTime;
			size_t delayTimeInSamples;
			int writeDelayIndex;
			int readDelayIndex;
		};
	}
}
#endif
