#include "AuxCaster.h"

AuxPort::Audio::UINT8Converter::UINT8Converter() : data(0)
{
}

AuxPort::Audio::UINT8Converter::UINT8Converter(const std::vector<float>& floatData)
{
	setData(floatData);
}

AuxPort::Audio::UINT8Converter::UINT8Converter(const std::vector<uint8_t>& uint8Data)
{
	setData(uint8Data);
}

void AuxPort::Audio::UINT8Converter::setData(const std::vector<float>& floatData)
{
	uint32 uint8DataSize = floatData.size() * sizeof(float) / sizeof(uint8_t);
	uint8_t* uint8DataPointer = (uint8_t*)floatData.data();
	data.assign(uint8DataPointer, uint8DataPointer + uint8DataSize);
}

void AuxPort::Audio::UINT8Converter::setData(const std::vector<uint8_t>& uint8Data)
{
	data = uint8Data;
}

uint8_t* AuxPort::Audio::UINT8Converter::getUint8DataPointer()
{
	if (data.empty())
		return nullptr;
	else
		return data.data();
}

uint32 AuxPort::Audio::UINT8Converter::getUint8DataSize()
{
	return data.size();
}

std::vector<uint8_t> AuxPort::Audio::UINT8Converter::getUint8Data()
{
	return data;
}

std::vector<float> AuxPort::Audio::UINT8Converter::getFloatData()
{
	float* floatDataPointer = (float*)data.data();
	return std::vector<float>(floatDataPointer, floatDataPointer + getFloatDataSize());
}

float AuxPort::Audio::UINT8Converter::getFloatAt(const uint32 index)
{
	AuxAssert(index < getFloatDataSize(), "Index out of bounds!");
	float* floatDataPointer = (float*)data.data() + index;
	return *floatDataPointer;
}

void AuxPort::Audio::UINT8Converter::setFloatAt(const uint32 index, const float newVal)
{
	AuxAssert(index < getFloatDataSize(), "Index out of bounds!");
	float* floatDataPointer = (float*)data.data() + index;
	*floatDataPointer = newVal;
}

void AuxPort::Audio::UINT8Converter::append(const std::vector<float>& floatData)
{
	uint32 additionalUint8DataSize = floatData.size() * sizeof(float) / sizeof(uint8_t);
	uint8_t* additionalUint8DataPointer = (uint8_t*)floatData.data();
	
	uint32 writeIndex = data.size();
	data.resize(data.size() + additionalUint8DataSize);
	for (uint32 i = 0; i < additionalUint8DataSize; i++)
	{
		data[writeIndex] = additionalUint8DataPointer[i];
		writeIndex++;
	}
}

void AuxPort::Audio::UINT8Converter::pushBack(float newVal)
{
	append({ newVal });
}

uint32 AuxPort::Audio::UINT8Converter::getFloatDataSize()
{
	return data.size() * sizeof(uint8_t) / sizeof(float);
}