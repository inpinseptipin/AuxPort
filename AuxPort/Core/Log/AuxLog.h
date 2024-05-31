#ifndef AUXPORT_LOG_H
#define AUXPORT_LOG_H
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

#include<string>
#include<iostream>
#include<cstdlib>
#include<vector>
#include "../Time/AuxTime.h"
#include "../Env/AuxEnv.h"
#ifdef AUXPORT_WINDOWS
#include<Windows.h>
#endif
namespace AuxPort
{
	///////////////////////////////////////////////////////////////////////////////////////            
	/// @brief Provides functionality to get current system time
	///////////////////////////////////////////////////////////////////////////////////////            
	class Time
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////            
		/// @brief TimeType is a type that can be used to set Formatting rules for the values returned by getCurrentTime() function
		///////////////////////////////////////////////////////////////////////////////////////            
		enum TimeType
		{
			Day = 0x31,
			Date = 0x32,
			time = 0x33,
			Year = 0x34,
			Raw = 0x35
		};

		///////////////////////////////////////////////////////////////////////////////////////  
		/// @brief This function is used to get current system time and returns the time typecasted into std::string.
		/// @param timeType TimeType is a type that can be used to set Formatting rules for the values returned by getCurrentTime() function
		///////////////////////////////////////////////////////////////////////////////////////  
		static std::string getCurrentTime(const TimeType& timeType);
	};

	///////////////////////////////////////////////////////////////////////////////////////  
	///	@brief LogType is an enumerator that allows you to choose between different Logging Directives.
	///////////////////////////////////////////////////////////////////////////////////////  
	enum class LogType
	{
		Success = 0x31,
		Warning = 0x32,
		Info = 0x33,
		Error = 0x34
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @cond  
	///				Colour Codes for Windows
	///		1	0x0001	Blue	|	9	0x0009	Light Blue
	/// 	2	0x0002	Green	|	0	0x0000	Black
	/// 	3	0x0003	Cyan	|	A	0x000A	Light Green
	/// 	4	0x0004	Red		|	B	0x000B	Light Aqua
	/// 	5	0x0005	Purple	|	C	0x000C	Light Red
	/// 	6	0x0006	Yellow	|	D	0x000D	Light Purple
	/// 	7	0x0007	White	|	E	0x000E	Light Yellow
	/// 	8	0x0008	Gray	|	F	0x000F	Bright White
	/// @endcond
	///////////////////////////////////////////////////////////////////////////////////////  

	///////////////////////////////////////////////////////////////////////////////////////  
	///	@brief Use this to select text colour for Logging.
	///////////////////////////////////////////////////////////////////////////////////////  
	enum class ColourType  
	{
#ifdef AUXPORT_WINDOWS
		Black = 0x0000,
		Blue = 0x0001,
		Green = 0x002,
		Cyan = 0x003,
		Red = 0x004,
		Purple = 0x005,
		Yellow = 0x006,
		White = 0x007,
		Gray = 0x008,
		Light_Blue = 0x009,
		Light_Green = 0x00A,
		Light_Aqua = 0x00B,
		Light_Red = 0x000C,
		Light_Purple = 0x00D,
		Light_Yellow = 0x00E,
		Bright_White = 0x00F
#elif defined(AUXPORT_LINUX) || defined(AUXPORT_MAC)
		Black = 0x01E,
		Red = 0x01F,
		Green = 0x020,
		Yellow = 0x021,
		Blue = 0x022,
		Purple = 0x023,
		Cyan = 0x024,
		Bright_White = 0x025,
		Gray = 0x05A,
		Light_Red = 0x05B,
		Light_Green = 0x05C,
		Light_Yellow = 0x05D,
		Light_Blue = 0x05E,
		Light_Purple = 0x05F,
		Light_Aqua = 0x060,
		White = 0x061
#endif
	};

	///////////////////////////////////////////////////////////////////////////////////////  
	/// @brief This class provides static interfaces to allow the end user to log their messages on the console.
	/// 
	/// @details It also consists of Logging directives such as Info, Warning, Error, Success which are implemented in
	/// the form of interfaces.
	/// 
	/// Example:
	/// @code AuxPort::Logger::Log("message"); @endcode
	///////////////////////////////////////////////////////////////////////////////////////   
	///////////////////////////////////////////////////////////////////////////////////////  
	class Logger
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////  
		/// @brief Log is a function that allows you to log "string" messages on the console.
		/// @param message Message to be logged
		/// @param logType This tells the function to which type of message is to be logged on the console. (Eg: Error, Warning, Success, Info)
		/// @param colourType Allows you to choose the colour of your logged message
		/// @param timeType Allows you to choose between different date or time stamps for the logged messages.
		///////////////////////////////////////////////////////////////////////////////////////  
		template<class T>
		static void Log(const T& message, const LogType& logType = LogType::Info, const ColourType& colourType = ColourType::White,const AuxPort::Time::TimeType& timeType = AuxPort::Time::TimeType::time)
		{
			setColour(colourType);
			logMessage(message, logType,timeType);
			setColour(ColourType::White);
		}
		
		///////////////////////////////////////////////////////////////////////////////////////  
		/// @brief Log is a function that allows you to log "string" messages on the console.
		/// @param messages Messages to be logged
		/// @param logType This tells the function to which type of message is to be logged on the console. (Eg: Error, Warning, Success, Info)
		/// @param colourType Allows you to choose the colour of your logged message
		/// @param timeType Allows you to choose between different date or time stamps for the logged messages.
		///////////////////////////////////////////////////////////////////////////////////////
		template<class T>
		static void Log(const std::vector<T>& messages, const LogType& logType = LogType::Info, const ColourType& colourType = ColourType::White, const AuxPort::Time::TimeType& timeType = AuxPort::Time::TimeType::time)
		{
			setColour(colourType);
			for (int i = 0; i < messages.size(); i++)
			{
				logMessage(messages[i], logType, timeType);
			}
			setColour(ColourType::White);
		}
	
	private:

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function allows you to set text colour for the text to be printed onto the console.
		/// @param colourType Allows you to choose the colour of your logged message
		///////////////////////////////////////////////////////////////////////////////////////
		static void setColour(const ColourType& colourType);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This Function logs the messages onto the console, can only be called through public interfaces provided by the Class.
		/// @param message Message to be logged
		/// @param logType This tells the function to which type of message is to be logged on the console. (Eg: Error, Warning, Success, Info)
		/// @param timeType Allows you to choose between different date or time stamps for the logged messages.
		///////////////////////////////////////////////////////////////////////////////////////
		template<class T>
		static void logMessage(const T& message,const LogType& logType,const AuxPort::Time::TimeType& timeType)
		{
			std::cout << getMessageFormat(logType) <<" | "<<Time::getCurrentTime(timeType) << " | " << message << "\n";
		}

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Gets preformatted messages for the corrossponding log type.
		/// @param logType This tells the function to which type of message is to be logged on the console. (Eg: Error, Warning, Success, Info)
		///////////////////////////////////////////////////////////////////////////////////////
		static std::string getMessageFormat(const LogType& logType);
	};

	///////////////////////////////////////////////////////////////////////////////////////
	/// @brief This class provides an inheritable interface to implement logging functionality in the derived classes
	///////////////////////////////////////////////////////////////////////////////////////
	class ILog
	{
	protected:
		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief This function allows you to set text colour for the text to be printed onto the console.
		/// @param colourType Allows you to choose the colour of your logged message
		///////////////////////////////////////////////////////////////////////////////////////
		void setColour(const ColourType& colourType);

		///////////////////////////////////////////////////////////////////////////////////////
		/// @brief Implement this method in the derived class to specify logging behaviour
		///////////////////////////////////////////////////////////////////////////////////////
		virtual void Log();
	};
}
#endif