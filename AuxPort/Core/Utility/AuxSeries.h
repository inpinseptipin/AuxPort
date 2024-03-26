#ifndef AUXPORT_SERIES_H
#define AUXPORT_SERIES_H
/*
			AuxPort Library
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
#include "../Env/AuxEnv.h"
#include "../File/AuxFile.h"
#include "../SIMD/AuxSimd.h"

namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	/// PolynomialTerm is a struct that represents a polynomial's exponent and its coefficient.
	/// For Example :
	///
	/// PolynomialTerm term = {3,2}
	/// then this represent a polynomial
	///	y = 2x^3
	///////////////////////////////////////////////////////////////////////////////////////
	struct PolynomialTerm
	{
		float exponent, coefficient;
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// Class : AuxSeries
	/// This class can be used to express continuous mathematical functions as an infinite series of polynomial terms.
	///////////////////////////////////////////////////////////////////////////////////////
	class AuxSeries : virtual protected AuxPort::TextFile, protected AuxPort::TextFormat
	{
	public:

		AuxSeries();
		~AuxSeries() = default;
		AuxSeries(const AuxSeries& obj) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Type is used to specify the mathematical function, the class should compute the series for.
		///////////////////////////////////////////////////////////////////////////////////////
		enum Type { Sin, Cos, Sinh, Cosh, Tanh, ArcTan, E, NaturalLog, Undefined };

		///////////////////////////////////////////////////////////////////////////////////////
		/// Computes the Taylor Series terms and returns a vector of those terms
		/// Parameters:
		/// N - Number of terms to compute
		/// type - Type of function for which we need to compute Taylor Teries terms
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<PolynomialTerm>& getTerms(uint32 N, const Type& type = Type::Sin);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Computes Taylor Series terms and stores them in a vector internally
		/// Parameters:
		/// N - Number of terms to compute
		/// type - Type of function for which we need to compute Taylor Teries terms
		///////////////////////////////////////////////////////////////////////////////////////
		void computeTerms(uint32 N, const Type& type = Type::Sin);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Logs the Taylor Series terms that are present in the internal terms vector.
		/// The terms are logged in the following form :
		/// f(x) = c1*x^e1 + c2*x^e2 + .........
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Logs information about AuxSeries File which was last opened for read/write operation
		///////////////////////////////////////////////////////////////////////////////////////
		void logFileInfo();

		///////////////////////////////////////////////////////////////////////////////////////
		/// Writes a computed series into a file.
		///////////////////////////////////////////////////////////////////////////////////////
		void writeSeriesToFile(const std::string& fileName);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Reads the Taylor Series terms from a file and loads them into the internal terms vector
		///////////////////////////////////////////////////////////////////////////////////////
		void readSeriesFromFile(const std::string& fileName);

	protected:
		///////////////////////////////////////////////////////////////////////////////////////
		/// Converts the internal enum into a string
		///////////////////////////////////////////////////////////////////////////////////////
		std::string getTypeAsString();

		///////////////////////////////////////////////////////////////////////////////////////
		/// A vector which is used to store the computed terms
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<AuxPort::PolynomialTerm> terms;

		///////////////////////////////////////////////////////////////////////////////////////
		/// It specifies the type of function whose Taylor Series terms are currently stored in internal terms vector
		///////////////////////////////////////////////////////////////////////////////////////
		Type type;

		///////////////////////////////////////////////////////////////////////////////////////
		/// This string denoted the type of Taylor Series if it is something other than the defined types
		///////////////////////////////////////////////////////////////////////////////////////
		std::string undefinedType;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Dummy function for inheriting TextFormat class
		///////////////////////////////////////////////////////////////////////////////////////
		void read(std::string& line, int props = 0) override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Dummy function for inheriting TextFormat class
		///////////////////////////////////////////////////////////////////////////////////////
		void write(const std::string& line, int props = 0) override;
	};


	///////////////////////////////////////////////////////////////////////////////////////
	/// Class that evaluates a function at a given x-value using the taylor series approximation.
	/// Example usage:
	/// AuxPort::AuxSeriesEngine series;
	/// series.computeTerms(5, AuxPort::AuxSeriesEngine::Type::Sin);
	/// series.computeFunction(0.23f);
	///////////////////////////////////////////////////////////////////////////////////////
	class AuxSeriesEngine : public AuxSeries
	{
	public:
		AuxSeriesEngine() = default;
		~AuxSeriesEngine() = default;
		AuxSeriesEngine(const AuxSeriesEngine& obj) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// Evaluates a taylor series approximation of the chosen function at a given x-value.
		///////////////////////////////////////////////////////////////////////////////////////
		float computeFunction(float x);

	private:
		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns a vector containing the coefficients(including zeros) of the terms
		/// For Example: 
		/// For the following polynomial -> 5x^6 + 2x^2 + 3
		/// The returned vector will contain {3, 0, 2, 0, 0, 0, 5}
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<float> extractConsecutiveCoefficients();

		///////////////////////////////////////////////////////////////////////////////////////
		/// Fills up first given vector with even-index coefficients and other given vector with
		/// odd-indexed ones. Used for employing Estrin's algorithm
		///////////////////////////////////////////////////////////////////////////////////////
		void getEvenOddCoefficients(std::vector<float>& evenIndexCoefficients, std::vector<float>& oddIndexCoefficients);
	};
}
#endif