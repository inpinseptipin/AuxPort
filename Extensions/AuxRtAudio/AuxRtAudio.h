#ifndef AUXPORT_RTAUDIO_H
#define AUXPORT_RTAUDIO_H
/*
			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2023, Satyarth Arora
			All rights reserved.

			Redistribution and use in source and binary forms, with or without
			modification, are permitted provided that the following conditions are met:

			1. Redistributions of source code must retain the above copyright notice, this
			   list of conditions and the following disclaimer.

			2. Redistributions in binary form must reproduce the above copyright notice,
			   this list of conditions and the following disclaimer in the documentation
			   and/or other materials provided with the distribution.

			3. Neither the name of the copyright holder nor the names of its
			   contributors may be used to endorse or promote products derived from
			   this software without specific prior written permission.

			THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
			AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
			DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
			FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
			DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
			SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
			CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
			OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
			OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "RtAudio.h"
#include "AuxPort.h"

namespace AuxPort
{
namespace Extensions
{
	class AuxRtAudioDevice
	{
	public:
		AuxRtAudioDevice(const RtAudio::DeviceInfo& deviceInfo);
		AuxRtAudioDevice(const AuxRtAudioDevice& obj) = default;
		~AuxRtAudioDevice() = default;

		unsigned int ID;
		std::string name;
		unsigned int outputChannels;
		unsigned int inputChannels;
		unsigned int duplexChannels;
		bool isDefaultOutput;
		bool isDefaultInput;
		std::vector<unsigned int> sampleRates;
		unsigned int currentSampleRate;
		unsigned int preferredSampleRate;

		// TO-DO : Implement wrapper for RtAudioFormat
		RtAudioFormat nativeFormats;
	};
	
	template <class sampleType>
	class AuxRtAudio
	{
	public:
		// Stream Type
		enum class StreamType { Playback, Record, Duplex };
		
		// Default Constructor
		AuxRtAudio()
		{
			setStreamType(StreamType::Playback);
			setDeviceId(getDefaultOutputDeviceId());
			AuxRtAudioDevice defaultDevice = getDeviceInfo(parameters.deviceId);
			setChannelCount(2);
			setFirstChannelIndex(0);
			setSampleRate(defaultDevice.preferredSampleRate);
			setBufferSize(256);
			setDefaultUserCallback();
			format = getFormat();
		}

		// Destructor
		~AuxRtAudio()
		{
			closeStream();
		}

		// Audio Devices Methods
		unsigned int getDeviceCount()
		{
			return api.getDeviceCount();
		}

		AuxRtAudioDevice getDeviceInfo(unsigned int deviceId)
		{
			return AuxRtAudioDevice(api.getDeviceInfo(deviceId));
		}

		std::vector<unsigned int> getDeviceIds()
		{
			return api.getDeviceIds();
		}

		std::vector<std::string> getDeviceNames()
		{
			return api.getDeviceNames();
		}

		unsigned int getDefaultInputDeviceId()
		{
			return api.getDefaultInputDevice();
		}

		unsigned int getDefaultOutputDeviceId()
		{
			return api.getDefaultOutputDevice();
		}

		// Stream Parameter Methods
		void setStreamType(const StreamType& type)
		{
			this->type = type;
		}

		void setDeviceId(unsigned int deviceId)
		{
			parameters.deviceId = deviceId;
		}

		void setChannelCount(unsigned int count)
		{
			parameters.nChannels = count;
		}

		void setFirstChannelIndex(unsigned int index)
		{
			parameters.firstChannel = index;
		}

		void setSampleRate(unsigned int sampleRate)
		{
			this->sampleRate = sampleRate;
		}

		void setBufferSize(unsigned int bufferSize)
		{
			this->bufferSize = bufferSize;
		}

		// Stream Methods
		void startStream()
		{
			RtAudioErrorType errorCode;
			switch (type)
			{
			case StreamType::Playback:
				errorCode = api.openStream(&parameters, NULL, format, sampleRate, &bufferSize, &rtAudioCallback, (void*)this);
				break;

			case StreamType::Record:
				errorCode = api.openStream(NULL, &parameters, format, sampleRate, &bufferSize, &rtAudioCallback, (void*)this);
				break;

			case StreamType::Duplex:
				errorCode = api.openStream(&parameters, &parameters, format, sampleRate, &bufferSize, &rtAudioCallback, (void*)this);
				break;
			}
			
			if (errorCode)
				throw std::runtime_error(api.getErrorText());
			api.startStream();
			if (errorCode)
				throw std::runtime_error(api.getErrorText());
		}

		void closeStream()
		{
			if (api.isStreamRunning())
				api.stopStream();

			if (api.isStreamOpen())
				api.closeStream();
		}

		// User Defined Callback lambda with easyi nterface
		// Return zero if no errors
		std::function<int(sampleType* outputBuffer, sampleType* inputBuffer, unsigned int nBufferFrames, double streamTime)> callback;
	private:
		RtAudio api;
		StreamType type;
		unsigned int sampleRate;
		unsigned int bufferSize;
		RtAudioFormat format;
		RtAudio::StreamParameters parameters;

		// Helper Functions
		void setDefaultUserCallback()
		{
			callback = [](sampleType* outputBuffer, sampleType* inputBuffer, unsigned int nBufferFrames, double streamTime) {
				return 0;
			};
		}

		static RtAudioFormat getFormat()
		{
			if (std::is_same<sampleType, int8>::value)
				return RTAUDIO_SINT8;
			else if (std::is_same<sampleType, int16>::value)
				return RTAUDIO_SINT16;
			else if (std::is_same<sampleType, int32>::value)
				return RTAUDIO_SINT32;
			else if (std::is_same<sampleType, float>::value)
				return RTAUDIO_FLOAT32;
			else if (std::is_same<sampleType, double>::value)
				return RTAUDIO_FLOAT32;
			else
				AuxAssert(false, "Unsupported Sample Type!");
		}

		// Playback Callback
		static int rtAudioCallback(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void* userData)
		{
			sampleType* audioOutputBuffer = (sampleType*)outputBuffer;
			sampleType* audioInputBuffer = (sampleType*)inputBuffer;
			auto obj = (AuxRtAudio*)userData;

			// Handle UnderFlow and Overflow here
			//if (status)
				//std::cout << "Stream underflow detected!" << std::endl;

			return obj->callback(audioOutputBuffer, audioInputBuffer, nBufferFrames, streamTime);
		}
	};
}
}

#endif