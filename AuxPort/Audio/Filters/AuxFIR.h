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
			enum Type
			{
				LowPass, HighPass, BandPass, BandReject
			};

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
			void compute(float passband, float stopband, uint32_t order, Type filterType = Type::LowPass);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Function designs an FIR by taking a cutoff frequency for a particular provided Order
		///////////////////////////////////////////////////////////////////////////////////////
			void compute(float cutoffFrequency, uint32_t order, Type filterType = Type::LowPass);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Method to load an impulse response into an FIR object...can be used with the FIR Engine
		///////////////////////////////////////////////////////////////////////////////////////
			void replace(const std::vector<float>& impulseResponse);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Method to load an impulse response into an FIR object...can be used with the FIR Engine
		///////////////////////////////////////////////////////////////////////////////////////
			void replace(float* impulseResponse, uint32_t size);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Logs the Impulse Response onto the Console
		///////////////////////////////////////////////////////////////////////////////////////
			void Log() override;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Returns a pointer to the internal std::vector containing the IR
		///////////////////////////////////////////////////////////////////////////////////////
			std::vector<float>* getImpulseResponse();
		protected:
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Normalize the Impulse Response (In Development)
		///////////////////////////////////////////////////////////////////////////////////////
			void normalize();
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Performs spectral reversal of Impulse Response
		///////////////////////////////////////////////////////////////////////////////////////
			void spectralReversal();
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Applys a window on the Impulse Response.
		///////////////////////////////////////////////////////////////////////////////////////
			virtual void applyWindow();

			Type filterType;
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
		protected:
			void genIR(float band);
			void genIR(float passband, float stopband);
			void filterAlgo() override;

		};

		class HammingFIR : public RectangleFIR
		{
		public:
			HammingFIR() = default;
			~HammingFIR() = default;
			HammingFIR(const HammingFIR& hammingFIR) = default;
			void applyWindow() override;
		};

		class HannFIR : public RectangleFIR
		{
		public:
			HannFIR() = default;
			~HannFIR() = default;
			HannFIR(const HannFIR& hannFIR) = default;
			void applyWindow() override;
		};

		class BlackmanFIR : public RectangleFIR
		{
		public:
			BlackmanFIR() = default;
			~BlackmanFIR() = default;
			BlackmanFIR(const BlackmanFIR& blackmanFIR) = default;
			void applyWindow() override;
		};

		class BartlettFIR : public RectangleFIR
		{
		public:
			BartlettFIR() = default;
			~BartlettFIR() = default;
			BartlettFIR(const BartlettFIR& bartlettFIR) = default;
			void applyWindow() override;
		};
		
		class BartlettHannFIR : public RectangleFIR
		{
		public:
			BartlettHannFIR() = default;
			~BartlettHannFIR() = default;
			BartlettHannFIR(const BartlettHannFIR& bartlettHannFIR) = default;
			void applyWindow() override;
		};

		class NuttallFIR : public RectangleFIR
		{
		public:
			NuttallFIR() = default;
			~NuttallFIR() = default;
			NuttallFIR(const NuttallFIR& nuttallFIR) = default;
			void applyWindow() override;
		};

		class FlatFIR : public RectangleFIR
		{
		public:
			FlatFIR() = default;
			~FlatFIR() = default;
			FlatFIR(const FlatFIR& flatFIR) = default;
			void applyWindow() override;
		};

		class BlackmanHarrisFIR : public RectangleFIR
		{
		public:
			BlackmanHarrisFIR() = default;
			~BlackmanHarrisFIR() = default;
			BlackmanHarrisFIR(const BlackmanHarrisFIR& blackmanHarrisFIR) = default;
			void applyWindow() override;
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
