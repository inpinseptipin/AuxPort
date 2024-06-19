#include "AuxInterpolation.h"

AuxPort::Interpolation::Interpolation()
{
	this->type = Type::Linear;
	valuesCount = 0;
}

void AuxPort::Interpolation::setType(Type type)
{
	this->type = type;
}

void AuxPort::Interpolation::setXValues(float start, float end, float delta)
{
	AuxAssert(start < end, "Start should be less than end!");
	AuxAssert(delta > 0, "Delta should be positive (greater than 0)!");
	AuxAssert(end >= start + delta, "There should be atleast 2 values for interpolation!");
	this->valuesCount = (end - start) / delta + 1;
	xValues.reserve(valuesCount);
	for (float currVal = start; currVal <= end; currVal += delta)
		xValues.push_back(currVal);
}

void AuxPort::Interpolation::setXValues(const std::vector<float> xValues)
{
	this->xValues = xValues;
	valuesCount = xValues.size();
	std::sort((this->xValues).begin(), (this->xValues).end());
}

void AuxPort::Interpolation::setYValues(const std::vector<float> yValues)
{
	AuxAssert(valuesCount != 0, "No xValues provided. Call setXValues() first!");
	AuxAssert(yValues.size() == valuesCount, "Number of yValues must be equal to number of xValues!");
	this->yValues = yValues;
}

float AuxPort::Interpolation::interpolate(float val)
{
	AuxAssert(valuesCount != 0, "No xValues provided. Call setXValues() first!");
	AuxAssert(yValues.size() == valuesCount, "Number of yValues must be equal to number of xValues!");
	AuxAssert(val >= xValues.front() && val <= xValues.back(), "val should lie within the provided Xvalues!");
	switch (type)
	{
	case Type::Linear:
		return _interpolateLinear(val);
	case Type::Cubic:
		return _interpolateCubic(val);
	case Type::Lagrange:
		return _interpolateLagrange(val);
	case Type::Cosine:
		return _interpolateCosine(val);
	case Type::Newton:
		return _interpolateNewton(val);
	}
}

float AuxPort::Interpolation::linearInterpolate(float x0, float y0, float x1, float y1, float x)
{
	AuxAssert(x >= x0 && x <= x1, "x should lie in the range [x0, x1]");
	return y0 + (x - x0) * (y1 - y0) / (x1 - x0);;
}

float AuxPort::Interpolation::cubicInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x)
{
	AuxAssert(xValues.size() == 4 && yValues.size() == 4, "xValues and yValues should have size 4!");
	AuxAssert(x >= xValues[1] && x <= xValues[2], "x should lie in the range [x1, x2]");

	// Finding coefficients of cubic polynomial curve between x1 and x2
	float a = (-yValues[0] + 3 * yValues[1] - 3 * yValues[2] + yValues[3]) / 2;
	float b = yValues[0] - (2.5f * yValues[1]) + 2 * yValues[2] - (yValues[3] / 2);
	float c = (-yValues[0] + yValues[2]) / 2;
	float d = yValues[1];

	// Normalized value of x between x1 and x2
	float nVal = (x - xValues[1]) / (xValues[2] - xValues[1]);
	return a * nVal * nVal * nVal + b * nVal * nVal + c * nVal + d;
}

float AuxPort::Interpolation::cosineInterpolate(float x0, float y0, float x1, float y1, float x)
{
	AuxAssert(x >= x0 && x <= x1, "x should lie in the range [x0, x1]");
	float mu = (x - x0) / (x1 - x0);
	float mu2 = (1 - cos(mu * AuxPort::pi)) / 2;
	return y0 * (1 - mu2) + y1 * mu2;
}

float AuxPort::Interpolation::lagrangeInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x)
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

float AuxPort::Interpolation::newtonInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x)
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

float AuxPort::Interpolation::_interpolateLinear(float val)
{
	AuxAssert(val >= xValues.front() && val <= xValues.back(), "val should lie within the provided Xvalues!");

	size_t index = _findIndex(val);
	if (index == valuesCount - 1) return yValues[index];

	float x0 = xValues[index];
	float x1 = xValues[index + 1];
	float y0 = yValues[index];
	float y1 = yValues[index + 1];
	return linearInterpolate(x0, y0, x1, y1, val);
	/*return y0 + (val - x0) * (y1 - y0) / (x1 - x0)*/;
}

float AuxPort::Interpolation::_interpolateCubic(float val)
{
	AuxAssert(val >= xValues.front() && val <= xValues.back(), "val should lie within the provided Xvalues!");

	size_t index = _findIndex(val);
	if (index == valuesCount - 1) return yValues[index];

	float x0 = xValues[index == 0 ? 0 : index - 1];
	float x1 = xValues[index];
	float x2 = xValues[index + 1];
	float x3 = xValues[index + 2 < valuesCount ? index + 2 : index + 1];

	float y0 = yValues[index == 0 ? 0 : index - 1];
	float y1 = yValues[index];
	float y2 = yValues[index + 1];
	float y3 = yValues[index + 2 < valuesCount ? index + 2 : index + 1];

	return cubicInterpolate({ x0, x1, x2, x3 }, { y0, y1, y2, y3 }, val);
}

