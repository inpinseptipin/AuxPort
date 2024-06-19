#include "AuxInterpolation.h"

AuxPort::Interpolator::Interpolator(size_t bufferSize) : bufferSize(bufferSize), circularBuffer(bufferSize)
{
}

void AuxPort::Interpolator::generateXYVectors(std::vector<float>& xValues, std::vector<float>& yValues, float currSample)
{
	xValues.reserve(bufferSize + 1);
	yValues.reserve(bufferSize + 1);
	for (size_t i = 0; i < bufferSize; i++)
	{
		xValues.push_back(i);
		yValues.push_back(circularBuffer.getShiftedElement(i));
	}
	xValues.push_back(bufferSize);
	yValues.push_back(currSample);
}

float AuxPort::Interpolator::linearInterpolate(float x0, float y0, float x1, float y1, float x)
{
	AuxAssert(x >= x0 && x <= x1, "x should lie in the range [x0, x1]");
	return y0 + (x - x0) * (y1 - y0) / (x1 - x0);;
}

float AuxPort::Interpolator::cubicInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x)
{
	AuxAssert(xValues.size() == 4 && yValues.size() == 4, "xValues and yValues should have size 4!");

	// Finding coefficients of cubic polynomial curve between x1 and x2
	float a = (-yValues[0] + 3 * yValues[1] - 3 * yValues[2] + yValues[3]) / 2;
	float b = yValues[0] - (2.5f * yValues[1]) + 2 * yValues[2] - (yValues[3] / 2);
	float c = (-yValues[0] + yValues[2]) / 2;
	float d = yValues[1];

	// Normalized value of x between x1 and x2
	float nVal = (x - xValues[1]) / (xValues[2] - xValues[1]);
	return a * nVal * nVal * nVal + b * nVal * nVal + c * nVal + d;
}

float AuxPort::Interpolator::cosineInterpolate(float x0, float y0, float x1, float y1, float x)
{
	AuxAssert(x >= x0 && x <= x1, "x should lie in the range [x0, x1]");
	float mu = (x - x0) / (x1 - x0);
	float mu2 = (1 - cos(mu * AuxPort::pi)) / 2;
	return y0 * (1 - mu2) + y1 * mu2;
}

float AuxPort::Interpolator::lagrangeInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x)
{
	AuxAssert(xValues.size() == yValues.size(), "xValues and yValues should have same size!");
	AuxAssert(x >= xValues.front() && x <= xValues.back(), "x should lie within the provided Xvalues!");

	float res = 0.0f;
	float currTerm;
	for (int i = 0; i < xValues.size(); i++)
	{
		currTerm = yValues[i];
		for (int j = 0; j < xValues.size(); j++)
		{
			if (i != j)
				currTerm *= (x - xValues[j]) / (xValues[i] - xValues[j]);
		}
		res += currTerm;
	}
	return res;
}

float AuxPort::Interpolator::newtonInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x)
{
	AuxAssert(xValues.size() == yValues.size(), "xValues and yValues should have same size!");
	AuxAssert(x >= xValues.front() && x <= xValues.back(), "x should lie within the provided Xvalues!");

	std::vector<float> dividedDifferences = yValues;
	for (int i = 1; i < dividedDifferences.size(); i++)
	{
		for (int j = dividedDifferences.size() - 1; j >= i; j--)
		{
			dividedDifferences[j] = (dividedDifferences[j] - dividedDifferences[j - 1]) / (xValues[j] - xValues[j - i]);
		}
	}

	float res = dividedDifferences[0];
	float factor = 1.0f;
	for (int i = 1; i < dividedDifferences.size(); i++)
	{
		factor *= (x - xValues[i - 1]);
		res += dividedDifferences[i] * factor;
	}

	return res;
}

AuxPort::LinearInterpolator::LinearInterpolator() : Interpolator(1)
{
}

float AuxPort::LinearInterpolator::interpolate(float currSample)
{
	float y0 = circularBuffer.getShiftedElement(-1);
	circularBuffer.push(currSample);
	return Interpolator::linearInterpolate(0, y0, 1, currSample, 0.5);
}

AuxPort::CubicInterpolator::CubicInterpolator() : Interpolator(3)
{}

float AuxPort::CubicInterpolator::interpolate(float currSample)
{
	float y2 = circularBuffer.getShiftedElement(-1);
	float y1 = circularBuffer.getShiftedElement(-2);
	float y0 = circularBuffer.getShiftedElement(-3);
	circularBuffer.push(currSample);
	return Interpolator::cubicInterpolate({ 0, 1, 2, 3 }, {y0, y1, y2, currSample}, 2.5);
}

AuxPort::CosineInterpolator::CosineInterpolator() : Interpolator(1)
{
}

float AuxPort::CosineInterpolator::interpolate(float currSample)
{
	float y0 = circularBuffer.getShiftedElement(-1);
	circularBuffer.push(currSample);
	return Interpolator::cosineInterpolate(0, y0, 1, currSample, 0.5);
}

AuxPort::LagrangeInterpolator::LagrangeInterpolator() : Interpolator(15)
{
}

AuxPort::LagrangeInterpolator::LagrangeInterpolator(size_t bufferSize) : Interpolator(bufferSize)
{
}

float AuxPort::LagrangeInterpolator::interpolate(float currSample)
{
	std::vector<float> xValues;
	std::vector<float> yValues;
	generateXYVectors(xValues, yValues, currSample);
	circularBuffer.push(currSample);
	return Interpolator::lagrangeInterpolate(xValues, yValues, static_cast<float>(bufferSize) - 0.5f);
}

AuxPort::NewtonInterpolator::NewtonInterpolator() : Interpolator(15)
{
}

AuxPort::NewtonInterpolator::NewtonInterpolator(size_t bufferSize) : Interpolator(bufferSize)
{
}

float AuxPort::NewtonInterpolator::interpolate(float currSample)
{
	std::vector<float> xValues;
	std::vector<float> yValues;
	generateXYVectors(xValues, yValues, currSample);
	circularBuffer.push(currSample);
	return Interpolator::newtonInterpolate(xValues, yValues, static_cast<float>(bufferSize) - 0.5f);
}