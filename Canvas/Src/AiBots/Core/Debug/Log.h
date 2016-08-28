// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"
#include <cstdarg>

namespace Rio
{

	struct LogSeverity
	{
		enum Enum
		{
			INFO = 0,
			WARN = 1,
			Error = 2,
			Debug = 3
		};
	};

	namespace LogInternalFn
	{
		void logx(LogSeverity::Enum sev, const char* msg, va_list args);
		void logx(LogSeverity::Enum sev, const char* msg, ...);
	} // namespace LogInternalFn

} // namespace Rio

#if RIO_DEBUG
#define RIO_LOGIV(msg, va_list) Rio::LogInternalFn::logx(Rio::LogSeverity::INFO, msg, va_list)
#define RIO_LOGDV(msg, va_list) Rio::LogInternalFn::logx(Rio::LogSeverity::Debug, msg, va_list)
#define RIO_LOGEV(msg, va_list) Rio::LogInternalFn::logx(Rio::LogSeverity::Error, msg, va_list)
#define RIO_LOGWV(msg, va_list) Rio::LogInternalFn::logx(Rio::LogSeverity::WARN, msg, va_list)

#define RIO_LOGI(msg, ...) Rio::LogInternalFn::logx(Rio::LogSeverity::INFO, msg, ##__VA_ARGS__)
#define RIO_LOGD(msg, ...) Rio::LogInternalFn::logx(Rio::LogSeverity::Debug, msg, ##__VA_ARGS__)
#define RIO_LOGE(msg, ...) Rio::LogInternalFn::logx(Rio::LogSeverity::Error, msg, ##__VA_ARGS__)
#define RIO_LOGW(msg, ...) Rio::LogInternalFn::logx(Rio::LogSeverity::WARN, msg, ##__VA_ARGS__)
#else
#define RIO_LOGIV(msg, va_list) ((void)0)
#define RIO_LOGDV(msg, va_list) ((void)0)
#define RIO_LOGEV(msg, va_list) ((void)0)
#define RIO_LOGWV(msg, va_list) ((void)0)

#define RIO_LOGI(msg, ...) ((void)0)
#define RIO_LOGD(msg, ...) ((void)0)
#define RIO_LOGE(msg, ...) ((void)0)
#define RIO_LOGW(msg, ...) ((void)0)
#endif // RIO_DEBUG
