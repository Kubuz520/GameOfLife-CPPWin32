
#include "PlanszaGry.h"

#include "Miejsce.h"
#include "Information.h"
#include <iostream>


// Funckja tworząca planszę i wypełniająca ją pustymi miejscami
Plansza::Plansza() {
    for (int i = 0; i < amount_width; i++) {
        for (int j = 0; j < amount_height; j++) {
            tablica[i][j] = new Puste(i, j);
        }
    }
}

// Funkcja usuwająca wszystkie bloki z planszy i ustawiająca je na puste
void Plansza::Reset() {
    for (int i = 0; i < amount_width; i++) {
        for (int j = 0; j < amount_height; j++) {
            delete tablica[i][j];
            tablica[i][j] = new Puste(i, j);
        }
    }
}

// Funkcja pokazująca planszę w konsoli (Debug)
void Plansza::Show() {
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
void Plansza::AllNeighbours() {
    for (int i = 0; i < amount_width; i++) {
        for (int j = 0; j < amount_height; j++) {
            tablica[i][j]->Neighbours(tablica);
        }
    }
}
void Plansza::AllPlay() {
    for (int i = 0; i < amount_width; i++) {
        for (int j = 0; j < amount_height; j++) {
            tablica[i][j]->Play(tablica);
        }
    }
}

//Funkcje do dodawania i usuwania bloków z planszy
void Plansza::AddBlock(int w, int s) {
    delete tablica[w][s];
    tablica[w][s] = new Pelne(w, s);
}
void Plansza::RemoveBlock(int w, int s) {
    delete tablica[w][s];
    tablica[w][s] = new Puste(w, s);
}
void Plansza::AddBlocks(int cords[], int ilosc) {
    for (int i{ 0 };i < ilosc;i++) {
        AddBlock(cords[i] / amount_height, cords[i] % amount_height);
    }
}
