#pragma once

#include "Miejsce.h"
#include "Information.h"
#include <iostream>

class Plansza {

public:
    Miejsce* (*tablica)[amount_height] = new Miejsce * [amount_width][amount_height];

	// Funckja tworząca planszę i wypełniająca ją pustymi miejscami
    Plansza() {
        for (int i = 0; i < amount_width; i++) {
            for (int j = 0; j < amount_height; j++) {
                tablica[i][j] = new Puste(i, j);
            }
        }
    }

	// Funkcja usuwająca wszystkie bloki z planszy i ustawiająca je na puste
    void Reset() {
        for (int i = 0; i < amount_width; i++) {
            for (int j = 0; j < amount_height; j++) {
                delete tablica[i][j];
                tablica[i][j] = new Puste(i, j);
            }
        }
	}

    void Show() {
        for (int i = 0; i < amount_width; i++) {
            std::cout << "\n";
            for (int j = 0; j < amount_height; j++) {
                printf("%c", tablica[i][j]->GetTile());
            }
        }
    }

    // Funkcje wywołujące liczenie sąsiadów wszystkich miejsc w planszy oraz
	// Wywołującą funkcje Play() dla wszystkich miejsc w planszy która albo 
    // Ustawi dane miejsce na puste lub pełne
    void AllNeighbours() {
        for (int i = 0; i < amount_width; i++) {
            for (int j = 0; j < amount_height; j++) {
                tablica[i][j]->Neighbours(tablica);
            }
        }
    }
    void AllPlay() {
        for (int i = 0; i < amount_width; i++) {
            for (int j = 0; j < amount_height; j++) {
                tablica[i][j]->Play(tablica);
            }
        }
    }
    
    //Funkcje do dodawania i usuwania bloków z planszy
    void AddBlock(int w, int s) {
        delete tablica[w][s];
        tablica[w][s] = new Pelne(w, s);
    }
    void RemoveBlock(int w, int s) {
        delete tablica[w][s];
        tablica[w][s] = new Puste(w, s);
	}
    void AddBlocks(int cords[], int ilosc) {
        for (int i{ 0 };i < ilosc;i++) {
            AddBlock(cords[i] / amount_height, cords[i] % amount_height);
        }
    }

};