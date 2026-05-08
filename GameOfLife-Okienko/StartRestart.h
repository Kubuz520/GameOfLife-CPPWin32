#pragma once

#include <Windows.h>
#include "Information.h"

// Funkcja startująca grę
bool StartGame(HWND Enter_Button, HWND Restart_Button, HWND Time_Edit, HWND Time_Text, HWND Clear_Button, HWND Stop_Button, HWND UI_Panel, HWND Game_Panel,
                HWND checkboxes[amount_width*amount_height], Plansza* plansza, int blocks[], int ilosc) {

    for (int i = 0;i < amount_width; i++) {
        for (int j = 0;j < amount_height;j++) {
            ShowWindow(checkboxes[(i * amount_height) + j], SW_HIDE);
        }
    }
    ShowWindow(Enter_Button, SW_HIDE);
    ShowWindow(Clear_Button, SW_HIDE);
    ShowWindow(Time_Edit, SW_HIDE);
    ShowWindow(Time_Text, SW_HIDE);
    ShowWindow(Restart_Button, SW_SHOW);
    ShowWindow(Stop_Button, SW_SHOW);
    Button_SetText(Stop_Button, L"Stop");
    ShowWindow(Game_Panel, SW_HIDE);
	plansza->AddBlocks(blocks, ilosc);

    return true;

}

// Funkcja restartująca grę
bool RestartGame(HWND Enter_Button, HWND Restart_Button, HWND Time_Edit, HWND Time_Text, HWND Clear_Button, HWND Stop_Button, HWND UI_Panel, HWND Game_Panel, 
                HWND checkboxes[amount_width * amount_height], Plansza* plansza) {

    for (int i = 0;i < amount_width; i++) {
        for (int j = 0;j < amount_height;j++) {
            ShowWindow(checkboxes[(i * amount_height) + j], SW_SHOW);
        }
    }
    ShowWindow(Enter_Button, SW_SHOW);
    ShowWindow(Clear_Button, SW_SHOW);
    ShowWindow(Time_Edit, SW_SHOW);
    ShowWindow(Time_Text, SW_SHOW);
    ShowWindow(Restart_Button, SW_HIDE);
    ShowWindow(Stop_Button, SW_HIDE);
    ShowWindow(Game_Panel, SW_SHOW);
	plansza->Reset();
    return false;

}