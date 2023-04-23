// Plik zawieraj�cy definicj� podstawowych struktur gry

#pragma once // zapewnienie �e dany plik nag��wkowy b�dzie za��czony tylko raz
#include "game_includes.h"

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
    unsigned char bg_color_r;           // kolor t�a (r)
    unsigned char bg_color_g;           // kolor t�a (g)
    unsigned char bg_color_b;           // kolor t�a (b)
    int node_min_interpolation;         // minimalna warto�� dla kt�rej obliczany jest gradient koloru
    int node_max_interpolation;         // maksymalna warto�� dla kt�rej obliczany jest gradient koloru
    unsigned char node_min_color_r;     // warto�� minimalna gradientu (r)
    unsigned char node_min_color_g;     // warto�� minimalna gradientu (g)
    unsigned char node_min_color_b;     // warto�� minimalna gradientu (b)
    unsigned char node_max_color_r;     // warto�� maksymalna gradientu (r)
    unsigned char node_max_color_g;     // warto�� maksymalna gradientu (g)
    unsigned char node_max_color_b;     // warto�� maksymalna gradientu (b)
};

extern struct config cfg;

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

extern struct game_window game;

// struktura reprezentuj�ca klocek planszy
struct node {
    int value;				// warto��, jak� przechowuje klocek (2, 4, 8, 16, 32...)
    int top_x;				// koordynata X klocka w lewym g�rnym rogu (px)
    int top_y;				// koordynata Y klocka w lewym g�rnym rogu (px)
    int bottom_x;			// koordynata X klocka w prawym dolnym rogu (px)
    int bottom_y;			// koordynata Y klocka w prawym dolnym rogu (px)
    int size;				// wielko�� boku klocka (px)
    ALLEGRO_COLOR color;	// kolor klocka
};

// struktura zawieraj�ce zmienne planszy gry
struct game_board {
    int x_size;						// maksymalna ilo�� klock�w na osi X 
    int y_size;						// maksymalna ilo�� klock�w na osi Y
    int node_size;					// wielko�� klocka (px)
    int gap;						// wielko�� przerwy mi�dzy klockami (10px)
    bool first_turn;                // informacja, czy aktualna tura jest pierwsza
    struct node** prev_board_array; // poprzedni stan planszy
    struct node** board_array;		// plansza z klockami
};

extern struct game_board board;

// struktura ze zmiennymi tabeli punktowej
struct game_points {
    int counter;    // licznik wyniku
    int width;      // szeroko�� tabeli punktowej (px)
    int height;     // wysoko�� tabeli punktowej (px)
    int top_x;      // koordynata X lewego g�rnego rogu tabeli punktowej (px)
    int top_y;      // koordynata Y lewego g�rnego rogu tabeli punktowej (px)
    int bottom_x;   // koordynata X prawego dolnego rogu tabeli punktowej (px)
    int bottom_y;   // koordynata Y prawego dolnego rogu tabeli punktowej (px)
};

extern struct game_points points;