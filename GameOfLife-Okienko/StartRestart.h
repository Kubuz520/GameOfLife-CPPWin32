#pragma once

#include <Windows.h>
#include "PlanszaGry.h"
#include "Information.h"

// Funkcja startująca grę
bool StartGame(HWND Enter_Button, HWND Restart_Button, HWND Time_Edit, HWND Time_Text, HWND Clear_Button, HWND Stop_Button, HWND Generation_Counter, HWND UI_Panel, HWND Game_Panel,
    HWND checkboxes[amount_width * amount_height], Plansza* plansza, int blocks[], int ilosc);
// Funkcja restartująca grę
bool RestartGame(HWND Enter_Button, HWND Restart_Button, HWND Time_Edit, HWND Time_Text, HWND Clear_Button, HWND Stop_Button, HWND Generation_Counter, HWND UI_Panel, HWND Game_Panel,
    HWND checkboxes[amount_width * amount_height], Plansza* plansza, int* Generation);
