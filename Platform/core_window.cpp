#include "core_window.h"
#include <iostream>

#ifdef _WIN32
#include <windowsx.h>
#endif


bool core_initialize_window(core_window& window, window_backend backend, i32 width, i32 height, const char* title) {
	window.backend = backend;

	switch (backend) {
#ifdef _WIN32	
	case window_backend::Win32:
		return core_initialize_win32(window, width, height, title);
#endif
#ifdef __linux__
	case window_backend::X11:
		return core_initialize_x11(window, width, height, title);
#endif
	default:
		return false;	
	}
}

void core_poll_events(core_window& window) {
	switch (window.backend) {
#ifdef _WIN32
	case window_backend::Win32:
		core_poll_events_win32(window);
		break;
#endif
#ifdef __linux__ 
	case WindowBackend::X11:
		core_poll_events_x11(window);
		break;
#endif
	}
}

void core_shutdown_window(core_window& window) {
	switch (window.backend) {
#ifdef _WIN32
	case window_backend::Win32:
		core_shutdown_win32(window);
		break;
#endif
#ifdef __linux__
	case: window_backend::X11:
		core_shutdown_x11(window);
		break;
#endif
	}
}

bool core_window_should_close(const core_window& window) {
	switch (window.backend) {
#ifdef _WIN32
	case window_backend::Win32:
		return window.win32.should_close;
#endif
#ifdef __linux__
	case window_backend::X11:
		return window.x11.shouldClose;
#endif
	default:
		return true;
	}
}

#ifdef _WIN32

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	core_window* window = reinterpret_cast<core_window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (msg){
	case WM_NCCREATE:
		{
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			window = reinterpret_cast<core_window*>(cs->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
			window->win32.hwnd = hwnd;
		}
		return 1;
	case WM_CLOSE:
		window->win32.should_close = true;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

bool core_initialize_win32(core_window& window, i32 width, i32 height, const char* title) {
	HINSTANCE hInstance = GetModuleHandle(nullptr);
	window.win32.hinstance = hInstance;

	WNDCLASSEXA wc{};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "HeliconWindowClass";

	if (!RegisterClassExA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
		return false;
	}

	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	RECT rect{ 0, 0, width, height };
	AdjustWindowRect(&rect, style, FALSE);

	window.win32.hwnd = CreateWindowExA(
		0,
		"HeliconWindowClass",
		title,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		nullptr, nullptr, hInstance, &window
	);

	if (!window.win32.hwnd) {
		return false;
	}

	ShowWindow(window.win32.hwnd, SW_SHOW);
	UpdateWindow(window.win32.hwnd);

	window.win32.should_close = false;

	return true;
}

void core_poll_events_win32(core_window& window)
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void core_shutdown_win32(core_window& window)
{
	if (window.win32.hwnd)
	{
		DestroyWindow(window.win32.hwnd);
		window.win32.hwnd = nullptr;
	}
}

#elif defined(__linux__)

	// X11 implementation

#endif // _WIN32