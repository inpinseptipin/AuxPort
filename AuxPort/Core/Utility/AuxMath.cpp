#include "AuxMath.h"

AuxPort::Interpolation::Interpolation()
{
	this->type = Type::Linear;
	startX = endX = delta = valuesCount = 0;
}

void AuxPort::Interpolation::setType(Type type)
{
	this->type = type;
}

void AuxPort::Interpolation::setXValues(float start, float end, float delta)
{
	AuxAssert(start < end, "Start should be less than end!");
	AuxAssert(end >= start + delta, "There should be atleast 2 values for interpolation!");
	AuxAssert(delta > 0, "Delta should be positive (greater than 0)!");
	this->startX = start;
	this->endX = end;
	this->delta = delta;
	this->valuesCount = (end - start) / delta + 1;
}

void AuxPort::Interpolation::setYValues(const std::vector<float> yValues)
{
	AuxAssert(valuesCount != 0, "No xValues provided. Call setXValues() first!");
	AuxAssert(yValues.size() == valuesCount, "Number of yValues must be equal to number of xValues!");
	this->yValues = yValues;
}

float AuxPort::Interpolation::polate(float val)
{
	AuxAssert(valuesCount != 0, "No xValues provided. Call setXValues() first!");
	AuxAssert(yValues.size() == valuesCount, "Number of yValues must be equal to number of xValues!");
	AuxAssert(val >= startX && val <= endX, "val should be in the range [start, end]");
	switch (type)
	{
	case Type::Linear:
		return linearInterpolate(val);
	case Type::Cubic:
		return cubicInterpolate(val);
	case Type::Lagrange:
		return lagrangeInterpolate(val);
	case Type::Cosine:
		return cosineInterpolate(val);
	case Type::Newton:
		return newtonInterpolate(val);
	}
}

float AuxPort::Interpolation::linearInterpolate(float val)
{
	AuxAssert(val >= startX && val <= endX, "Given val should lie in the range [start, end]!");
	size_t index = findIndex(val);
	
	float x0 = startX + index * delta;
	float x1 = x0 + delta;
	float y0 = yValues[index];
	float y1 = yValues[index + 1];
	
	return y0 + (val - x0) * (y1 - y0) / (x1 - x0);
}

float AuxPort::Interpolation::cubicInterpolate(float val)
{
	AuxAssert(val >= startX && val <= endX, "Given val should lie in the range [start, end]!");
	size_t index = findIndex(val);

	float x1 = startX + index * delta;
	float x2 = x1 + delta;
	float x0 = (index == 0 ? startX : x1 - delta);
	float x3 = (index + 2 < valuesCount ? x2 + delta : x2);

	float y0 = yValues[index == 0 ? 0 : index - 1];
	float y1 = yValues[index];
	float y2 = yValues[index + 1];
	float y3 = yValues[index + 2 < valuesCount ? index + 2 : index + 1];

	// Finding coefficients of cubic polynomial curve between x1 and x2
	float a = (-y0 + 3 * y1 - 3 * y2 + y3) / 2;
	float b = y0 - (2.5f * y1) + 2 * y2 - (y3 / 2);
	float c = (-y0 + y2) / 2;
	float d = y1;

	// Normalized val between x1 and x2
	float nVal = (val - x1) / delta;
	return a * nVal * nVal * nVal + b * nVal * nVal + c * nVal + d;
}

float AuxPort::Interpolation::cosineInterpolate(float val)
{
	AuxAssert(val >= startX && val <= endX, "Given val should lie in the range [start, end]!");
	size_t index = findIndex(val);

	float x0 = startX + index * delta;
	float y0 = yValues[index];
	float y1 = yValues[index + 1];

	// Normalized between x0 and x1
	float mu = (val - x0) / delta;
	float mu2 = (1 - cos(mu * AuxPort::pi)) / 2;
	return y0 * (1 - mu2) + y1 * mu2;
}

float AuxPort::Interpolation::lagrangeInterpolate(float val)
{
	AuxAssert(val >= startX && val <= endX, "Given val should lie in the range [start, end]!");

	float res = 0.0f;
	float currTerm;
	float currX;
	float xi = startX;
	for (int i = 0; i < valuesCount; i++)
	{
		currTerm = yValues[i];
		
		currX = startX;
		for (int j = 0; j < valuesCount; j++)
		{
			if (i != j)
				currTerm *= (val - currX) / (xi - currX);
			currX += delta;
		}
		res += currTerm;
		xi += delta;
	}

	return res;
}

float AuxPort::Interpolation::newtonInterpolate(float val)
{
	AuxAssert(val >= startX && val <= endX, "Given val should lie in the range [start, end]!");

	std::vector<float> dividedDifferences = yValues;
	for (int i = 1; i < dividedDifferences.size(); i++)
	{
		for (int j = dividedDifferences.size() - 1; j >= i; j--)
		{
			dividedDifferences[j] = (dividedDifferences[j] - dividedDifferences[j - 1]) / (i * delta);
		}
	}

	float res = dividedDifferences[0];
	float factor = 1.0f;
	float xi = startX;
	for (int i = 1; i < dividedDifferences.size(); i++)
	{
		factor *= (val - xi);
		res += dividedDifferences[i] * factor;
		xi += delta;
	}

	return res;
}

size_t AuxPort::Interpolation::findIndex(float xVal)
{
	size_t index = (xVal - startX) / delta;
	AuxAssert(index < yValues.size() - 1 && index >= 0, "Given val should lie between two defined xValues!");
	return index;
}

AuxPort::FastRandomFloat::FastRandomFloat()
{
	randomSeed = 1;
}

AuxPort::FastRandomFloat::FastRandomFloat(const int& randomSeed)
{
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
