#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;
    HDC hDC;

    switch (message) {
    case WM_PAINT:
        hDC = BeginPaint(hwnd, &paintStruct);
        EndPaint(hwnd, &paintStruct);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE prevInstance,
                    LPWSTR cmdLine,
                    int cmdShow)
{
    UNREFERENCED_PARAMETER(prevInstance);
    UNREFERENCED_PARAMETER(cmdLine);

    WNDCLASSEX wndClass = { 0 };
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = L"DX11BookWindowClass";

    if (!RegisterClassEx(&wndClass)) {
        return -1;
    }

    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindow(L"DX11BookWindowClass",
                             L"Blank Win32 Window",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             rc.right - rc.left,
                             rc.bottom - rc.top,
                             NULL,
                             NULL,
                             hInstance,
                             NULL);

    if (!hwnd) return -1;

    ShowWindow(hwnd, cmdShow);

    MSG msg = { 0 };

    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

        }
    }

    return static_cast<int>(msg.wParam);
}