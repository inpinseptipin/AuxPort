 #ifndef AUXPORT_FIR_H
#define AUXPORT_FIR_H

#include<vector>
#include"../../Core/Env/AuxEnv.h"
#include "../../Core/Utility/AuxUtility.h"
#include <functional>
#include "../Windows/AuxWindow.h"
#include "../../Core/Utility/AuxCircularBuffer.h"
#include "../FFT/AuxFFT.h"
namespace AuxPort
{
	namespace Audio
	{

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Parent class for all FIR Design SubClasses
		///////////////////////////////////////////////////////////////////////////////////////
		class FIR : public ILog
		{
		public:
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Represents the type of FIR Filter
			///////////////////////////////////////////////////////////////////////////////////////
			enum Type
			{
				LowPass, HighPass, BandPass, BandReject
			};

			FIR() = default;
			~FIR() = default;
			FIR(const FIR& response) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Implement this function with your FIR Algorithm in your Derived Class [Overridable]
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void filterAlgo() = 0;
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Sets the Sample Rate
			///////////////////////////////////////////////////////////////////////////////////////
			void setSampleRate(uint32_t sampleRate);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Function designs an FIR by taking in Passband and stopband frequencies for a particular provided Order
			///////////////////////////////////////////////////////////////////////////////////////
			void compute(float passband, float stopband, uint32_t order, Type filterType = Type::LowPass);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Function designs an FIR by taking a cutoff frequency for a particular provided Order
			///////////////////////////////////////////////////////////////////////////////////////
			void compute(float cutoffFrequency, uint32_t order, Type filterType = Type::LowPass);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Method to load an impulse response into an FIR object...can be used with the FIR Engine
			///////////////////////////////////////////////////////////////////////////////////////
			void replace(const std::vector<float>& impulseResponse);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Method to load an impulse response into an FIR object...can be used with the FIR Engine
			///////////////////////////////////////////////////////////////////////////////////////
			void replace(float* impulseResponse, uint32_t size);
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Logs the Impulse Response onto the Console
			///////////////////////////////////////////////////////////////////////////////////////
			void Log() override;
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns a pointer to the internal std::vector containing the IR
			///////////////////////////////////////////////////////////////////////////////////////
			std::vector<float>* getImpulseResponse();
		protected:
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Normalize the Impulse Response (In Development)
			///////////////////////////////////////////////////////////////////////////////////////
			void normalize();
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Performs spectral reversal of Impulse Response
			///////////////////////////////////////////////////////////////////////////////////////
			void spectralReversal();
			
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Applyies a window on the Impulse Response.
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

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Rectangle Window
		///////////////////////////////////////////////////////////////////////////////////////
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

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Hamming Window
		///////////////////////////////////////////////////////////////////////////////////////
		class HammingFIR : public RectangleFIR
		{
		public:
			HammingFIR() = default;
			~HammingFIR() = default;
			HammingFIR(const HammingFIR& hammingFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Hann Window
		///////////////////////////////////////////////////////////////////////////////////////
		class HannFIR : public RectangleFIR
		{
		public:
			HannFIR() = default;
			~HannFIR() = default;
			HannFIR(const HannFIR& hannFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Blackman Window
		///////////////////////////////////////////////////////////////////////////////////////
		class BlackmanFIR : public RectangleFIR
		{
		public:
			BlackmanFIR() = default;
			~BlackmanFIR() = default;
			BlackmanFIR(const BlackmanFIR& blackmanFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Bartlett Window
		///////////////////////////////////////////////////////////////////////////////////////
		class BartlettFIR : public RectangleFIR
		{
		public:
			BartlettFIR() = default;
			~BartlettFIR() = default;
			BartlettFIR(const BartlettFIR& bartlettFIR) = default;
			void applyWindow() override;
		};
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with BartletttHann Window
		///////////////////////////////////////////////////////////////////////////////////////
		class BartlettHannFIR : public RectangleFIR
		{
		public:
			BartlettHannFIR() = default;
			~BartlettHannFIR() = default;
			BartlettHannFIR(const BartlettHannFIR& bartlettHannFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Nuttall Window
		///////////////////////////////////////////////////////////////////////////////////////
		class NuttallFIR : public RectangleFIR
		{
		public:
			NuttallFIR() = default;
			~NuttallFIR() = default;
			NuttallFIR(const NuttallFIR& nuttallFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Flat Window
		///////////////////////////////////////////////////////////////////////////////////////
		class FlatFIR : public RectangleFIR
		{
		public:
			FlatFIR() = default;
			~FlatFIR() = default;
			FlatFIR(const FlatFIR& flatFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Represents an FIR filter with Rectangle Window
		///////////////////////////////////////////////////////////////////////////////////////
		class BlackmanHarrisFIR : public RectangleFIR
		{
		public:
			BlackmanHarrisFIR() = default;
			~BlackmanHarrisFIR() = default;
			BlackmanHarrisFIR(const BlackmanHarrisFIR& blackmanHarrisFIR) = default;
			void applyWindow() override;
		};

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Provides an interface to convolve a signal with an Impulse Response
		///////////////////////////////////////////////////////////////////////////////////////
		class Convolution
		{
		protected:
			std::vector<float> impulseResponse;
			AuxPort::CircularBuffer<float> inputBuffer;
			size_t irSize;
		public:
			Convolution() = default;
			~Convolution() = default;
			Convolution(const Convolution& convolution) = default;

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Sets the Impulse Response for Convolution using the given vector
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void setImpulseResponse(const std::vector<float>& impulseResponse);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Sets the Impulse Response for Convolution using the given array pointer
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void setImpulseResponse(const float* impulseResponse, uint32_t size);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Sets the Impulse Response for Convolution using the given vector pointer
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void setImpulseResponse(std::vector<float>* impulseResponse, uint32_t size);

			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the sample value after convolving the current sample with given IR
			///////////////////////////////////////////////////////////////////////////////////////
			virtual float process(float sample);
			///////////////////////////////////////////////////////////////////////////////////////
			/// @brief Returns the sample value after convolving the current sample with given IR
			///////////////////////////////////////////////////////////////////////////////////////
			virtual void process(const float* inputBuffer, float* outputBuffer, uint32_t bufferSize);
		};


		/**
		 * Fast Convolution implements overlap-save for Fast FIR filtering
		 */
		class FastConvolution : Convolution
		{
		public:
			/**
			  @brief Constructor that takes in the fft size to initialize the engine 
			  @param fftSize
			  \code{.cpp}
			  
			  \endcode 
			 */
			FastConvolution(uint32_t fftSize);
			~FastConvolution() = default;
			/**
			  @brief Initializes the Filter module with the impulse response provided 
			  @param impulseResponse
			 */
			void setImpulseResponse(const std::vector<float>& impulseResponse) override;
			/**
			  @brief Initializes the Filter module with the impulse response provided
			  @param impulseResponse
			 */
			void setImpulseResponse(const float* impulseResponse, uint32_t size) override;
			/**
			  @brief Fast Convolution, in-place and out-place, Buffer Size does not have to equal FFT Size
			  @param impulseResponse
			 */
			virtual void process(const float* input, float* output, uint32_t bufferSize);
			/**
			  @brief Resets the convolution kernel, to start of playback 
			  \code{.cpp}
			  
			  \endcode 
			 */
			void reset();
		protected:
			/**
			  @brief Performs Overlap-save based Fast Convolution 
			  \code{.cpp}
			  
			  \endcode 
			 */
			void compute();
			std::vector<std::complex<float>>* fftFrame;
			std::vector<std::complex<float>>* filterFFTFrame;
			std::unique_ptr<AuxPort::Audio::FourierTransform> filterFourierTransform;
			std::unique_ptr<AuxPort::Audio::FourierTransform> audioFourierTransform;

			std::vector<float> inputDataBuffer;
			std::vector<float> overlapBuffer;
			std::vector<float> outputDataBuffer;
			std::vector<float> fftInputBuffer;
			std::vector<float> fftOutputBuffer;

			uint32_t writeIndex;
			uint32_t readIndex;

			size_t impulseResponseSize;


		};

		/**  Fast Convolution 2 implements overlap-add */
		class FastConvolution2 : public FastConvolution
		{
		public:
			FastConvolution2() = default;
			~FastConvolution2() = default;
			FastConvolution2(const FastConvolution2& fastConvolutionv2) = default;
			void process(const float* input, float* output, uint32_t bufferSize) override;
		protected:
		};

	}
}

#endif
