#include "HcWin32Window.h"

#include <stdint.h>
using u32 = uint32_t;

bool HcWin32Window::Initialize(HINSTANCE hInstance, int width, int height, const char* title)
{
    m_hInstance = hInstance;

    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = HcWin32Window::WndProc;
    wc.hInstance = m_hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "HeliconWindowClass";

    if (!RegisterClassExA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return false;

    DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    RECT rect{ 0, 0, width, height };
    AdjustWindowRect(&rect, style, FALSE);

    m_hWnd = CreateWindowExA(
        0,
        "HeliconWindowClass",
        title,
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr, nullptr, m_hInstance, this
    );

    if (!m_hWnd) return false;

    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    return true;
}

void HcWin32Window::PollEvents()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void HcWin32Window::Shutdown()
{
    if (m_hWnd)
    {
        DestroyWindow(m_hWnd);
        m_hWnd = nullptr;
    }

    if (m_hInstance)
    {
        UnregisterClassA("HeliconWindowClass", m_hInstance);
        m_hInstance = nullptr;
    }
}

LRESULT CALLBACK HcWin32Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HcWin32Window* window = nullptr;

    if (msg == WM_NCCREATE)
    {
        auto createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        window = reinterpret_cast<HcWin32Window*>(createStruct->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

        if (window->m_splashHWnd == nullptr) {
            window->m_hWnd = hWnd;
        }
    }
    else
    {
        window = reinterpret_cast<HcWin32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (window)
    {
        switch (msg)
        {
        case WM_CLOSE:
            DestroyWindow(hWnd); // triggers WM_DESTROY
            return 0;

        case WM_DESTROY:
            if (hWnd == window->m_hWnd)
            {
                window->m_shouldClose = true;
                PostQuitMessage(0);
            }
            return 0;
        case WM_SIZE:
            { 
            u32 width = LOWORD(lParam);
            u32 height = HIWORD(lParam);

            // renderer->onResize(width, height);
            return 0;
            } 
            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                if (hWnd == window->m_splashHWnd && window->m_hSplashImage)
                {
                    HDC hMemDC = CreateCompatibleDC(hdc);
                    SelectObject(hMemDC, window->m_hSplashImage);

                    RECT rect;
                    GetClientRect(hWnd, &rect);

                    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);

                    DeleteDC(hMemDC);
                }
                EndPaint(hWnd, &ps);
            }
            return 0;
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void HcWin32Window::CreateLaunchWindow(HINSTANCE hInstance, int width, int height)
{
    RegisterWindowClass(hInstance);

    int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

    DWORD style = WS_POPUP | WS_VISIBLE;

    m_splashHWnd = CreateWindowExA(
        WS_EX_TOOLWINDOW,
        "HeliconWindowClass",
        "Helicon Launching...",
        style,
        x, y, width, height,
        nullptr, nullptr, hInstance, this 
    );

    if (!m_splashHWnd) {
        DWORD error = GetLastError();
        return;
    }


    if (m_hSplashImage == nullptr) {
        DWORD error = GetLastError();
        OutputDebugStringA("FAILED TO LOAD BMP! Check path and format.\n");
    }
    ShowWindow(m_splashHWnd, SW_SHOW);
    UpdateWindow(m_splashHWnd);
}

void HcWin32Window::DestroyLaunchWindow()
{
    if (m_splashHWnd) {
        DestroyWindow(m_splashHWnd);
        m_splashHWnd = nullptr;
    }
}

void HcWin32Window::RegisterWindowClass(HINSTANCE hInstance) {
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = HcWin32Window::WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "HeliconWindowClass";

    RegisterClassExA(&wc);
}