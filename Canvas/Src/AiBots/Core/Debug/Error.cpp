// Copyright (c) 2015, 2016 Volodymyr Syvochka
#include "Core/Debug/Error.h"
#include "Core/Debug/StackTrace.h"

#include "Core/Os/Os.h"

#if RIO_PLATFORM_WINDOWS
#include "Core/Os/Windows/Headers_Windows.h" // DebugBreak()
#endif // RIO_PLATFORM_WINDOWS

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

namespace Rio
{
	namespace ErrorFn
	{
		void abort(const char* file, int line, const char* message, ...)
		{
			va_list ap;
			va_start(ap, message);
			vprintf(message, ap);
			va_end(ap);

			printf("\tIn: %s:%d\n", file, line);
			printf("Stacktrace:\n");
			printCallStack();

#if RIO_PLATFORM_WINDOWS
			::DebugBreak();
#else
			::exit(EXIT_FAILURE);
#endif // RIO_PLATFORM_WINDOWS
		}
	} // namespace ErrorFn

} // namespace Rio
