#ifndef AUXPORT_THREAD_H
#define AUXPORT_THREAD_H
#include "../Env/AuxEnv.h"
#include <functional>
#include <thread>
#include <mutex>
#include "../Log/AuxLog.h"
namespace AuxPort
{
	/**
		Abstract Class for Multithreading
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
		void quit();
		std::function<void()> work;
	};

	class TimerWithCallback : public Thread
	{
	public:
		TimerWithCallback();
		~TimerWithCallback();
		TimerWithCallback(const TimerWithCallback& timerWithCallback) = default;
		void startTimer(uint32_t millisecond);
		void stopTimer();
		virtual void timerCallback() = 0;
	protected:
		uint32_t millisecond = 0;
	};

}

#endif
