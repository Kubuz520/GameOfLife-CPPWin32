#pragma once

#include "Type.h"
#include "Information.h"

// Stworzenie klasy Miejsce która będzie reprezentować pojedyncze pole na planszy
class Miejsce {

protected:

    int neighbours{};
    char type{};
    int wys{};
    int szer{};

public:
    char GetTile() {
        return type;
    }

    // Funkcja oznaczająca co ma zrobić dany element planszy
    virtual void Play(Miejsce* tablica[][amount_height]) = 0;
    
    // Odpowiednio funkcje do usuwania i pojawiania się bloków w planszy
    void Usuniecie(Miejsce* tablica[][amount_height], int w, int s);
    void Pojawienie(Miejsce* tablica[][amount_height], int w, int s);

	// Funkcja licząca ilość sąsiadów danego miejsca, która będzie potrzebna do określenia czy miejsce ma się pojawić lub zniknąć
    void Neighbours(Miejsce* tablica[][amount_height]) {
        neighbours = 0;

        if (szer > 0 && szer < amount_height - 1 && wys > 0 && wys < amount_width - 1) {
            // Szerokosc
            if (tablica[wys][szer + 1]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            if (tablica[wys][szer - 1]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            // Wysokosc
            if (tablica[wys + 1][szer]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            if (tablica[wys - 1][szer]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            // Skosy
            if (tablica[wys + 1][szer + 1]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            if (tablica[wys + 1][szer - 1]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            if (tablica[wys - 1][szer + 1]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
            if (tablica[wys - 1][szer - 1]->GetTile() == GetType(Type::X)) {
                neighbours += 1;
            }
        }


    }

};

// Podklasa Puste oznaczająca puste miejsce
class Puste : public Miejsce {

public:
    Puste(int w, int s) {
        type = GetType(Type::O);
        wys = w;
        szer = s;
    }
    void Play(Miejsce* tablica[][amount_height]) {
        if (neighbours == 3) {
            Pojawienie(tablica, wys, szer);
        }
    }

};

// Podklasa Pełne oznaczająca pełne miejsce
class Pelne : public Miejsce {
public:
    Pelne(int w, int s) {
        type = GetType(Type::X);
        wys = w;
        szer = s;
    }
    void Play(Miejsce* tablica[][amount_height]) {
        if (neighbours > 3 || neighbours < 2) {
            Usuniecie(tablica, wys, szer);
        }
    }
};

// Deklaracji funkcji potrzebnych do usuwania i pojawiania się bloków
void Miejsce::Usuniecie(Miejsce* tablica[][amount_height], int w, int s) {
    delete tablica[w][s];
    tablica[w][s] = new Puste(w, s);
}
void Miejsce::Pojawienie(Miejsce* tablica[][amount_height], int w, int s) {
    delete tablica[w][s];
    tablica[w][s] = new Pelne(w, s);
}
