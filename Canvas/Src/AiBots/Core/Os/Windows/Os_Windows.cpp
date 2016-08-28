// Copyright (c) 2015, 2016 Volodymyr Syvochka
#include "Core/Os/Os.h"

#if RIO_PLATFORM_WINDOWS
#include "Core/Os/Windows/Headers_Windows.h"
#include <io.h>

namespace Rio
{
	namespace Os
	{
		void log(const char* msg)
		{
			puts(msg);
			fflush(stdout);
#if RIO_DEBUG
			size_t size = Rio::strLen(msg);
			char str[2048];
			sprintf_s(str, msg, size);
			str[size] = '\0';
			::OutputDebugString(str);
#endif // RIO_DEBUG
		}

		bool doesPathExist(const char* path)
		{
			return _access(path, 0) != -1;
		}

		bool isDirectory(const char* path)
		{
			DWORD fAttr = GetFileAttributes(path);
			return (fAttr != INVALID_FILE_ATTRIBUTES && (fAttr & FILE_ATTRIBUTE_DIRECTORY) != 0);
		}

		bool isFile(const char* path)
		{
			DWORD fAttr = GetFileAttributes(path);
			return (fAttr != INVALID_FILE_ATTRIBUTES && (fAttr & FILE_ATTRIBUTE_DIRECTORY) == 0);
		}

		uint64_t getLastModifiedTime(const char* path)
		{
			HANDLE hfile = CreateFile(path
				, GENERIC_READ
				, FILE_SHARE_READ
				, NULL
				, OPEN_EXISTING
				, 0
				, NULL
				);
			RIO_ASSERT(hfile != INVALID_HANDLE_VALUE, "CreateFile: GetLastError = %d", GetLastError());
			FILETIME ftwrite;
			BOOL err = GetFileTime(hfile, NULL, NULL, &ftwrite);
			RIO_ASSERT(err != 0, "GetFileTime: GetLastError = %d", GetLastError());
			RIO_UNUSED(err);
			CloseHandle(hfile);
			return (uint64_t)((uint64_t(ftwrite.dwHighDateTime) << 32) | ftwrite.dwLowDateTime);
		}

		void createFile(const char* path)
		{
			HANDLE hFile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			RIO_ASSERT(hFile != INVALID_HANDLE_VALUE, "CreateFile: GetLastError = %d", GetLastError());
			CloseHandle(hFile);
		}

		void deleteFile(const char* path)
		{
			BOOL err = DeleteFile(path);
			RIO_ASSERT(err != 0, "DeleteFile: GetLastError = %d", GetLastError());
			RIO_UNUSED(err);
		}

		void createDirectory(const char* path)
		{
			BOOL err = CreateDirectory(path, NULL);
			RIO_ASSERT(err != 0, "CreateDirectory: GetLastError = %d", GetLastError());
			RIO_UNUSED(err);
		}

		void deleteDirectory(const char* path)
		{
			BOOL err = RemoveDirectory(path);
			RIO_ASSERT(err != 0, "RemoveDirectory: GetLastError = %d", GetLastError());
			RIO_UNUSED(err);
		}

		void getFileList(const char* path, Vector<DynamicString>& files)
		{
			TempAllocator1024 ta;
			DynamicString curPath(path, ta);
			curPath += "\\*";

			WIN32_FIND_DATA ffd;
			HANDLE file = FindFirstFile(curPath.toCStr(), &ffd);
			if (file == INVALID_HANDLE_VALUE)
			{
				return;
			}

			do
			{
				const char* fname = ffd.cFileName;

				if (!strCmp(fname, ".") || !strCmp(fname, ".."))
				{
					continue;
				}

				TempAllocator512 ta;
				DynamicString filename(fname, ta);
				VectorFn::pushBack(files, filename);
			} 
			while (FindNextFile(file, &ffd) != 0);

			FindClose(file);
		}

		const char* getCurrentDirName(char* buf, size_t size)
		{
			GetCurrentDirectory(size, buf);
			return buf;
		}

		int64_t getClockTime()
		{
			LARGE_INTEGER ttime;
			QueryPerformanceCounter(&ttime);
			return (int64_t)ttime.QuadPart;
		}

		int64_t getClockFrequency()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			return (int64_t)freq.QuadPart;
		}

		void* openLibrary(const char* path)
		{
			return (void*)LoadLibraryA(path);
		}

		void closeLibrary(void* library)
		{
			FreeLibrary((HMODULE)library);
		}

		void* lookupLibrarySymbol(void* library, const char* name)
		{
			return (void*)GetProcAddress((HMODULE)library, name);
		}

		int executeProcess(const char* path, const char* args, StringStream& output)
		{
			STARTUPINFO info;
			memset(&info, 0, sizeof(info));
			info.cb = sizeof(info);

			PROCESS_INFORMATION process;
			memset(&process, 0, sizeof(process));

			int err = CreateProcess(path, (LPSTR)args, NULL, NULL, TRUE, 0, NULL, NULL, &info, &process);
			RIO_ASSERT(err != 0, "CreateProcess: GetLastError = %d", GetLastError());
			RIO_UNUSED(err);

			DWORD exitCode = 1;
			::WaitForSingleObject(process.hProcess, INFINITE);
			GetExitCodeProcess(process.hProcess, &exitCode);
			CloseHandle(process.hProcess);
			CloseHandle(process.hThread);
			return (int)exitCode;
		}

	} // namespace Os
} // namespace Rio

#endif // RIO_PLATFORM_WINDOWS
