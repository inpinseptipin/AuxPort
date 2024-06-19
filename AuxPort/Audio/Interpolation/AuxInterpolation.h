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
	class Interpolator
	{
	public:
		Interpolator(size_t bufferSize);
		Interpolator(const Interpolator& obj) = default;
		~Interpolator() = default;

		virtual float interpolate(float currSample) = 0;
	protected:
		size_t bufferSize;
		AuxPort::CircularBuffer<float> circularBuffer;

		void generateXYVectors(std::vector<float>& xValues, std::vector<float>& yValues, float currSample);
		static float linearInterpolate(float x0, float y0, float x1, float y1, float x);
		static float cubicInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x);
		static float cosineInterpolate(float x0, float y0, float x1, float y1, float x);
		static float lagrangeInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x);
		static float newtonInterpolate(const std::vector<float>& xValues, const std::vector<float>& yValues, float x);
	};

	class LinearInterpolator : public Interpolator
	{
	public:
		LinearInterpolator();
		LinearInterpolator(const LinearInterpolator& obj) = default;
		~LinearInterpolator() = default;

		float interpolate(float currSample);
	};

	class CubicInterpolator : public Interpolator
	{
	public:
		CubicInterpolator();
		CubicInterpolator(const CubicInterpolator& obj) = default;
		~CubicInterpolator() = default;

		float interpolate(float currSample);
	private:
	};

	class CosineInterpolator : public Interpolator
	{
	public:
		CosineInterpolator();
		CosineInterpolator(const CosineInterpolator& obj) = default;
		~CosineInterpolator() = default;

		float interpolate(float currSample);
	};

	class LagrangeInterpolator : public Interpolator
	{
	public:
		 LagrangeInterpolator();
		 LagrangeInterpolator(size_t bufferSize);
		 LagrangeInterpolator(const LagrangeInterpolator& obj) = default;
		 ~LagrangeInterpolator() = default;

		float interpolate(float currSample);
	};

	class NewtonInterpolator : public Interpolator
	{
	public:
		NewtonInterpolator();
		NewtonInterpolator(size_t bufferSize);
		NewtonInterpolator(const NewtonInterpolator& obj) = default;
		~NewtonInterpolator() = default;

		float interpolate(float currSample);
	};
}
#endif