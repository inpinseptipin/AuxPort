#ifndef AUXPORT_PASCAL_H
#define AUXPORT_PASCAL_H
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

namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provide an interface to compute and manage a Pascal Triangle
	///////////////////////////////////////////////////////////////////////////////////////
	class AuxPascal : virtual private AuxPort::TextFile, private AuxPort::TextFormat
	{
	public:
		AuxPascal();
		~AuxPascal() = default;
		AuxPascal(const AuxPascal& obj) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Type is an enumerator that specifies the type of Pascal Triangle: Positive or Negative
		///////////////////////////////////////////////////////////////////////////////////////
		enum Type { Positive, Negative };

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Computes N'th rows of the pascal triangle and returns a 2-D vector of floats.
		/// @param N Number of rows to be computed in the pascal triangle
		/// @param type Type of Pascal Triangle (Positive or Negative)
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::vector<float>> computePascalTriangle(uint32 N, const Type& type = Type::Positive);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Logs the computed Pascal Triangle
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Writes the computed Pascal Triangle into a textfile
		///////////////////////////////////////////////////////////////////////////////////////
		void writeToFile(const std::string& fileName);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Reads and loads coefficients of pascal triangle from a textfile
		///////////////////////////////////////////////////////////////////////////////////////
		void readFromFile(const std::string& fileName);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Logs the info of last file that was read/written
		///////////////////////////////////////////////////////////////////////////////////////
		void logFileInfo();

	private:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief A two-dimensional vector of floats which is used to store Pascal Triangle
		///////////////////////////////////////////////////////////////////////////////////////
		std::vector<std::vector<float>> pascalTriangle;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief It specifies the current type of Pascal Triangle
		///////////////////////////////////////////////////////////////////////////////////////
		Type type;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Dummy function for inheriting TextFormat class
		///////////////////////////////////////////////////////////////////////////////////////
		void read(std::string& line, int props = 0) override;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Dummy function for inheriting TextFormat class
		///////////////////////////////////////////////////////////////////////////////////////
		void write(const std::string& line, int props = 0) override;
	};
}

#endif
