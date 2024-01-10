#ifndef AUXPORT_FIR_H
#define AUXPORT_FIR_H

#include<vector>
#include"../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
#include <functional>
#include "../Windows/AuxWindow.h"
namespace AuxPort
{
	namespace Audio
	{
		class FIR : public ILog
		{
		public:
			FIR() = default;
			~FIR() = default;
			FIR(const FIR& response) = default;
			virtual void filterAlgo() = 0;
			void setSampleRate(uint32_t sampleRate);
			void compute(float passband, float stopband, uint32_t order);
			void compute(float cutoffFrequency, uint32_t order);
			void replace(const std::vector<float>& impulseResponse);
			void replace(float* impulseResponse, uint32_t size);
			void normalize();
			void Log() override;
			std::vector<float>* getImpulseResponse();
		protected:
			std::vector<float> impulseResponse;
			float passband = 0;
			float stopband = 0;
			float cutoff = 0;
			float normFreq = 0;
			uint32_t order = 0;
			uint32_t sampleRate = 0;
		};

		class RectangleFIR : public FIR
		{
		public:
			RectangleFIR() = default;
			~RectangleFIR() = default;
			RectangleFIR(const RectangleFIR& rectangleFIR) = default;
			void filterAlgo() override;
		};

		class HammingFIR : public FIR
		{
		public:
			HammingFIR() = default;
			~HammingFIR() = default;
			HammingFIR(const HammingFIR& hammingFIR) = default;
			void filterAlgo() override;
		};

		class HannFIR : public FIR
		{
		public:
			HannFIR() = default;
			~HannFIR() = default;
			HannFIR(const HannFIR& hannFIR) = default;
			void filterAlgo() override;
		};

		class BlackmanFIR : public FIR
		{
		public:
			BlackmanFIR() = default;
			~BlackmanFIR() = default;
			BlackmanFIR(const BlackmanFIR& blackmanFIR) = default;
			void filterAlgo() override;
		};

		
	}
}

#endif
