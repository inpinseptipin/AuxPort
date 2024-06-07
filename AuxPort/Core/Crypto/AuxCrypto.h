#ifndef AUXPORT_CRYPTO_H
#define AUXPORT_CRYPTO_H
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
#include <string>
#include <iomanip>
#include <sstream>

namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief Provides interface to calculate MD5 hash of a string
	///////////////////////////////////////////////////////////////////////////////////////
	class MD5
	{
	public:
		MD5() = default;
		~MD5() = default;
		MD5(const MD5& md5) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Returns MD5 hash of the given string string
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string hash(const std::string& data);
	private:
		///////////////////////////////////////////////////////////////////////////////////////
		/// s specifies the amount of shift per round
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32_t S[64];
		static uint32_t K[64];

		///////////////////////////////////////////////////////////////////////////////////////
		/// Functions for MD5
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32_t F(uint32_t x, uint32_t y, uint32_t z);
		static uint32_t G(uint32_t x, uint32_t y, uint32_t z);
		static uint32_t H(uint32_t x, uint32_t y, uint32_t z);
		static uint32_t I(uint32_t x, uint32_t y, uint32_t z);
		
		///////////////////////////////////////////////////////////////////////////////////////
		/// Shifts the bits to the left in a circular manner
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32_t rotateLeft(uint32_t x, uint32_t n);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns a copy of data with padding as specified in MD5 Algorithm
		///////////////////////////////////////////////////////////////////////////////////////
		static std::vector<uint8_t> getPaddedData(const std::string& data);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Main MD5 Algorithm which processes paddedData in blocks of 512 bytes
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string computeHash(const std::vector<uint8_t>& paddedData);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns the given number in the hexadecimal form as a string
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string getHexString(uint32_t num);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Returns a 32-byte word from the paddedData bytes. This function forms a word out of
		/// each set of 4 paddedData Bytes. The word comprises of the bytes in Little Endian format.
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32_t getWord(const std::vector<uint8_t>& paddedData, size_t wordIndex);

		///////////////////////////////////////////////////////////////////////////////////////
		/// Converts the given 32-bit number to Big Endian format. 
		///////////////////////////////////////////////////////////////////////////////////////
		static uint32_t convertToBigEndian(uint32_t num);
	};
}
#endif
