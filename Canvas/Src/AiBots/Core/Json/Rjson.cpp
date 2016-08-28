// Copyright (c) 2015, 2016 Volodymyr Syvochka
#include "Core/Json/Rjson.h"
#include "Core/Strings/StringUtils.h"
#include "Core/Memory/TempAllocator.h"
#include "Core/Containers/Map.h"

namespace Rio
{
	namespace Rjson
	{
		static const char* getNext(const char* json, const char c = 0)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (c && c != *json)
			{
				RIO_ASSERT(false, "Expected '%c' got '%c'", c, *json);
			}

			return ++json;
		}

		static const char* skipString(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			bool escaped = false;

			while ((*(json = getNext(json))) != 0)
			{
				if (*json == '"' && !escaped)
				{
					json = getNext(json);
					return json;
				}
				else if (*json == '\\')
				{
					escaped = true;
				}
				else
				{
					escaped = false;
				}
			}

			return json;
		}

		static const char* skipValue(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			switch (*json)
			{
			case '"': json = skipString(json); break;
			case '[': json = skipBlock(json, '[', ']'); break;
			case '{': json = skipBlock(json, '{', '}'); break;
			default: for (; *json != ',' && *json != '\n' && *json != ' ' && *json != '}' && *json != ']'; ++json); break;
			}

			return json;
		}

		static const char* skipComments(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (*json == '/')
			{
				json = getNext(json);
				if (*json == '/')
				{
					json = getNext(json, '/');
					while (*json && *json != '\n')
					{
						json = getNext(json);
					}
				}
				else if (*json == '*')
				{
					json = getNext(json);
					while (*json && *json != '*')
					{
						json = getNext(json);
					}
					json = getNext(json, '*');
					json = getNext(json, '/');
				}
				else
				{
					RIO_FATAL("Bad comment");
				}
			}

			return json;
		}

		static const char* skipSpaces(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			while (*json)
			{
				if (*json == '/') json = skipComments(json);
				else if (isSpace(*json) || *json == ',') ++json;
				else break;
			}

			return json;
		}

		JsonValueType::Enum getJsonType(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			switch (*json)
			{
			case '"': return JsonValueType::STRING;
			case '{': return JsonValueType::OBJECT;
			case '[': return JsonValueType::ARRAY;
			case '-': return JsonValueType::NUMBER;
			default: return (::isdigit(*json)) ? JsonValueType::NUMBER : (*json == 'n' ? JsonValueType::NIL : JsonValueType::BOOL);
			}
		}

		void parseString(const char* json, DynamicString& string)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (*json == '"')
			{
				while (*(json = getNext(json)))
				{
					// Empty string
					if (*json == '"')
					{
						json = getNext(json);
						return;
					}
					else if (*json == '\\')
					{
						json = getNext(json);

						switch (*json)
						{
						case '"': string += '"'; break;
						case '\\': string += '\\'; break;
						case '/': string += '/'; break;
						case 'b': string += '\b'; break;
						case 'f': string += '\f'; break;
						case 'n': string += '\n'; break;
						case 'r': string += '\r'; break;
						case 't': string += '\t'; break;
						default:
						{
							RIO_FATAL("Bad escape character");
							break;
						}
						}
					}
					else
					{
						string += *json;
					}
				}
			}