float AuxPort::Interpolation::_interpolateCosine(float val)
{
	AuxAssert(val >= xValues.front() && val <= xValues.back(), "val should lie within the provided Xvalues!");

	size_t index = _findIndex(val);
	if (index == valuesCount - 1) return yValues[index];

	float x0 = xValues[index];
	float x1 = xValues[index + 1];
	float y0 = yValues[index];
	float y1 = yValues[index + 1];

	return cosineInterpolate(x0, y0, x1, y1, val);
}

float AuxPort::Interpolation::_interpolateLagrange(float val)
{
	AuxAssert(val >= xValues.front() && val <= xValues.back(), "val should lie within the provided Xvalues!");
	return lagrangeInterpolate(xValues, yValues, val);
}

float AuxPort::Interpolation::_interpolateNewton(float val)
{
	AuxAssert(val >= xValues.front() && val <= xValues.back(), "val should lie within the provided Xvalues!");
	return newtonInterpolate(xValues, yValues, val);
}

size_t AuxPort::Interpolation::_findIndex(float xVal)
{
	AuxAssert(xVal >= xValues.front() && xVal <= xValues.back(), "val should lie within the provided Xvalues!");
	for (size_t i = 0; i < xValues.size(); i++)
	{
		if (xValues[i] > xVal)
			return i - 1;
	}
	return valuesCount - 1;
}

AuxPort::SignalInterpolator::SignalInterpolator(size_t bufferSize) : bufferSize(bufferSize), circularBuffer(bufferSize)
{
}

void AuxPort::SignalInterpolator::generateXYVectors(std::vector<float>& xValues, std::vector<float>& yValues, float currSample)
{
	xValues.reserve(bufferSize + 1);
	yValues.reserve(bufferSize + 1);
	for (size_t i = 0; i < bufferSize; i++)
	{
		xValues.push_back(i);
		yValues.push_back(circularBuffer.getShiftedElement(0));
	}
	xValues.push_back(bufferSize);
	yValues.push_back(currSample);
}

AuxPort::LinearSignalInterpolator::LinearSignalInterpolator() : SignalInterpolator(1)
{
}

float AuxPort::LinearSignalInterpolator::interpolate(float currSample)
{
	float y0 = circularBuffer.getShiftedElement(-1);
	circularBuffer.push(currSample);
	return Interpolation::linearInterpolate(0, y0, 1, currSample, 0.5);
}

AuxPort::CubicSignalInterpolator::CubicSignalInterpolator() : SignalInterpolator(2)
{}

float AuxPort::CubicSignalInterpolator::interpolate(float currSample, float nextSample)
{
	float y1 = circularBuffer.getShiftedElement(-1);
	float y0 = circularBuffer.getShiftedElement(-2);
	circularBuffer.push(currSample);
	return Interpolation::cubicInterpolate({ 0, 1, 2, 3 }, {y0, y1, currSample, nextSample}, 1.5);
}

AuxPort::CosineSignalInterpolator::CosineSignalInterpolator() : SignalInterpolator(1)
{
}

float AuxPort::CosineSignalInterpolator::interpolate(float currSample)
{
	float y0 = circularBuffer.getShiftedElement(-1);
	circularBuffer.push(currSample);
	return Interpolation::cosineInterpolate(0, y0, 1, currSample, 0.5);
}

AuxPort::LagrangeSignalInterpolator::LagrangeSignalInterpolator() : SignalInterpolator(15)
{
}

AuxPort::LagrangeSignalInterpolator::LagrangeSignalInterpolator(size_t bufferSize) : SignalInterpolator(bufferSize)
{
}

float AuxPort::LagrangeSignalInterpolator::interpolate(float currSample)
{
	std::vector<float> xValues;
	std::vector<float> yValues;
	generateXYVectors(xValues, yValues, currSample);
	return Interpolation::lagrangeInterpolate(xValues, yValues, static_cast<float>(bufferSize) - 0.5f);
}

AuxPort::NewtonSignalInterpolator::NewtonSignalInterpolator() : SignalInterpolator(15)
{
}

AuxPort::NewtonSignalInterpolator::NewtonSignalInterpolator(size_t bufferSize) : SignalInterpolator(bufferSize)
{
}

float AuxPort::NewtonSignalInterpolator::interpolate(float currSample)
{
	std::vector<float> xValues;
	std::vector<float> yValues;
	generateXYVectors(xValues, yValues, currSample);
	return Interpolation::newtonInterpolate(xValues, yValues, static_cast<float>(bufferSize) - 0.5f);
}
