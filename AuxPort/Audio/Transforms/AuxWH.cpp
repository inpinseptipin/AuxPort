#include "AuxWH.h"

AuxPort::Audio::WalshHadamardTransform::WalshHadamardTransform(size_t whtSize)
{
	uint32_t isPowerOfTwo = (uint32_t)(whtSize & (whtSize - 1));
	AuxAssert(isPowerOfTwo == 0, "Library is compatible for WHT sizes that are multiples of 2");
	this->whtSize = whtSize;
	whtBuffer.resize(whtSize);
}

void AuxPort::Audio::WalshHadamardTransform::transform(const std::vector<float>& input, std::vector<float>& output)
{
	std::copy(input.begin(),input.end(),whtBuffer.begin());
	compute();
	std::copy(whtBuffer.begin(), whtBuffer.end(), output.begin());
}

void AuxPort::Audio::WalshHadamardTransform::inverseTransform(std::vector<float>& output)
{
	compute();
	std::copy(whtBuffer.begin(), whtBuffer.end(), output.begin());
}

void AuxPort::Audio::WalshHadamardTransform::compute()
{
	uint32_t h = 1;
	float x;
	float y;
	while (h < whtBuffer.size())
	{
		for (uint32_t i = 0; i < whtBuffer.size(); i +=h * 2)
		{
			for (uint32_t j = i; j < i + h; j++)
			{
				x = whtBuffer[j];
				y = whtBuffer[j + h];
				whtBuffer[j] = x + y;
				whtBuffer[j + h] = x - y;
			}
		}
		AuxPort::Utility::divide(whtBuffer, AuxPort::sqrt2);
		h *= 2;

	}
}