			RIO_FATAL("Bad string");
		}

		static const char* parseKey(const char* json, DynamicString& key)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (*json == '"')
			{
				parseString(json, key);
				return skipString(json);
			}
			else if (::isalpha(*json)) // TODO replace for internal string function
			{
				while (true)
				{
					// TODO replace for internal string function
					if (::isspace(*json) || *json == '=')
					{
						return json;
					}

					key += *json;
					++json;
				}
			}

			RIO_FATAL("Bad key");
		}

		double parseDouble(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			TempAllocator512 alloc;
			Array<char> number(alloc);

			if (*json == '-')
			{
				ArrayFn::pushBack(number, '-');
				json = getNext(json, '-');
			}
			while (isDigit(*json))
			{
				ArrayFn::pushBack(number, *json);
				json = getNext(json);
			}

			if (*json == '.')
			{
				ArrayFn::pushBack(number, '.');
				while ((*(json = getNext(json))) && ::isdigit(*json)) // TODO replace for internal string function
				{
					ArrayFn::pushBack(number, *json);
				}
			}

			if (*json == 'e' || *json == 'E')
			{
				ArrayFn::pushBack(number, *json);
				json = getNext(json);

				if (*json == '-' || *json == '+')
				{
					ArrayFn::pushBack(number, *json);
					json = getNext(json);
				}
				while (::isdigit(*json)) // TODO replace for internal string function
				{
					ArrayFn::pushBack(number, *json);
					json = getNext(json);
				}
			}

			// Ensure null terminated
			ArrayFn::pushBack(number, '\0');
			return Rio::parseDouble(ArrayFn::begin(number));
		}

		bool parseBool(const char* json)
		{
			RIO_ASSERT_NOT_NULL(json);

			switch (*json)
			{
			case 't':
			{
				json = getNext(json, 't');
				json = getNext(json, 'r');
				json = getNext(json, 'u');
				json = getNext(json, 'e');
				return true;
			}
			case 'f':
			{
				json = getNext(json, 'f');
				json = getNext(json, 'a');
				json = getNext(json, 'l');
				json = getNext(json, 's');
				json = getNext(json, 'e');
				return false;
			}
			default:
			{
				RIO_FATAL("Bad boolean");
				return false;
			}
			}
		}

		int32_t parseInt(const char* json)
		{
			return (int32_t)parseDouble(json);
		}

		uint32_t parseUint(const char* json)
		{
			return (uint32_t)parseDouble(json);
		}

		float parseFloat(const char* json)
		{
			return (float)parseDouble(json);
		}

		void parseArray(const char* json, JsonArray& array)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (*json == '[')
			{
				json = getNext(json, '[');
				json = skipSpaces(json);

				if (*json == ']')
				{
					json = getNext(json, ']');
					return;
				}

				while (*json)
				{
					ArrayFn::pushBack(array, json);

					json = skipValue(json);
					json = skipSpaces(json);

					if (*json == ']')
					{
						json = getNext(json, ']');
						return;
					}

					json = skipSpaces(json);
				}
			}

			RIO_FATAL("Bad array");
		}

		void parseRootObject(const char* json, Map<DynamicString, const char*>& object)
		{
			RIO_ASSERT_NOT_NULL(json);

			while (*json)
			{
				TempAllocator256 ta;
				DynamicString key(ta);
				json = parseKey(json, key);

				json = skipSpaces(json);
				json = getNext(json, '=');
				json = skipSpaces(json);

				MapFn::set(object, key, json);

				json = skipValue(json);
				json = skipSpaces(json);
			}
		}

		void parseObject(const char* json, Map<DynamicString, const char*>& object)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (*json == '{')
			{
				json = getNext(json, '{');

				json = skipSpaces(json);

				if (*json == '}')
				{
					getNext(json, '}');
					return;
				}

				while (*json)
				{
					TempAllocator256 ta;
					DynamicString key(ta);
					json = parseKey(json, key);

					json = skipSpaces(json);
					json = getNext(json, '=');
					json = skipSpaces(json);

					MapFn::set(object, key, json);

					json = skipValue(json);
					json = skipSpaces(json);

					if (*json == '}')
					{
						getNext(json, '}');
						return;
					}

					json = skipSpaces(json);
				}
			}

			RIO_FATAL("Bad object");
		}

		void parse(const char* json, Map<DynamicString, const char*>& object)
		{
			RIO_ASSERT_NOT_NULL(json);

			json = skipSpaces(json);

			if (*json == '{')
			{
				parseObject(json, object);
			}
			else
			{
				parseRootObject(json, object);
			}
		}

		void parseRootObject(const char* json, JsonObject& object)
		{
			RIO_ASSERT_NOT_NULL(json);

			while (*json)
			{
				const char* keyBegin = *json == '"' ? (json + 1) : json;

				TempAllocator256 ta;
				DynamicString key(ta);
				json = parseKey(json, key);

				FixedString fixedSizeKey(keyBegin, key.getLength());

				json = skipSpaces(json);
				json = getNext(json, '=');
				json = skipSpaces(json);

				MapFn::set(object, fixedSizeKey, json);

				json = skipValue(json);
				json = skipSpaces(json);
			}
		}

		void parseObject(const char* json, JsonObject& object)
		{
			RIO_ASSERT_NOT_NULL(json);

			if (*json == '{')
			{
				json = getNext(json, '{');

				json = skipSpaces(json);

				if (*json == '}')
				{
					getNext(json, '}');
					return;
				}

				while (*json)
				{
					const char* keyBegin = *json == '"' ? (json + 1) : json;

					TempAllocator256 ta;
					DynamicString key(ta);
					json = parseKey(json, key);

					FixedString fixedSizeKey(keyBegin, key.getLength());

					json = skipSpaces(json);
					json = getNext(json, '=');
					json = skipSpaces(json);

					MapFn::set(object, fixedSizeKey, json);

					json = skipValue(json);
					json = skipSpaces(json);

					if (*json == '}')
					{
						getNext(json, '}');
						return;
					}

					json = skipSpaces(json);
				}
			}

			RIO_FATAL("Bad object");
		}

		void parse(const char* json, JsonObject& object)
		{
			RIO_ASSERT_NOT_NULL(json);

			json = skipSpaces(json);

			if (*json == '{')
			{
				parseObject(json, object);
			}
			else
			{
				parseRootObject(json, object);
			}
		}

		void parse(Buffer& json, JsonObject& object)
		{
			ArrayFn::pushBack(json, '\0');
			ArrayFn::popBack(json);
			parse(ArrayFn::begin(json), object);
		}

		Vector2 parseVector2(const char* json)
		{
			TempAllocator64 ta;
			JsonArray array(ta);
			Rjson::parseArray(json, array);

			Vector2 v;
			v.x = Rjson::parseFloat(array[0]);
			v.y = Rjson::parseFloat(array[1]);
			return v;
		}

		StringId32 parseStringId(const char* json)
		{
			TempAllocator1024 ta;
			DynamicString str(ta);
			Rjson::parseString(json, str);
			return str.toStringId32();
		}

		ResourceId parseResourceId(const char* json)
		{
			TempAllocator1024 ta;
			DynamicString str(ta);
			Rjson::parseString(json, str);
			return ResourceId(str.toCStr());
		}

	} // namespace Rjson

} // namespace Rio
