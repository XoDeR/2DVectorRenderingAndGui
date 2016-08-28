// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"

#include "Core/Base/Types.h"
#include "Core/Debug/Error.h" // RIO_ASSERT

#include "Core/Memory/Allocator.h"

namespace Rio
{

	Allocator& getDefaultAllocator();
	Allocator& getDefaultScratchAllocator();

	namespace MemoryFn
	{
		// Returns the pointer aligned to the desired align byte
		inline void* getAlignTop(void* ptr, size_t align)
		{
			RIO_ASSERT((align != 0) && !(align & (align - 1)), "Check if power of 2");

			uintptr_t p = (uintptr_t)ptr;
			const size_t mod = p % align;
			if (mod)
			{
				p += (uintptr_t)(align - mod);
			}
			return (void*)p;
		}
	} // namespace MemoryFn

#define ALLOCATOR_AWARE using allocatorAware = int

	// Convert integer to type.
	template <int v>
	struct Int2Type 
	{ 
		enum 
		{ 
			value = v 
		}; 
	};

	// Determines if a class is allocator aware.
	template <class T>
	struct isAllocatorAware 
	{
		template <typename C>
		static char testFunction(typename C::allocatorAware*);

		template <typename C>
		static int testFunction(...);

		enum 
		{
			value = (sizeof(testFunction<T>(0)) == sizeof(char))
		};
	};

#define IS_ALLOCATOR_AWARE(T) isAllocatorAware<T>::value
#define IS_ALLOCATOR_AWARE_TYPE(T) Int2Type< IS_ALLOCATOR_AWARE(T) >

	// Allocator aware construction
	template <class T> inline T& construct(void *p, Allocator& a, Int2Type<true>) 
	{ 
		new (p)T(a); return *(T *)p; 
	}

	template <class T> inline T& construct(void *p, Allocator& a, Int2Type<false>) 
	{ 
		new (p)T; return *(T *)p; 
	}

	template <class T> inline T& construct(void *p, Allocator& a) 
	{ 
		return construct<T>(p, a, IS_ALLOCATOR_AWARE_TYPE(T)()); 
	}

	namespace MemoryGlobalsFn
	{
		// Constructs the initial default allocators.
		// Has to be called before anything else during the engine startup.
		void init();
		// Destroys the allocators created with MemoryGlobalsFn::init().
		// Should be the last call of the program.
		void shutdown();
	} // namespace MemoryGlobalsFn

} // namespace Rio
