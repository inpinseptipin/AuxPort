#ifndef AUXPORT_THREAD_H
#define AUXPORT_THREAD_H
#include "../Env/AuxEnv.h"
#include <functional>
#include <thread>
#include <mutex>
#include <queue>
#include "../Log/AuxLog.h"
#include "../Utility/AuxUtility.h"

#if AUXPORT_WINDOWS
#include <Windows.h>
#include <tchar.h>
#endif
namespace AuxPort
{
	/**
		Abstract Class for Threads
	*/
	class Thread
	{
	public:
		Thread();
		~Thread();
		Thread(const Thread& thread) = default;
	protected:
		std::unique_ptr<std::thread> thread;
		bool threadLoopBool;
		std::mutex threadMutex;
	};

	class ParallelThread : public Thread
	{
	public:
		ParallelThread();
		~ParallelThread();
		ParallelThread(const ParallelThread& parallelThread) = default;
		/**
		  @brief Joins the thread with the main application thread and terminates it 
		  \code{.cpp}
		  
		  \endcode 
		 */
		void quit();
		/**
			Assign this function pointer with another function to perform a stask that should be done by this thread.
		 */
		std::function<void()> work;
	};

	class TimerWithCallback : public Thread
	{
	public:
		TimerWithCallback();
		~TimerWithCallback();
		TimerWithCallback(const TimerWithCallback& timerWithCallback) = default;
		/**
		  @brief Sets the timer in milliseconds 
		  @param millisecond
		  \code{.cpp}
		  
		  \endcode 
		 */
		void startTimer(uint32_t millisecond);
		/**
		  @brief Stops the Timer 
		  \code{.cpp}
		  
		  \endcode 
		 */
		void stopTimer();
		/**
		  @brief Redefine this callback with the work to be done. 
		  \code{.cpp}
		  
		  \endcode 
		 */
		virtual void timerCallback() = 0;
	protected:
		uint32_t millisecond = 0;
	};


	class ProcessQueue : public ParallelThread
	{
	public:
		ProcessQueue();
		~ProcessQueue() = default;
		/**
		  @brief Use this function to add a process command to the queue for execution 
		  @param processQueue
		  \code{.cpp}
		  
		  \endcode 
		 */
		void addProcess(const std::string& processQueue);
	protected:
		std::mutex processMutex;
		std::queue<std::string> processQueue;
#if AUXPORT_WINDOWS
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		bool workDispatched;
#endif
	};

}

#endif
