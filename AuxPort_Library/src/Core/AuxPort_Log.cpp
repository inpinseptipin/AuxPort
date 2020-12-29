
/*
*			AuxPort Library
			"Generic Modules to facilitate C++ Windows Application development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2020, Satyarth Arora
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
#pragma once

#include "../../include/Core/AuxPort_Log.h"

namespace AuxPort
{

	void Logger::Success(const std::string& message,const TimeType& timeType)
	{
		setColour(ColourType::Green);
		logMessage(message, LogType::Success,timeType);
		setColour(ColourType::White);
	}

	void Logger::Warning(const std::string& message,const TimeType& timeType)
	{
		setColour(ColourType::Yellow);
		logMessage(message, LogType::Warning,timeType);
		setColour(ColourType::White);
	}

	void Logger::Information(const std::string& message,const TimeType& timeType)
	{
		setColour(ColourType::Cyan);
		logMessage(message, LogType::Info,timeType);
		setColour(ColourType::White);
	}

	void Logger::Error(const std::string& message,const TimeType& timeType)
	{
		setColour(ColourType::Red);
		logMessage(message, LogType::Error,timeType);
		setColour(ColourType::White);
	}
	void Logger::Log(const std::string& message, const LogType& logType=LogType::Info, const ColourType& colourType=ColourType::White, const TimeType& timeType=TimeType::Raw)
	{
		setColour(colourType);
		logMessage(message, logType,timeType);
		setColour(ColourType::White);
	}

	void Logger::setColour(const ColourType& colourType)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (unsigned int)colourType);
	}

	void Logger::logMessage(const std::string& message,const LogType& logType,const TimeType& timeType)
	{
		std::string m_message = getMessageFormat(logType);
		std::cout <<Time::getCurrentTime(timeType)<<"\n"<< m_message << message << "\n\n";
	}

	std::string Logger::getMessageFormat(const LogType& logType)
	{
		unsigned char m_logType = (unsigned char)logType;
		switch (m_logType)
		{
		case '1': return "[Success] : ";
			break;
		case '2': return "[Warning] : ";
			break;
		case '3': return "[Info] : ";
			break;
		case '4': return "[Error] : ";
			break;
		default: return "[Log] : ";
		}
	}

}