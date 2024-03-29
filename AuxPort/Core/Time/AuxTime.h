#ifndef AUXPORT_TIME_H
#define AUXPORT_TIME_H
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

#include<ctime>
#include<string>
#include<sstream>
#include <chrono>
#include "../Log/AuxLog.h"

///////////////////////////////////////////////////////////////////////////////////////
/// This is a wrapper over the C Time Library, It is used to get Date and Time formatted onto std::string
/// The wrapper provides you with an interface that can be called.
/// 
/// Eg: AuxPort::Time::getCurrentTime(TimeType::Time)
///////////////////////////////////////////////////////////////////////////////////////

namespace AuxPort
{

	///////////////////////////////////////////////////////////////////////////////////////
	/// [Class] Simple Timer used for Benchmarking DSP Algorithms
	///////////////////////////////////////////////////////////////////////////////////////
	class Timer
	{
	public:
		enum Type
		{
			nano, milli, micro, seconds
		};
		Timer();
		~Timer() = default;
		Timer(const Timer& timer) = default;
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Use this function to Start the timer
		///////////////////////////////////////////////////////////////////////////////////////
		void start();
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Use this function to Stop the timer
		///////////////////////////////////////////////////////////////////////////////////////
		void stop();
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Logs the Time Ellapsed onto the console
		///////////////////////////////////////////////////////////////////////////////////////
		void show(const Type& type = Type::micro);
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Determines whether a timer is still Running
		///////////////////////////////////////////////////////////////////////////////////////
		bool stillRunning();
		///////////////////////////////////////////////////////////////////////////////////////
		/// [Function] Returns the ellapsed time
		///////////////////////////////////////////////////////////////////////////////////////
		long long getEllapsedTime(const Type& type = Type::micro);
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
		long long ellapsedTime;
		bool isRunning;
		Type type;
		std::string displayString;
	};

}
#endif