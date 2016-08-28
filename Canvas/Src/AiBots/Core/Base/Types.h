// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"
#include "Core/Base/Macros.h"

#include <type_traits>
#include <memory>

#include <cstddef> // NULL
#include <cstring>
#include <cstdint>

#if defined(_MSC_VER)
#define _ALLOW_KEYWORD_MACROS
#endif

namespace Rio
{
	//static_assert(sizeof(int64_t) == sizeof(size_t), "int64_t is not the same size as size_t");
} // namespace Rio


