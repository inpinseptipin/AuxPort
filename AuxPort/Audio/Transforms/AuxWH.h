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
		/**
		 * Implementation of the Fast Walsh Hadamard Transform
		 */
		class WalshHadamardTransform
		{
		public:
			/**
			  @brief Instantiates the Fast Walsh Hadamard Transform Engine with the size 
			  @param whtSize
			  \code{.cpp}
				AuxPort::Audio::WalshHadamardTransform wht(512);
			  \endcode 
			 */
			WalshHadamardTransform(size_t whtSize);
			~WalshHadamardTransform() = default;
			WalshHadamardTransform(const WalshHadamardTransform& walshHadamardTransform) = default;
			/**
			  @brief Computes the forward transform
			  @param input
			  @param output
			  \code{.cpp}
			  
			  \endcode 
			 */
			void transform(const std::vector<float>& input, std::vector<float>& output);
			/**
			  @brief Computes the inverse transform 
			  @param output
			  \code{.cpp}
			  
			  \endcode 
			 */
			void inverseTransform(std::vector<float>& output);
		protected:
			/**
			  @brief FWHT Kernel 
			 */
			void compute();
			std::vector<float> whtBuffer;
			size_t whtSize;
		};
	}
}


#endif
