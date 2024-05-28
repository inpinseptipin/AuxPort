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
	}
}

float AuxPort::Interpolation::linearInterpolate(float val)
{
	size_t index = findIndex(val);
	AuxAssert(index < yValues.size() - 1, "Given val should lie between two defined xValues!");
	
	float x0 = startX + index * delta;
	float x1 = x0 + delta;
	float y0 = yValues[index];
	float y1 = yValues[index + 1];
	
	return y0 + (val - x0) * (y1 - y0) / (x1 - x0);
}

float AuxPort::Interpolation::cubicInterpolate(float val)
{
	size_t index = findIndex(val);
	AuxAssert(index < yValues.size() - 1, "Given val should lie between two defined xValues!");

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
	float nVal = (val - x1) / (x2 - x1);
	return a * nVal * nVal * nVal + b * nVal * nVal + c * nVal + d;
}

float AuxPort::Interpolation::lagrangeInterpolate(float val)
{
	size_t index = findIndex(val);
	AuxAssert(index < yValues.size() - 1, "Given val should lie between two defined xValues!");

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

size_t AuxPort::Interpolation::findIndex(float xVal)
{
	return (xVal - startX) / delta;
}
