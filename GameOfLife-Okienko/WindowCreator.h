#pragma once

#include <Windows.h>
#include "Information.h"

void CreateWindows(HWND hwnd, HWND UI_Panel, HWND Game_Panel, HINSTANCE hInstance, const wchar_t UI_nazwa[], const wchar_t Game_nazwa[]) {

    // Tworzenie Panelu UI i Panelu z checkboxami
    UI_Panel = CreateWindowEx(
        0,
        UI_nazwa,
        NULL,
        WS_CHILD | WS_VISIBLE,
        0, height - 200, width, 200,
        hwnd,
        NULL,
        hInstance,
        NULL
    );
    Game_Panel = CreateWindowEx(
        0,
        Game_nazwa,
        NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0, width, height - 200,
        hwnd,
        NULL,
        hInstance,
        NULL
    );
}