#include "Window.h"

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				if (MessageBox(
					NULL,
					TEXT("종료하시겠습니까?"),
					TEXT("종료"),
					MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					DestroyWindow(hwnd);
				}
			}
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Window::Init(HINSTANCE hInstance, int width, int height, std::wstring title)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->title = title;
	
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = TEXT("Engine");

	if (RegisterClassExW(&wcex) == false)
		return false;

	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	this->width = rect.right - rect.left;
	this->height = rect.bottom - rect.top;

	this->hwnd = CreateWindowW(wcex.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW,
		0, 0, this->width, this->height, NULL, NULL, hInstance, NULL);
	
	if (!this->hwnd)
		return false;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return true;
}
