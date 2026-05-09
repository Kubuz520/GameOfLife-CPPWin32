#pragma once

#include "PlanszaGry.h"
#include <Windows.h>

// Funkcja rysująca plansze podczas gdy gra jest uruchomiona
void GamePlaying(HDC hdc, HBRUSH pelne, HBRUSH puste, Plansza plansza, int* Population);
