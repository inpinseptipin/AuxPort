#include "AuxThread.h"

AuxPort::ParallelThread::ParallelThread()
{
	thread.reset(new std::thread([this] {
		while (threadLoopBool)
		{
			if (work != nullptr)
				work();
		}
		}));
}

AuxPort::ParallelThread::~ParallelThread()
{
	if (threadLoopBool == true)
	{
		std::lock_guard lockGuard(threadMutex);
		threadLoopBool = false;
		thread->join();
	}
}

void AuxPort::ParallelThread::quit()
{
	threadLoopBool = false;
	if (thread->joinable())
		thread->join();
}

AuxPort::Thread::Thread()
{
	threadLoopBool = true;
}

AuxPort::Thread::~Thread()
{
	if(thread->joinable())
		thread->join();
}


AuxPort::TimerWithCallback::TimerWithCallback()
{
	millisecond = 0;
	thread.reset(new std::thread([this] {
		while (threadLoopBool)
		{
			if (this->millisecond >= 1)
			{
				timerCallback();
				auto futureTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(millisecond);
				std::this_thread::sleep_until(futureTime);
			}
		}
		}));
}

AuxPort::TimerWithCallback::~TimerWithCallback()
{
	std::lock_guard lockGuard(threadMutex);
	threadLoopBool = false;
	if(thread->joinable())
		thread->join();
}

void AuxPort::TimerWithCallback::startTimer(uint32_t millisecond)
{
	std::lock_guard lockGuard(threadMutex);
	this->millisecond = millisecond;
}

void AuxPort::TimerWithCallback::stopTimer()
{
	std::lock_guard lockGuard(threadMutex);
	threadLoopBool = false;
	this->millisecond = 0;
}
