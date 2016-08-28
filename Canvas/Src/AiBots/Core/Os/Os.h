// Copyright (c) 2015, 2016 Volodymyr Syvochka
#pragma once

#include "Core/Base/Config.h"
#include "Core/Base/Types.h"
#include "Core/Memory/TempAllocator.h"
#include "Core/Debug/Error.h"
#include "Core/Containers/Vector.h"
#include "Core/Strings/DynamicString.h"
#include "Core/Strings/StringUtils.h"
#include "Core/Strings/StringStream.h"

namespace Rio
{
	namespace Os
	{
		void log(const char* msg);
		bool doesPathExist(const char* path);
		// Returns whether the path is a directory
		bool isDirectory(const char* path);
		// Returns whether the path is a regular file
		bool isFile(const char* path);
		// Returns the last modification time of the path
		uint64_t getLastModifiedTime(const char* path);
		// Creates a regular file.
		void createFile(const char* path);
		// Deletes a regular file.
		void deleteFile(const char* path);
		void createDirectory(const char* path);
		// Deletes a directory.
		void deleteDirectory(const char* path);
		// Returns the list of files at the given path
		// NOTE Does not follow symbolic links
		void getFileList(const char* path, Vector<DynamicString>& files);
		const char* getCurrentDirName(char* buf, size_t size);
		int64_t getClockTime();
		int64_t getClockFrequency();
		void* openLibrary(const char* path);
		void closeLibrary(void* library);
		void* lookupLibrarySymbol(void* library, const char* name);
		// Executes the process with the given args and returns its exit code
		// output is filled with stdout and stderr.
		int executeProcess(const char* path, const char* args, StringStream& output);
	} // namespace Os

} // namespace Rio
