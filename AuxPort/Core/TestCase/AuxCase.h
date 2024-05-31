#ifndef AUXPORT_CASE_H
#define AUXPORT_CASE_H
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
#include <functional>
#include "../Env/AuxEnv.h"
#include "../Log/AuxLog.h"

namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////
	///	@brief Represents a Test Case
	///////////////////////////////////////////////////////////////////////////////////////
	class Case : public ILog
	{
	public:
		Case() = default;
		~Case() = default;
		Case(const Case& testcase) = default;

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Sets the ID for Test Case
		///////////////////////////////////////////////////////////////////////////////////////
		void setTestID(const std::string& testID);

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Sets testcase name
		///////////////////////////////////////////////////////////////////////////////////////
		void setTestName(const std::string& testName);

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Lambda Function that will be called to run the Test Case.
		/// 
		/// Takes some commands as paramater, which can be used to provide some parameters to
		/// the module being tested.
		/// @returns Returns true if test succeeds, otherwise returns false
		///////////////////////////////////////////////////////////////////////////////////////
		std::function<bool(const std::vector<std::string>& commands)> testCase = 0;

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns the Test Case ID
		///////////////////////////////////////////////////////////////////////////////////////
		std::string& getTestID();

		///////////////////////////////////////////////////////////////////////////////////////
		///	@brief Returns the Test Case Name
		///////////////////////////////////////////////////////////////////////////////////////
		std::string& getTestName();

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Logs the details of the Test Case
		///////////////////////////////////////////////////////////////////////////////////////
		void Log() override;
	private:
		std::string testID;
		std::string testName;
	};
}
#endif

