#ifndef AUXPORT_STIMULUS_H
#define AUXPORT_STIMULUS_H

#include "../../Core/Env/AuxEnv.h"
#include<vector>

namespace AuxPort
{
	namespace Audio
	{
		/**
		 Class consisting of static methods to generate Stimuli for various audio applications
		 */
		class Stimulus
		{
		public:
			/**
			  @brief Generates an impulse
			  @param lengthInTime
			  @param sampleRate
			  @return 
			 */
			static std::vector<float> generateImpulse(float lengthInTime,float sampleRate);
			/**
			  @brief Generates an Impulse
			  @param numberOfSamples
			  @return 
			 */
			static std::vector<float> generateImpulse(uint32_t numberOfSamples);
			/**
			  @brief Generates White Noise 
			  @param lengthInTime
			  @param sampleRate
			  @return 
			 */
			static std::vector<float> generateWhiteNoise(float lengthInTime, float sampleRate);
			/**
			  @brief Generates White Noise 
			  @param numberOfSamples
			  @return 
			  \code{.cpp}
			  
			  \endcode 
			 */
			static std::vector<float> generateWhiteNoise(uint32_t numberOfSamples);

			static std::vector<float> generateExponentialSineSweep(float lengthInTime, float startFrequency, float endFrequency, float sampleRate);


		};
	}
}


#endif
