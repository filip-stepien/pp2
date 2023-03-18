// Plik zawieraj¹cy definicjê podstawowych struktur gry

#pragma once // zapewnienie ¿e dany plik nag³ówkowy bêdzie za³¹czony tylko raz

// za³adowanie biblioteki allegro i jej modu³ów
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// struktura zawieraj¹ca podstawow¹ konfiguracjê gry
struct config {
    unsigned short int width;   // szerokoœæ okna gry
    unsigned short int height;  // wysokoœæ okna gry
    unsigned short int fps;     // liczba klatek/s
};

// struktura zawieraj¹ca g³ówne zmienne okna gry
struct game_window {
    bool gameInitialized;       // czy gra zosta³a zainicjowana poprawnie
    bool keyboardInitialized;   // czy gra posiada zainicjowan¹ klawiaturê
    ALLEGRO_DISPLAY* display;   // okno gry
    ALLEGRO_EVENT_QUEUE* queue; // kolejka gry
    ALLEGRO_FONT* font;         // czcionka okna
    ALLEGRO_TIMER* timer;       // licznik klatek gry
};