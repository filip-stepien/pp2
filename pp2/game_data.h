// Plik zawieraj¹cy definicjê podstawowych struktur gry

#pragma once // zapewnienie ¿e dany plik nag³ówkowy bêdzie za³¹czony tylko raz

// za³adowanie biblioteki allegro i jej modu³ów
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// struktura zawieraj¹ca podstawow¹ konfiguracjê gry
struct config {
    unsigned short int width;           // szerokoœæ okna gry
    unsigned short int height;          // wysokoœæ okna gry
    unsigned short int font_size;       // wysokoœæ okna gry
    unsigned short int fps;             // liczba klatek/s
    int board_x_size;					// maksymalna iloœæ klocków na osi X
    int board_y_size;					// maksymalna iloœæ klocków na osi Y
    int board_node_size;				// wielkoœæ klocka (px)
    int board_gap;						// wielkoœæ przerwy miêdzy klockami (10px)
    int node_min_interpolation;
    int node_max_interpolation;
    unsigned char node_min_color_r;
    unsigned char node_min_color_g;
    unsigned char node_min_color_b;
    unsigned char node_max_color_r;
    unsigned char node_max_color_g;
    unsigned char node_max_color_b;
};

// struktura zawieraj¹ca g³ówne zmienne okna gry
struct game_window {
    bool game_initialized;                      // czy gra zosta³a zainicjowana poprawnie
    bool keyboard_initialized;                  // czy gra posiada zainicjowan¹ klawiaturê
    bool primitive_shapes_addon_initialized;    // czy modu³ z podstawowymi kszta³tami zosta³ zainicjowany
    bool font_addon_initialized;                // czy modu³ z czcionk¹ zosta³ zainicjowany
    bool ttf_addon_initialized;                 // czy modu³ z plikami .ttf zosta³ zainicjowany
    ALLEGRO_DISPLAY* display;                   // okno gry
    ALLEGRO_EVENT_QUEUE* queue;                 // kolejka gry
    ALLEGRO_FONT* font;                         // czcionka okna
    ALLEGRO_TIMER* timer;                       // licznik klatek gry
};