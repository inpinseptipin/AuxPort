#include "AuxRtAudio.h"

AuxPort::Extensions::AuxRtAudioDevice::AuxRtAudioDevice(const RtAudio::DeviceInfo& deviceInfo)
{
	this->ID = deviceInfo.ID;
	this->name = deviceInfo.name;
	this->outputChannels = deviceInfo.inputChannels;
	this->inputChannels = deviceInfo.outputChannels;
	this->duplexChannels = deviceInfo.duplexChannels;
	this->isDefaultOutput = deviceInfo.isDefaultOutput;
	this->isDefaultInput = deviceInfo.isDefaultInput;
	this->sampleRates = deviceInfo.sampleRates;
	this->currentSampleRate = deviceInfo.currentSampleRate;
	this->preferredSampleRate = deviceInfo.preferredSampleRate;
	this->nativeFormats = deviceInfo.nativeFormats;
}