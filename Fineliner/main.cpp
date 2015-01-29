#include <windows.h>
#include "game.hpp"

const LPCTSTR WindowClassName = "Fineliner";
const LPCTSTR WindowCaption = "Fineliner";

const int WindowLeft = 100;
const int WindowTop = 100;
const int WindowWidth = 800;
const int WindowHeight = 600;

const int UpdateInterval = 50; // [ms]
const int MY_ID_TIMER = 101;

HWND hWnd;
Game* game;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/// main
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    WNDCLASSEX wndClassEx;

    wndClassEx.cbSize = sizeof(WNDCLASSEX);
    wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
    wndClassEx.lpfnWndProc = WndProc;
    wndClassEx.cbClsExtra = 0;
    wndClassEx.cbWndExtra = 0;
    wndClassEx.hInstance = hInstance;
    wndClassEx.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClassEx.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndClassEx.lpszMenuName = NULL;
    wndClassEx.lpszClassName = WindowClassName;
    wndClassEx.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    RegisterClassEx(&wndClassEx);

    hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, WindowClassName, WindowCaption,
    WS_OVERLAPPEDWINDOW, WindowLeft, WindowTop, WindowWidth, WindowHeight,
    NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while ( GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;
    switch (msg) {
        case WM_CREATE:
            hdc = GetDC(hWnd);
            game = new Game(hdc);
            game->Initialize();
            SetTimer(hWnd, MY_ID_TIMER, UpdateInterval, NULL);
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            game->Render(hdc);
            EndPaint(hWnd, &ps);
            break;
        case WM_TIMER:
            game->Update();
            InvalidateRect(hWnd, NULL, FALSE);
            break;
        case WM_KEYDOWN:
            switch (wParam) {
                case 65: // A
                    game->Steer(1, dir2::Left());
                    break;
                case 68: // D
                    game->Steer(1, dir2::Right());
                    break;
                case 83: // S
                    game->Steer(1, dir2::Down());
                    break;
                case 87: // W
                    game->Steer(1, dir2::Up());
                    break;
                case VK_TAB:
                    game->Jump(1);
                    break;
                case VK_LEFT:
                    game->Steer(0, dir2::Left());
                    break;
                case VK_RIGHT:
                    game->Steer(0, dir2::Right());
                    break;
                case VK_DOWN:
                    game->Steer(0, dir2::Down());
                    break;
                case VK_UP:
                    game->Steer(0, dir2::Up());
                    break;
                case VK_CONTROL:
                    game->Jump(0);
                    break;
                case VK_F7:
                    game->Stop(0);
                    break;
                case VK_F8:
                    game->Stop(1);
                    break;
                case VK_ESCAPE:
                    DestroyWindow(hWnd);
                    break;
            }
            break;
        case WM_DESTROY:
            delete game;
            PostQuitMessage(WM_QUIT);
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
