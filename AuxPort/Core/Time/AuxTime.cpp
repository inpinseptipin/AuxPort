
/*
*			AuxPort Library
			"Modules for Audio Software Development" - inpinseptipin

			BSD 3-Clause License

			Copyright (c) 2025, Satyarth Arora
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
#include "AuxTime.h"
#include "../../Core/Utility/AuxCaster.h"
namespace AuxPort
{
	Timer::Timer()
	{
		type = nano;
		ellapsedTime = 0LL;
		isRunning = false;
	}

	void Timer::start()
	{
		startTime = std::chrono::high_resolution_clock::now();
		isRunning = true;
	}

	void Timer::stop()
	{
		endTime = std::chrono::high_resolution_clock::now();
		isRunning = false;
		ellapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	}

	void Timer::show(const Type& type)
	{
		this->type = type;
		switch (type)
		{
			case Type::nano:ellapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count(); displayString = " ns";
				break;
			case Type::milli:ellapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count(); displayString = " ms";
				break;
			case Type::micro:ellapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count(); displayString = " us";
				break;
			case Type::seconds:ellapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count(); displayString = " s";
		}		
		AuxPort::Logger::Log(AuxPort::Casters::toStdString(ellapsedTime) + displayString);
	}

	bool Timer::stillRunning()
	{
		return isRunning != 0;
	}

	long long  Timer::getEllapsedTime(const Type& type)
	{
		this->type = type;
		switch (type)
		{
		case Type::nano:ellapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count(); displayString = " ns";
			break;
		case Type::milli:ellapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count(); displayString = " ms";
			break;
		case Type::micro:ellapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count(); displayString = " us";
			break;
		case Type::seconds:ellapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count(); displayString = " s";
		}
		return ellapsedTime;
	}

	

	

}
