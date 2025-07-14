#ifndef AUXPORT_STIMULUS_H
#define AUXPORT_STIMULUS_H

#include <vector>
#include "../../Core/Env/AuxEnv.h"

namespace AuxPort
{
	namespace Audio
	{
		class Stimulus
		{
		public:
			static std::vector<float> generateImpulse(float lengthInTime,float sampleRate);
		};
	}
}


#endif
