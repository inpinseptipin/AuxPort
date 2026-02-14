#ifndef AUXPORT_WALSH_HADAMARD_TRANSFORM
#define AUXPORT_WALSH_HADAMARD_TRANSFORM
#include "../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxCircularBuffer.h"
#include "../../Core/Utility/AuxUtility.h"
#include <vector>

namespace AuxPort
{
	namespace Audio
	{
		class WalshHadamardTransform
		{
		public:
			WalshHadamardTransform(size_t whtSize);
			~WalshHadamardTransform() = default;
			WalshHadamardTransform(const WalshHadamardTransform& walshHadamardTransform) = default;
			void transform(const std::vector<float>& input, std::vector<float>& output);
			void inverseTransform(std::vector<float>& output);
		protected:
			void compute();
			std::vector<float> whtBuffer;
			size_t whtSize;
		};
	}
}


#endif
