#pragma once

#include "Core/Base/Config.h"
#include "Core/Base/Types.h"

#include <cstdarg>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>

namespace Rio
{
	namespace
	{
		template <typename T, typename... Args>
		static std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args)
		{
			return std::unique_ptr < T > {new T{ std::forward<Args>(args)... }};
		}

		template <typename T, typename... Args>
		static std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args)
		{
			static_assert(std::extent<T>::value == 0,
				"Rio::make_unique<T[N]>() is forbidden, "
				"please use make_unique<T[]>().");

			typedef typename std::remove_extent<T>::type U;
			return std::unique_ptr < T > {
				new U[sizeof...(Args)]{std::forward<Args>(args)...}};
		}
	} // namespace (anonymous)

	// NOTE: Used as std::make_unique is not available in C++11, only C++14
	// MSVC does support std::make_unique but use this function instead
	template <typename T, typename... Args>
	inline std::unique_ptr<T> make_unique(Args&&... args)
	{
		return make_unique_helper<T>(std::is_array<T>(),
			std::forward<Args>(args)...);
	}

	// NOTE: Very similar to doing
	//             `*(T*)(&x)`
	// NOTE: This also uses snake_case rather than camelCase to be consistent
	// with the other casting types (e.g. static_cast, dynamic_cast, etc.)
	// NOTE IMPORTANT: Only use for small types as it requires `memcpy`
	template <typename T, typename U>
	inline T pseudo_cast(const U& x)
	{
		T to{ 0 };
		memcpy(&to, &x, (sizeof(T) < sizeof(U)) ? sizeof(T) : sizeof(U));
		return to;
	}

	namespace Impl
	{
		template <typename Fn>
		struct Defer
		{
			Defer(Fn&& fn)
				: fn{ std::forward<Fn>(fn) }
			{
			}
			~Defer() { fn(); };
			Fn fn;
		};

		template <typename Fn>
		Defer<Fn> deferFn(Fn&& fn) { return Defer<Fn>(std::forward<Fn>(fn)); }
	} // namespace Impl

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x) DEFER_2(x, __COUNTER__)
#define defer(code) auto DEFER_3(_defer_) = Impl::deferFn([&](){code;});

	// Example for defer
	// FILE* file = fopen("test.txt", "r"));
	// if (f == nullptr)
	// 	return;
	// defer(fclose(file));

} // namespace Rio
