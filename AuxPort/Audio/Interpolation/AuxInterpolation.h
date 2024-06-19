#ifndef AUXPORT_INTERPOLATION_H
#define AUXPORT_INTERPOLATION_H
/*
*			AuxPort Library
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

/*===================================================================================*/
#include <vector>
#include <complex>
#include <cmath>
#include "../../Core/Utility/AuxUtility.h"
#include "../../Core/Utility//AuxCircularBuffer.h"

namespace AuxPort
{
	class Interpolation
	{
	public:
		enum class Type { Linear, Cubic, Cosine, Lagrange, Newton };
		Interpolation();
		~Interpolation() = default;
		Interpolation(const Interpolation& interpolation) = default;
		void setType(Type type);
		void setXValues(float start, float end, float delta);
		void setXValues(const std::vector<float> xValues);
		void setYValues(const std::vector<float> yValues);
		float interpolate(float val);

		static float linearInterpolate(float x0, float y0, float x1, float y1, float x);
		static float cubicInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x);
		static float cosineInterpolate(float x0, float y0, float x1, float y1, float x);
		static float lagrangeInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x);
		static float newtonInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x);
	private:
		Type type;
		size_t valuesCount;
		std::vector<float> xValues;
		std::vector<float> yValues;

		float _interpolateLinear(float val);
		float _interpolateCubic(float val);
		float _interpolateCosine(float val);
		float _interpolateLagrange(float val);
		float _interpolateNewton(float val);
		size_t _findIndex(float xVal);
	};

	class SignalInterpolator
	{
	public:
		SignalInterpolator(size_t bufferSize);
		SignalInterpolator(const SignalInterpolator& obj) = default;
		~SignalInterpolator() = default;

		virtual float interpolate(float currSample) = 0;
	protected:
		AuxPort::CircularBuffer<float> circularBuffer;
		size_t bufferSize;
		void generateXYVectors(std::vector<float>& xValues, std::vector<float>& yValues, float currSample);
	};

	class LinearSignalInterpolator : public SignalInterpolator
	{
	public:
		LinearSignalInterpolator();
		LinearSignalInterpolator(const LinearSignalInterpolator& obj) = default;
		~LinearSignalInterpolator() = default;

		float interpolate(float currSample);
	};

	class CubicSignalInterpolator : public SignalInterpolator
	{
	public:
		CubicSignalInterpolator();
		CubicSignalInterpolator(const CubicSignalInterpolator& obj) = default;
		~CubicSignalInterpolator() = default;

		float interpolate(float currSample, float nextSample);
	private:
		float interpolate(float currSample) = 0;
	};

	class CosineSignalInterpolator : public SignalInterpolator
	{
	public:
		CosineSignalInterpolator();
		CosineSignalInterpolator(const CosineSignalInterpolator& obj) = default;
		~CosineSignalInterpolator() = default;

		float interpolate(float currSample);
	};

	class LagrangeSignalInterpolator : public SignalInterpolator
	{
	public:
		 LagrangeSignalInterpolator();
		 LagrangeSignalInterpolator(size_t bufferSize);
		 LagrangeSignalInterpolator(const LagrangeSignalInterpolator& obj) = default;
		 ~LagrangeSignalInterpolator() = default;

		float interpolate(float currSample);
	};

	class NewtonSignalInterpolator : public SignalInterpolator
	{
	public:
		NewtonSignalInterpolator();
		NewtonSignalInterpolator(size_t bufferSize);
		NewtonSignalInterpolator(const NewtonSignalInterpolator& obj) = default;
		~NewtonSignalInterpolator() = default;

		float interpolate(float currSample);
	};
}
#endif