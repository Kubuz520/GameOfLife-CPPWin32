
#include "Miejsce.h"
#include "Type.h"
#include "Information.h"

char Miejsce::GetTile() {
    return type;
}

// Funkcja licząca ilość sąsiadów danego miejsca, która będzie potrzebna do określenia czy miejsce ma się pojawić lub zniknąć
void Miejsce::Neighbours(Miejsce* tablica[][amount_height]) {
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


// Deklaracji funkcji potrzebnych do usuwania i pojawiania się bloków
void Miejsce::Usuniecie(Miejsce* tablica[][amount_height], int w, int s) {
    delete tablica[w][s];
    tablica[w][s] = new Puste(w, s);
}
void Miejsce::Pojawienie(Miejsce* tablica[][amount_height], int w, int s) {
    delete tablica[w][s];
    tablica[w][s] = new Pelne(w, s);
}



// Funkcje klasy Puste
Puste::Puste(int w, int s) {
    type = GetType(Type::O);
    wys = w;
    szer = s;
}
void Puste::Play(Miejsce* tablica[][amount_height]) {
    if (neighbours == 3) {
        Pojawienie(tablica, wys, szer);
    }
}

// Funkcje klasy Pelne
Pelne::Pelne(int w, int s) {
    type = GetType(Type::X);
    wys = w;
    szer = s;
}
void Pelne::Play(Miejsce* tablica[][amount_height]) {
    if (neighbours > 3 || neighbours < 2) {
        Usuniecie(tablica, wys, szer);
    }
}
