#ifndef AUXPORT_FIR_H
#define AUXPORT_FIR_H

#include<vector>
#include"../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
#include <functional>
#include "../Windows/AuxWindow.h"
#include "../../Core/Utility/AuxCircularBuffer.h"
namespace AuxPort
{
	namespace Audio
	{

		///////////////////////////////////////////////////////////////////////////////////////
		/// [Base Class] Parent class for all FIR Design SubClasses
		///////////////////////////////////////////////////////////////////////////////////////
		class FIR : public ILog
		{
		public:
			FIR() = default;
			~FIR() = default;
			FIR(const FIR& response) = default;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Virtual Function] Implement this function with your FIR Algorithm in your Derived Class [Overridable]
		///////////////////////////////////////////////////////////////////////////////////////
			virtual void filterAlgo() = 0;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Sets the Sample Rate
		///////////////////////////////////////////////////////////////////////////////////////
			void setSampleRate(uint32_t sampleRate);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Function designs an FIR by taking in Passband and stopband frequencies for a particular provided Order
		///////////////////////////////////////////////////////////////////////////////////////
			void compute(float passband, float stopband, uint32_t order);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Function designs an FIR by taking a cutoff frequency for a particular provided Order
		///////////////////////////////////////////////////////////////////////////////////////
			void compute(float cutoffFrequency, uint32_t order);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Method to load an impulse response into an FIR object...can be used with the FIR Engine
		///////////////////////////////////////////////////////////////////////////////////////
			void replace(const std::vector<float>& impulseResponse);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Method to load an impulse response into an FIR object...can be used with the FIR Engine
		///////////////////////////////////////////////////////////////////////////////////////
			void replace(float* impulseResponse, uint32_t size);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Normalize the Impulse Response (In Development)
		///////////////////////////////////////////////////////////////////////////////////////
			void normalize();
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Logs the Impulse Response onto the Console
		///////////////////////////////////////////////////////////////////////////////////////
			void Log() override;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Returns a pointer to the internal std::vector containing the IR
		///////////////////////////////////////////////////////////////////////////////////////
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

		class BartlettFIR : public FIR
		{
		public:
			BartlettFIR() = default;
			~BartlettFIR() = default;
			BartlettFIR(const BartlettFIR& bartlettFIR) = default;
			void filterAlgo() override;
		};
		
		class BartlettHannFIR : public FIR
		{
		public:
			BartlettHannFIR() = default;
			~BartlettHannFIR() = default;
			BartlettHannFIR(const BartlettHannFIR& bartlettHannFIR) = default;
			void filterAlgo() override;
		};

		class NuttallFIR : public FIR
		{
		public:
			NuttallFIR() = default;
			~NuttallFIR() = default;
			NuttallFIR(const NuttallFIR& nuttallFIR) = default;
			void filterAlgo() override;
		};

		class FlatFIR : public FIR
		{
		public:
			FlatFIR() = default;
			~FlatFIR() = default;
			FlatFIR(const FlatFIR& flatFIR) = default;
			void filterAlgo() override;
		};

		class BlackmanHarrisFIR : public FIR
		{
		public:
			BlackmanHarrisFIR() = default;
			~BlackmanHarrisFIR() = default;
			BlackmanHarrisFIR(const BlackmanHarrisFIR& blackmanHarrisFIR) = default;
			void filterAlgo() override;
		};

		class Convolution
		{
			std::vector<float> impulseResponse;
			AuxPort::CircularBuffer<float> inputBuffer;
			size_t irSize;
		public:
			Convolution() = default;
			~Convolution() = default;
			Convolution(const Convolution& convolution) = default;
			void setImpulseResponse(const std::vector<float>& impulseResponse);
			void setImpulseResponse(float* impulseResponse, uint32_t size);
			void setImpulseResponse(std::vector<float>* impulseResponse, uint32_t size);
			float process(float sample);
		};		
	}
}

#endif
