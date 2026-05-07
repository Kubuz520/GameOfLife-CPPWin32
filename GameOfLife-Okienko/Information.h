#pragma once

// szerokosc i wysokosc ekranu
const int width = 1800;
const int height = 1000;

// Ilosc Miejsca w tablicach
const int amount_width = 92;
const int amount_height = 50;

// Szerokosc i wysokosc pojedynczego bloku
const int block_width = width / amount_width;
const int block_height = height / amount_height;

// Informacja o tym czy gra się rozpoczeła
bool GameStarted{false};



