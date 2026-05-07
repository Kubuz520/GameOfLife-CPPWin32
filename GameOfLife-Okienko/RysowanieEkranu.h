#pragma once

#include <Windows.h>
#include "Information.h"
#include "Type.h"


// Funkcja rysująca plansze podczas gdy gra jest uruchomiona
void GamePlaying(HDC hdc, HBRUSH pelne, HBRUSH puste, Plansza plansza) {
    for (int i = 0;i < amount_width; i++) {
        for (int j = 0;j < amount_height;j++) {
            if (plansza.tablica[i][j]->GetTile() == GetType(Type::O)) {
                RECT rect = { block_width * (i), block_height * (j), block_width * (i + 1), block_height * (j + 1) };
                FillRect(hdc, &rect, puste);
            }
            else {
                RECT rect = { block_width * (i), block_height * (j), block_width * (i + 1), block_height * (j + 1) };
                FillRect(hdc, &rect, pelne);
            }
        }
    }
}
