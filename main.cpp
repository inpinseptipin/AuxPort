#include "AuxPort/AuxPort.h"
#include "Extensions/AuxAudioFile/AuxAudioFile.h"


int main(int argc, char* argv[])
{
	AuxPort::Audio::STFT stft(64, 50);
	std::vector<float> outputBuffer;
	outputBuffer.resize(64);
	std::vector<float> inputBuffer;
	inputBuffer.resize(64);
	std::unique_ptr<AuxPort::CSV> csvEngine;
	csvEngine.reset(new AuxPort::CSV());
	csvEngine->open("STFTTest.csv", AuxPort::File::Mode::Write, false);
	AuxPort::Audio::Sine::Sine sine;
	sine.setSampleRate(48000);
	sine.init();
	sine.setFrequency(750);
	for (uint32_t i = 0;i < inputBuffer.size();i++)
		inputBuffer[i] = sine.process();
	stft.computeMagnitudeTransform(inputBuffer.data(), outputBuffer.data(), 64, AuxPort::Audio::STFT::initial);
	auto newOutputBuffer = AuxPort::Audio::Window::trim_r<float>(outputBuffer, AuxPort::Audio::Window::TrimType::fromStart, 50);
	for (uint32_t i = 0;i < newOutputBuffer.size();i++)
		newOutputBuffer[i] = abs(newOutputBuffer[i]);
	newOutputBuffer = AuxPort::Utility::linearTodB(newOutputBuffer);
	for (uint32_t j = 0;j < newOutputBuffer.size();j++)
		csvEngine->addDataRow({ std::to_string(newOutputBuffer[j]) });
	
	for (uint32_t i = 0;i < 10;i++)
	{
		for (uint32_t j = 0;j < inputBuffer.size();j++)
			inputBuffer[i] = sine.process();
		stft.computeMagnitudeTransform(inputBuffer.data(), outputBuffer.data(), 64, AuxPort::Audio::STFT::full);
		newOutputBuffer = AuxPort::Audio::Window::trim_r<float>(outputBuffer, AuxPort::Audio::Window::TrimType::fromStart, 50);
		for (uint32_t j = 0;j < newOutputBuffer.size();j++)
			newOutputBuffer[j] = abs(newOutputBuffer[j]);
		newOutputBuffer = AuxPort::Utility::linearTodB(newOutputBuffer);
		for (uint32_t j = 0;j < newOutputBuffer.size();j++)
			csvEngine->addDataRow({ std::to_string(newOutputBuffer[j]) });
	}
	csvEngine->write();
	csvEngine->close();


	
}


