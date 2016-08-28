// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"

#include "Core/Containers/Array.h"
#include "Core/Strings/StringUtils.h"

#include "Core/Math/Vector2.h"

namespace Rio
{
	// Stream of characters.
	using StringStream = Array<char>;

	// Functions to operate on StringStream.
	namespace StringStreamFn
	{
		// Appends a value to the stream s using appropriate formatting.
		StringStream& operator<<(StringStream& s, char ch);
		StringStream& operator<<(StringStream& s, int16_t val);
		StringStream& operator<<(StringStream& s, uint16_t val);
		StringStream& operator<<(StringStream& s, int32_t val);
		StringStream& operator<<(StringStream& s, uint32_t val);
		StringStream& operator<<(StringStream& s, int64_t val);
		StringStream& operator<<(StringStream& s, uint64_t val);
		StringStream& operator<<(StringStream& s, float val);
		StringStream& operator<<(StringStream& s, double val);

		// Appends a C string to the stream
		StringStream& operator<<(StringStream& s, const char* string);

		// Returns the stream as a NULL-terminated C string.
		const char* toCStr(StringStream& s);

		StringStream& operator<<(StringStream& stringStream, const Vector2& v);

		template <typename T> StringStream& streamPrintf(StringStream& s, const char* format, T& val);

		inline StringStream& operator<<(StringStream& s, char ch)
		{
			ArrayFn::pushBack(s, ch);
			return s;
		}

		inline StringStream& operator<<(StringStream& s, int16_t val)
		{
			return streamPrintf(s, "%hd", val);
		}

		inline StringStream& operator<<(StringStream& s, uint16_t val)
		{
			return streamPrintf(s, "%hu", val);
		}

		inline StringStream& operator<<(StringStream& s, int32_t val)
		{
			return streamPrintf(s, "%d", val);
		}

		inline StringStream& operator<<(StringStream& s, uint32_t val)
		{
			return streamPrintf(s, "%u", val);
		}

		inline StringStream& operator<<(StringStream& s, int64_t val)
		{
			return streamPrintf(s, "%lld", val);
		}

		inline StringStream& operator<<(StringStream& s, uint64_t val)
		{
			return streamPrintf(s, "%llu", val);
		}

		inline StringStream& operator<<(StringStream& s, float val)
		{
			return streamPrintf(s, "%g", val);
		}

		inline StringStream& operator<<(StringStream& s, double val)
		{
			return streamPrintf(s, "%g", val);
		}

		inline StringStream& operator<<(StringStream& s, const char* str)
		{
			ArrayFn::push(s, str, strLen(str));
			return s;
		}

		inline const char* toCStr(StringStream& s)
		{
			ArrayFn::pushBack(s, '\0');
			ArrayFn::popBack(s);
			return ArrayFn::begin(s);
		}

		template <typename T>
		inline StringStream& streamPrintf(StringStream& stringStream, const char* format, T& val)
		{
			char buf[32];
			snPrintf(buf, sizeof(buf), format, val);
			return stringStream << buf;
		}

		inline StringStream& operator<<(StringStream& stringStream, const Vector2& v)
		{
			stringStream << "Vector2{" << v.x << ", " << v.y << "}";
			return stringStream;
		}

	} // namespace StringStreamFn

} // namespace Rio
