#include "AuxMath.h"

AuxPort::FastRandomFloat::FastRandomFloat()
{
	randomSeed = 1;
}

AuxPort::FastRandomFloat::FastRandomFloat(const int& randomSeed)
{
	AuxAssert(randomSeed != 0, "Random Seed cannot be 0!");
	this->randomSeed = randomSeed;
}

float AuxPort::FastRandomFloat::getRandomFloat()
{
	randomSeed *= 16807;
	return (float)randomSeed * 4.6566129e-010f;
}

float AuxPort::FastRandomFloat::getRandomFloat(float start, float end)
{
	AuxAssert(start <= end, "start should be <= end.");
	return start + (end - start) * (getRandomFloat() + 1.0) / 2 ;
}
