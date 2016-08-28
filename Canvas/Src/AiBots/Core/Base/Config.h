// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Platform.h"

// Dependencies
// Third party libs
#ifndef RIO_BGFX
#define RIO_BGFX 0
#endif // RIO_BGFX

#ifndef RIO_DEBUG
#define RIO_DEBUG 1
#endif // RIO_DEBUG

////////////////
// Module Debug

// Whether to use profiler
#ifndef RIO_USE_PROFILER
#define RIO_USE_PROFILER 0
#endif // RIO_USE_PROFILER

// Whether to use debug console
#ifndef RIO_USE_DEBUG_CONSOLE
#define RIO_USE_DEBUG_CONSOLE 0
#endif // RIO_USE_DEBUG_CONSOLE

//
////////////////

// Whether to use script system
#ifndef RIO_USE_SCRIPT
#define RIO_USE_SCRIPT 0
#endif // RIO_USE_SCRIPT

// Whether to use 2D rendering system (2D sprites)
#ifndef RIO_USE_2D
#define RIO_USE_2D 0
#endif // RIO_USE_2D

// Whether to use audio system
#ifndef RIO_USE_AUDIO
#define RIO_USE_AUDIO 0
#endif // RIO_USE_AUDIO

// Whether to use physics system
#ifndef RIO_USE_PHYSICS
#define RIO_USE_PHYSICS 0
#endif // RIO_USE_PHYSICS

// Whether world (system manager) is enabled
#ifndef RIO_USE_WORLD
#define RIO_USE_WORLD 0
#endif // RIO_USE_WORLD

// Whether resource manager is enabled
#ifndef RIO_USE_RESOURCE_MANAGER
#define RIO_USE_RESOURCE_MANAGER 0
#endif // RIO_USE_RESOURCE_MANAGER

// Whether debug shapes are enabled
#ifndef RIO_USE_DEBUG_SHAPES
#define RIO_USE_DEBUG_SHAPES 0
#endif // RIO_USE_DEBUG_SHAPES
