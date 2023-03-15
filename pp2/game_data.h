// Plik zawieraj�cy definicj� podstawowych struktur gry

#pragma once // zapewnienie �e dany plik nag��wkowy b�dzie za��czony tylko raz

// za�adowanie biblioteki allegro i jej modu��w
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// struktura zawieraj�ca podstawow� konfiguracj� gry
struct config {
    unsigned short int width;   // szeroko�� okna gry
    unsigned short int height;  // wysoko�� okna gry
    unsigned short int fps;     // liczba klatek/s
};

// struktura zawieraj�ca g��wne zmienne okna gry
struct game_window {
    bool gameInitialized;       // czy gra zosta�a zainicjowana poprawnie
    bool keyboardInitialized;   // czy gra posiada zainicjowan� klawiatur�
    ALLEGRO_DISPLAY* display;   // okno gry
    ALLEGRO_EVENT_QUEUE* queue; // kolejka gry
    ALLEGRO_FONT* font;         // czcionka okna
    ALLEGRO_TIMER* timer;       // licznik klatek gry
};