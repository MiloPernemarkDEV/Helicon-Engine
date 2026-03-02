#include "HcWin32Window.h"

bool HcWin32Window::Initialize(HINSTANCE hInstance, int width, int height, const char* title)
{
    m_hInstance = hInstance;

    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = HcWin32Window::WndProc;
    wc.hInstance = m_hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = "HeliconWindowClass";

    if (!RegisterClassExA(&wc))
        return false;

    DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    RECT rect{ 0, 0, width, height };
    AdjustWindowRect(&rect, style, FALSE);

    m_hWnd = CreateWindowExA(
        0,
        wc.lpszClassName,
        title,
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        m_hInstance,
        this // lpParam -> we attach 'this' in WM_NCCREATE
    );

    if (!m_hWnd)
        return false;

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
        window->m_hWnd = hWnd;
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
            window->m_shouldClose = true;
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}