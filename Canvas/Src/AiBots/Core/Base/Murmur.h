// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"
#include "Core/Base/Types.h"

namespace Rio
{
	uint32_t murmur32(const void* key, uint32_t len, uint32_t seed = 0);
	uint64_t murmur64(const void* key, uint32_t len, uint64_t seed = 0);
} // namespace Rio
