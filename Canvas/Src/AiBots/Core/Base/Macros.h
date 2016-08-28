// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"

#if RIO_COMPILER_MSVC
#define RIO_ALIGNOF(x) __alignof(x)
#define RIO_EXPORT __declspec(dllexport)
#define RIO_INLINE __inline
#define RIO_THREAD __declspec(thread)
#elif RIO_COMPILER_GCC
#define RIO_ALIGNOF(x) __alignof__(x)
#define RIO_EXPORT __attribute__ ((visibility("default")))
#define RIO_INLINE inline
#define RIO_THREAD __thread
// TODO: add RIO_COMPILER_CLANG
#else
#error "Compiler not supported"
#endif

// a macro for eliminating the unused variable warning
#define RIO_UNUSED(x) do { (void)(x); } while (0)
#define RIO_COUNTOF(arr) (sizeof(arr)/sizeof(arr[0]))
#define RIO_CONCATENATE1(a, b) a ## b
#define RIO_CONCATENATE(a, b) RIO_CONCATENATE1(a, b)
#define RIO_STATIC_ASSERT(condition) typedef int RIO_CONCATENATE(STATIC_ASSERT,__LINE__)[condition ? 1 : -1]