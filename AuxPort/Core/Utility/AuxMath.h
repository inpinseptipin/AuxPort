#ifndef AUXPORT_MATH_H
#define AUXPORT_MATH_H
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
#include "../Env/AuxEnv.h"

namespace AuxPort
{
	template<class errorVal>
	class Error
	{
	public:
		enum class Type { MEAN, Absolute, RMSE };
		
		Error()
		{
			this->type = Type::Absolute;
		}

		~Error() = default;
		
		Error(const Error& error) = default;
		
		void setType(const Type& type)
		{
			this->type = type;
		}

		float compute(const std::vector<errorVal>& vec1, const std::vector<errorVal>& vec2)
		{
			AuxAssert(vec1.size() != vec2.size(), "Vectors must be of same size!");

			float result = 0.0f;
			size_t n = vec1.size();

			switch (type) 
			{
			case Mean:
				for (size_t i = 0; i < n; i++) 
				{
					result += (vec1[i] - vec2[i]);
				}
				result /= n;
				break;
			case Absolute:
				for (size_t i = 0; i < n; i++)
				{
					result += std::abs(vec1[i] - vec2[i]);
				}
				result /= n;
				break;

			case RMSE:
				for (size_t i = 0; i < n; i++) 
				{
					result += std::norm((vec1[i] - vec2[i]));
				}
				result = std::sqrt((float)result / n);
				break;
			}
			return result;
		}
	private:
		Type type;
	};

	class Interpolation
	{
	public:
		enum class Type { Linear, Cubic, Lagrange };
		Interpolation();
		~Interpolation() = default;
		Interpolation(const Interpolation& interpolation) = default;
		void setType(Type type);
		void setXValues(float start, float end, float delta);
		void setYValues(const std::vector<float> yValues);
		float polate(float val);
	private:
		Type type;
		float delta;
		float startX, endX;
		size_t valuesCount;
		std::vector<float> yValues;

		float linearInterpolate(float val);
		float cubicInterpolate(float val);
		float lagrangeInterpolate(float val);
		size_t findIndex(float xVal);
	};
}

#endif