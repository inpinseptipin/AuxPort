#ifndef AUXPORT_AUXMIXER_H
#define AUXPORT_AUXMIXER_H

#include "../../../Core/Env/AuxEnv.h"
#include "../../../Core/Log/AuxLog.h"
#include "../../../Core/SIMD/AuxSimd.h"


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
	}
}
#endif
