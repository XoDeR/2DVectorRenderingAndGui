// Copyright (c) 2015, 2016 Volodymyr Syvochka
#include "Core/Thread/Thread.h"

#if RIO_PLATFORM_WINDOWS

namespace Rio
{
	Thread::Thread()
		: threadHandle(INVALID_HANDLE_VALUE)
		, threadFunction(NULL)
		, threadData(NULL)
		, isRunning(false)
	{
	}

	Thread::~Thread()
	{
		if (isRunning)
		{
			stop();
		}
	}

	void Thread::start(ThreadFunction func, void* data, uint32_t stackSize)
	{
		RIO_ASSERT(!isRunning, "Thread is already running");
		RIO_ASSERT(func != NULL, "Function must be != NULL");
		threadFunction = func;
		threadData = data;
		threadStackSize = stackSize;

		threadHandle = CreateThread(NULL, stackSize, Thread::threadProc, this, 0, NULL);
		RIO_ASSERT(threadHandle != NULL, "CreateThread: GetLastError = %d", GetLastError());

		isRunning = true;
		semaphore.wait();
	}

	void Thread::stop()
	{
		RIO_ASSERT(isRunning, "Thread is not running");

		WaitForSingleObject(threadHandle, INFINITE);
		CloseHandle(threadHandle);
		threadHandle = INVALID_HANDLE_VALUE;

		isRunning = false;
	}

} // namespace Rio

#endif // RIO_PLATFORM_WINDOWS