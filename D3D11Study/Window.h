#pragma once

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

// C runtime header
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>

class Window
{

public:

	bool Init(HINSTANCE hInstance, int width, int height, std::wstring title);

	

private:

	HWND hwnd;
	HINSTANCE hInstance;

	int height, width;
	std::wstring title;

};

