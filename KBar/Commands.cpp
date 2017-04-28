#include "Commands.h"
using namespace msclr::interop;






int dir(String^ path)
{
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
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
	DWORD ret;

	pin_ptr<const wchar_t> wname = PtrToStringChars(path);

	ret = SetCurrentDirectory(wname);

	return ret;
}



int screenshot(String^ fname)
{
	const char* standardname = (const char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fname);

	RECT desktop;
	int x = 0;
	int y = 0;

	const HWND desktopHandle = GetDesktopWindow();
	GetWindowRect(desktopHandle, &desktop);
	x = desktop.right;
	y = desktop.bottom;



	HDC     hScreen = GetDC(NULL);
	HDC     hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, x, y);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL    bRet = BitBlt(hDC, 0, 0, x, y, hScreen, 0, 0, SRCCOPY);

	// save bitmap to file
	BITMAP bmp;
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bmp.bmWidth;
	bmi.bmiHeader.biHeight = -bmp.bmHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = bmp.bmWidth* bmp.bmHeight * 32 / 8;

	FILE* image = fopen(standardname, "wb");
	
	BITMAPFILEHEADER bmp_fh;
	bmp_fh.bfType = 0x4D42;
	bmp_fh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmp_fh.bfSize = bmi.bmiHeader.biSizeImage + bmp_fh.bfOffBits;
	bmp_fh.bfReserved1 = 0;
	bmp_fh.bfReserved2 = 0;
	BYTE *lpBits = new BYTE[bmp.bmWidth*bmp.bmHeight*bmp.bmBitsPixel / 8];
	GetBitmapBits((HBITMAP)hBitmap, (bmp.bmWidth*bmp.bmHeight*bmp.bmBitsPixel / 8), lpBits);

	try
	{
		fwrite(&bmp_fh, sizeof(bmp_fh), 1, image);
		fwrite(&bmi.bmiHeader, sizeof(BITMAPINFOHEADER), 1, image);
		fwrite(lpBits, bmi.bmiHeader.biSizeImage, 1, image);
		fclose(image);
	}
	catch (Exception^ e)
	{
		Console::WriteLine("Error writing the file: {0}", e);
	}

	


	// clean up
	SelectObject(hDC, old_obj);
	DeleteDC(hDC);
	ReleaseDC(NULL, hScreen);
	DeleteObject(hBitmap);
	return 0;
}


int timestomp(String^ good, String^ bad)
{
	int gerr;
	int serr;
	marshal_context mc;

	LPCTSTR goodname = mc.marshal_as<LPCTSTR>(good);
	LPCTSTR badname = mc.marshal_as<LPCTSTR>(bad);

	LPSECURITY_ATTRIBUTES lpSec;

	HANDLE gHandle = CreateFile(goodname, (GENERIC_READ | GENERIC_WRITE), 0, lpSec, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE bHandle = CreateFile(badname, (GENERIC_READ | GENERIC_WRITE), 0, lpSec, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (gHandle == INVALID_HANDLE_VALUE)
	{
		printf("Could not open file, error %ul\n", GetLastError());
		return -1;
	}

	if (bHandle == INVALID_HANDLE_VALUE)
	{
		printf("Could not open file, error %ul\n", GetLastError());
		return -1;
	}

	 FILETIME goodCreate;
	 FILETIME goodAccess;
	 FILETIME goodWrite;

	 gerr = GetFileTime(gHandle, &goodCreate, &goodAccess, &goodWrite);
	 serr = SetFileTime(bHandle, &goodCreate, &goodAccess, &goodWrite);

	 if ((serr == 0) || (gerr == 0))
	 {
		 Console::WriteLine("Did not set file\n");
		 return 1;
	 }
	 else
	 {

		 Console::WriteLine("Filetime set\n");
		 return 0;
	 }

}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{

	if (IsWindowVisible(hwnd))
	{
	
	int len = GetWindowTextLength(hwnd);

	TCHAR* buff;
	buff = new TCHAR[len + 1];
	memset(buff, 0, (len + 1) * sizeof(TCHAR));

	GetWindowText(hwnd, buff, len + 1);
	String^ winTitle = gcnew String(buff);
	delete[] buff;

	Console::WriteLine(winTitle);
	return TRUE;
}
	return TRUE;
}


void winlist()
{
	EnumWindows(EnumWindowsProc, NULL);

}
		