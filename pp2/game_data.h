// Plik zawieraj�cy definicj� podstawowych struktur gry

#pragma once // zapewnienie �e dany plik nag��wkowy b�dzie za��czony tylko raz

// za�adowanie biblioteki allegro i jej modu��w
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// struktura zawieraj�ca podstawow� konfiguracj� gry
struct config {
    unsigned short int width;           // szeroko�� okna gry
    unsigned short int height;          // wysoko�� okna gry
    unsigned short int font_size;       // wysoko�� okna gry
    unsigned short int fps;             // liczba klatek/s
    int board_x_size;					// maksymalna ilo�� klock�w na osi X
    int board_y_size;					// maksymalna ilo�� klock�w na osi Y
    int board_node_size;				// wielko�� klocka (px)
    int board_gap;						// wielko�� przerwy mi�dzy klockami (10px)
    int node_min_interpolation;
    int node_max_interpolation;
    unsigned char node_min_color_r;
    unsigned char node_min_color_g;
    unsigned char node_min_color_b;
    unsigned char node_max_color_r;
    unsigned char node_max_color_g;
    unsigned char node_max_color_b;
};

// struktura zawieraj�ca g��wne zmienne okna gry
struct game_window {
    bool game_initialized;                      // czy gra zosta�a zainicjowana poprawnie
    bool keyboard_initialized;                  // czy gra posiada zainicjowan� klawiatur�
    bool primitive_shapes_addon_initialized;    // czy modu� z podstawowymi kszta�tami zosta� zainicjowany
    bool font_addon_initialized;                // czy modu� z czcionk� zosta� zainicjowany
    bool ttf_addon_initialized;                 // czy modu� z plikami .ttf zosta� zainicjowany
    ALLEGRO_DISPLAY* display;                   // okno gry
    ALLEGRO_EVENT_QUEUE* queue;                 // kolejka gry
    ALLEGRO_FONT* font;                         // czcionka okna
    ALLEGRO_TIMER* timer;                       // licznik klatek gry
};