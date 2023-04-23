// Plik zawieraj¹cy definicjê podstawowych struktur gry

#pragma once // zapewnienie ¿e dany plik nag³ówkowy bêdzie za³¹czony tylko raz
#include "game_includes.h"

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
    unsigned char bg_color_r;           // kolor t³a (r)
    unsigned char bg_color_g;           // kolor t³a (g)
    unsigned char bg_color_b;           // kolor t³a (b)
    int node_min_interpolation;         // minimalna wartoœæ dla której obliczany jest gradient koloru
    int node_max_interpolation;         // maksymalna wartoœæ dla której obliczany jest gradient koloru
    unsigned char node_min_color_r;     // wartoœæ minimalna gradientu (r)
    unsigned char node_min_color_g;     // wartoœæ minimalna gradientu (g)
    unsigned char node_min_color_b;     // wartoœæ minimalna gradientu (b)
    unsigned char node_max_color_r;     // wartoœæ maksymalna gradientu (r)
    unsigned char node_max_color_g;     // wartoœæ maksymalna gradientu (g)
    unsigned char node_max_color_b;     // wartoœæ maksymalna gradientu (b)
};

extern struct config cfg;

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

extern struct game_window game;

// struktura reprezentuj¹ca klocek planszy
struct node {
    int value;				// wartoœæ, jak¹ przechowuje klocek (2, 4, 8, 16, 32...)
    int top_x;				// koordynata X klocka w lewym górnym rogu (px)
    int top_y;				// koordynata Y klocka w lewym górnym rogu (px)
    int bottom_x;			// koordynata X klocka w prawym dolnym rogu (px)
    int bottom_y;			// koordynata Y klocka w prawym dolnym rogu (px)
    int size;				// wielkoœæ boku klocka (px)
    ALLEGRO_COLOR color;	// kolor klocka
};

extern struct node;

// struktura zawieraj¹ce zmienne planszy gry
struct game_board {
    int x_size;						// maksymalna iloœæ klocków na osi X 
    int y_size;						// maksymalna iloœæ klocków na osi Y
    int node_size;					// wielkoœæ klocka (px)
    int gap;						// wielkoœæ przerwy miêdzy klockami (10px)
    bool first_turn;                // informacja, czy aktualna tura jest pierwsza
    struct node** prev_board_array; // poprzedni stan planszy
    struct node** board_array;		// plansza z klockami
};

extern struct game_board board;

// struktura ze zmiennymi tabeli punktowej
struct game_points {
    int counter;    // licznik wyniku
    int width;      // szerokoœæ tabeli punktowej (px)
    int height;     // wysokoœæ tabeli punktowej (px)
    int top_x;      // koordynata X lewego górnego rogu tabeli punktowej (px)
    int top_y;      // koordynata Y lewego górnego rogu tabeli punktowej (px)
    int bottom_x;   // koordynata X prawego dolnego rogu tabeli punktowej (px)
    int bottom_y;   // koordynata Y prawego dolnego rogu tabeli punktowej (px)
};

extern struct game_points points;