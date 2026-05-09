#pragma once

#include "Information.h"
#include "Type.h"

// Stworzenie klasy Miejsce która będzie reprezentować pojedyncze pole na planszy
class Miejsce {

protected:

    int neighbours{};
    char type{};
    int wys{};
    int szer{};

public:
    char GetTile();

    // Funkcja oznaczająca co ma zrobić dany element planszy
    virtual void Play(Miejsce* tablica[][amount_height]) = 0;
    
    // Odpowiednio funkcje do usuwania i pojawiania się bloków w planszy
    void Usuniecie(Miejsce* tablica[][amount_height], int w, int s);
    void Pojawienie(Miejsce* tablica[][amount_height], int w, int s);

	// Funkcja licząca ilość sąsiadów danego miejsca, która będzie potrzebna do określenia czy miejsce ma się pojawić lub zniknąć
    void Neighbours(Miejsce* tablica[][amount_height]);

};

// Podklasa Puste oznaczająca puste miejsce
class Puste : public Miejsce {

public:
    Puste(int w, int s);
    void Play(Miejsce* tablica[][amount_height]);

};

// Podklasa Pełne oznaczająca pełne miejsce
class Pelne : public Miejsce {

    public:
    Pelne(int w, int s);
    void Play(Miejsce* tablica[][amount_height]);
};
