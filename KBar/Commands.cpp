#include "Commands.h"



int dir(String^ path)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;


	Console::WriteLine("dir {0}", path);


	pin_ptr<const wchar_t> wpath = PtrToStringChars(path);

	StringCchCopy(szDir, MAX_PATH, wpath);
	StringCchCat(szDir, MAX_PATH, TEXT("\\*"));



	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		return dwError;
	}



	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{

	}

	FindClose(hFind);
	return dwError;
}

int cd(String^ path)
{
	TCHAR dirBuff[MAX_PATH];
	DWORD ret;

	pin_ptr<const wchar_t> wname = PtrToStringChars(path);

	ret = SetCurrentDirectory(wname);

	return ret;
}

