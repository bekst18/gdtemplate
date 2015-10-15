#include <pch.hpp>

#define MAX_LOADSTRING 100

ATOM MyRegisterClass(HINSTANCE hInstance);
bool init_instance(HINSTANCE inst, ATOM cls, int show_cmd);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE inst, HINSTANCE prev_inst, LPWSTR cmd_line, int show_cmd)
{
	// suppresses warnings
	UNREFERENCED_PARAMETER(prev_inst);
	UNREFERENCED_PARAMETER(cmd_line);

	// Initialize global strings
	auto cls = MyRegisterClass(inst);
	if (!init_instance(inst, cls, show_cmd))
	{
		return FALSE;
	}

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE inst)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = inst;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = 0;
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"GDWindow";
	wcex.hIconSm = 0;
	return RegisterClassExW(&wcex);
}

bool init_instance(HINSTANCE inst, ATOM cls, int show_cmd)
{
	auto hwnd = CreateWindow(
		reinterpret_cast<wchar_t*>(cls),
		L"Main Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		inst,
		nullptr);

	if (!hwnd)
	{
		return false;
	}

	ShowWindow(hwnd, show_cmd);
	UpdateWindow(hwnd);

	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wparam, lparam);
	}
	return 0;
}