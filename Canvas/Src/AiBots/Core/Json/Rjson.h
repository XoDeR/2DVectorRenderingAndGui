// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"

#include "Core/Strings/DynamicString.h"
#include "Core/Strings/StringId64.h"
#include "Core/Containers/Map.h"

#include "Core/Json/JsonTypes.h"

#include "Core/Math/Vector2.h"

namespace Rio
{
	// Functions to parse RJSON-encoded strings.
	namespace Rjson
	{
		// Returns the data type of the RJSON string
		JsonValueType::Enum getJsonType(const char* json);
		void parseString(const char* json, DynamicString& string);
		double parseDouble(const char* json);
		int32_t parseInt(const char* json);
		uint32_t parseUint(const char* json);
		float parseFloat(const char* json);
		bool parseBool(const char* json);
		
		// Parses the RJSON array and puts it into array as pointers to
		// the corresponding items into the original json string.
		void parseArray(const char* json, JsonArray& array);
		
		// Parses the RJSON object and puts it into object as map from
		// key to pointer to the corresponding value into the original string json.
		void parseObject(const char* json, Map<DynamicString, const char*>& object);

		// Parses the RJSON object and puts it into object as map from
		// key to pointer to the corresponding value into the original json string
		void parseObject(const char* json, JsonObject& object);

		// Parses the RJSON-encoded json.
		void parse(const char* json, JsonObject& object);

		// Parses the RJSON-encoded json.
		void parse(Buffer& json, JsonObject& object);

		// Vector2 = [x, y]
		Vector2 parseVector2(const char* json);

		// Returns the json string as StringId32.
		StringId32 parseStringId(const char* json);

		// Returns the json string as ResourceId.
		ResourceId parseResourceId(const char* json);

	} // namespace Rjson

} // namespace Rio
