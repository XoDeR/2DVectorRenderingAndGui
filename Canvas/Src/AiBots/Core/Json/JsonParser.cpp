// Copyright (c) 2015, 2016 Volodymyr Syvochka
#include "JsonParser.h"

#include "Core/Json/Rjson.h"
#include "Core/Memory/TempAllocator.h"
#include "Core/Strings/StringUtils.h"
#include "Core/FileSystem/File.h"

namespace Rio
{

	JsonParser::JsonParser(const char* s)
		: jsonDocument(s)
	{
		RIO_ASSERT_NOT_NULL(s);
	}

	JsonParser::JsonParser(File& f)
		: isFromFile(true)
	{
		const size_t size = f.getFileSize() + 1; // for ending zero symbol
		char* doc = (char*)getDefaultAllocator().allocate(size);
		f.read(doc, size - 1);
		// add ending zero
		doc[size - 1] = '\0';

		jsonDocument = doc;
	}

	JsonParser::~JsonParser()
	{
		if (isFromFile == true)
		{
			getDefaultAllocator().deallocate((void*)jsonDocument);
		}
	}

	JsonElement JsonParser::getJsonRoot()
	{
		const char* ch = jsonDocument;
		while ((*ch) && (*ch) <= ' ')
		{
			ch++;
		}

		return JsonElement(ch);
	}

} // namespace Rio
