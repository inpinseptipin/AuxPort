
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
#include "AuxLog.h"
#include <chrono>
namespace AuxPort
{
	std::string Time::getCurrentTime(const TimeType& timeType)
	{
		const std::time_t currentTime_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char timeBuffer[26];
		ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime_t);
		auto currentTime =  std::string(timeBuffer);
		switch (timeType)
		{
		case TimeType::Day:
			return "Day : " + currentTime.substr(0, 3);
			break;
		case TimeType::Date:
			return "Date : " + currentTime.substr(4, 6);
			break;
		case TimeType::time:
			return "Time : " + currentTime.substr(11, 8);
			break;
		case TimeType::Year:
			return "Year : " + currentTime.substr(20, 4);
			break;
		case TimeType::Raw:
			return currentTime.substr(0, 24);
			break;
		}
		return currentTime;
	}



	void Logger::setColour(const ColourType& colourType)
	{
#ifdef AUXPORT_WINDOWS
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)colourType);
#elif defined(AUXPORT_LINUX) || defined(AUXPORT_MAC)
		std::cout << "\033[" << (unsigned int) colourType << "m";
#endif
	}

	std::string Logger::getMessageFormat(const LogType& logType)
	{
		unsigned char m_logType = (unsigned char)logType;
		switch (m_logType)
		{
		case '1': return "[Success]";
			break;
		case '2': return "[Warning]";
			break;
		case '3': return "[Information]";
			break;
		case '4': return "[Error]";
			break;
		default: return "[Log]";
		}
	}

	void ILog::setColour(const ColourType& colourType)
	{
#ifdef AUXPORT_WINDOWS
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)colourType);
#elif defined(AUXPORT_LINUX) || defined(AUXPORT_MAC)
		std::cout << "\033[" << (unsigned int) colourType << "m";
#endif
	}

	void ILog::Log()
	{
		std::cout << "" << std::endl;
	}

}