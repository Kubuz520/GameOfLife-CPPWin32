#pragma once

#include "Miejsce.h"
#include "Information.h"

class Plansza {

public:
    Miejsce* (*tablica)[amount_height] = new Miejsce * [amount_width][amount_height];

	// Funckja tworząca planszę i wypełniająca ją pustymi miejscami
    Plansza();

	// Funkcja usuwająca wszystkie bloki z planszy i ustawiająca je na puste
    void Reset();

	// Funkcja pokazująca planszę w konsoli (Debug)
    void Show();

    // Funkcje wywołujące liczenie sąsiadów wszystkich miejsc w planszy oraz
	// Wywołującą funkcje Play() dla wszystkich miejsc w planszy która albo 
    // Ustawi dane miejsce na puste lub pełne
    void AllNeighbours();
    void AllPlay();
    
    //Funkcje do dodawania i usuwania bloków z planszy
    void AddBlock(int w, int s);
    void RemoveBlock(int w, int s);
    void AddBlocks(int cords[], int ilosc);

};