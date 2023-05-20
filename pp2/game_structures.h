// Plik zawieraj�cy definicj� podstawowych struktur gry

#pragma once // zapewnienie �e dany plik nag��wkowy b�dzie za��czony tylko raz
#include "game_includes.h"

#include <stdio.h>

// struktura zawieraj�ca podstawow� konfiguracj� gry
struct config {
    int width;                              // szeroko�� okna gry
    int height;                             // wysoko�� okna gry
    char* font_name;
    char* restart_button_filename;
    char* menu_button_filename;
    char* mute_button_filenames[2];
    int font_size;                          // wielko�� czcionki
    int title_font_size;
    int option_font_size;
    int points_font_size;                   // wielko�� czcionki z punktami
    int points_text_leading;                // interlinia licznik�w punkt�w   
    int fps;                                // liczba klatek/s
    int board_x_size;					    // maksymalna ilo�� klock�w na osi X
    int board_y_size;					    // maksymalna ilo�� klock�w na osi Y
    int board_node_size;				    // wielko�� klocka (px)
    int board_gap;						    // wielko�� przerwy mi�dzy klockami (10px)
    int points_width;                       // szeroko�� licznika punkt�w
    int points_height;                      // wysoko�� licznika punkt�w
    int best_points_width;                  // szeroko�� licznika najlepszego wyniku
    int best_points_height;                 // wysoko�� licznika najlepszego wyniku
    int restart_button_width;
    int restart_button_height;
    int restart_button_img_padding;
    int option_width;
    int option_height;
    int option_padding;
    int option_gap;
    int mute_button_width;
    int mute_button_height;
    unsigned char mute_button_bg_color_r;
    unsigned char mute_button_bg_color_g;
    unsigned char mute_button_bg_color_b;
    unsigned char option_bg_color_r;
    unsigned char option_bg_color_g;
    unsigned char option_bg_color_b;
    unsigned char restart_button_bg_color_r;
    unsigned char restart_button_bg_color_g;
    unsigned char restart_button_bg_color_b;
    int menu_button_width;
    int menu_button_height;
    int menu_button_img_padding;
    unsigned char menu_button_bg_color_r;
    unsigned char menu_button_bg_color_g;
    unsigned char menu_button_bg_color_b;
    unsigned char bg_color_r;               // kolor t�a (r)
    unsigned char bg_color_g;               // kolor t�a (g)
    unsigned char bg_color_b;               // kolor t�a (b)
    unsigned char points_bg_color_r;        // kolor t�a licznika (r)
    unsigned char points_bg_color_g;        // kolor t�a licznika (g)
    unsigned char points_bg_color_b;        // kolor t�a licznika (b)
    unsigned char default_node_color_r;     // kolor klocka bez warto�ci (r)
    unsigned char default_node_color_g;     // kolor klocka bez warto�ci (g)
    unsigned char default_node_color_b;     // kolor klocka bez warto�ci (b)
    unsigned char points_text_color_r;      // kolor tekstu licznika (r)
    unsigned char points_text_color_g;      // kolor tekstu licznika (g)
    unsigned char points_text_color_b;      // kolor tekstu licznika (b)
    unsigned char node_text_color_r;        // kolor tekstu klocka (r)
    unsigned char node_text_color_g;        // kolor tekstu klocka (g)
    unsigned char node_text_color_b;        // kolor tekstu klocka (b)
    unsigned char title_text_color_r;       
    unsigned char title_text_color_g;       
    unsigned char title_text_color_b;    
    unsigned char option_text_color_r;
    unsigned char option_text_color_g;
    unsigned char option_text_color_b;
    int node_min_interpolation;             // minimalna warto�� dla kt�rej obliczany jest gradient koloru
    int node_max_interpolation;             // maksymalna warto�� dla kt�rej obliczany jest gradient koloru
    unsigned char node_min_color_r;         // warto�� minimalna gradientu (r)
    unsigned char node_min_color_g;         // warto�� minimalna gradientu (g)
    unsigned char node_min_color_b;         // warto�� minimalna gradientu (b)
    unsigned char node_max_color_r;         // warto�� maksymalna gradientu (r)
    unsigned char node_max_color_g;         // warto�� maksymalna gradientu (g)
    unsigned char node_max_color_b;         // warto�� maksymalna gradientu (b)
    int grow_animation_duration;            // d�ugo�� animacjki tworzenia klocka (klatki)
    int slide_animation_speed;              // szybko�� animacji przesuwania klock�w (klatki/s)
    int move_cooldown;                      // co jaki czas mo�na wykona� ruch (klatki)
    int click_cooldown;
    unsigned char menu_bg_color_r;
    unsigned char menu_bg_color_g;
    unsigned char menu_bg_color_b;
};

extern struct config cfg;


// struktura zawieraj�ca g��wne zmienne okna gry
struct game_window {
    bool game_initialized;                      // czy gra zosta�a zainicjowana poprawnie
    bool keyboard_initialized;                  // czy gra posiada zainicjowan� klawiatur�
    bool primitive_shapes_addon_initialized;    // czy modu� z podstawowymi kszta�tami zosta� zainicjowany
    bool font_addon_initialized;                // czy modu� z czcionk� zosta� zainicjowany
    bool ttf_addon_initialized;                 // czy modu� z plikami .ttf zosta� zainicjowany
    bool image_addon_initialized;
    bool mouse_initialized;
    bool started;
    bool muted;
    ALLEGRO_DISPLAY* display;                   // okno gry
    ALLEGRO_EVENT_QUEUE* queue;                 // kolejka gry
    ALLEGRO_FONT* font;                         // czcionka okna
    ALLEGRO_FONT* points_font;                  // czcionka dla punkt�w
    ALLEGRO_FONT* title_font;
    ALLEGRO_FONT* option_font;
    ALLEGRO_TIMER* timer;                       // licznik klatek gry
    struct popup* current_popup;
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
    int total_size;
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
extern struct game_points best_points;

struct button {
    ALLEGRO_BITMAP* img;
    int width;
    int height;
    int top_x;
    int top_y;
    int bottom_x;
    int bottom_y;
    int img_padding;
    ALLEGRO_COLOR bg_color;
    bool visible;
    void (*on_click)();
};

extern struct button menu_button;
extern struct button restart_button;
extern struct button button_4x4;
extern struct button button_5x5;
extern struct button button_6x6;
extern struct button back;
extern struct button mute;

extern struct button* ui_buttons[3];
extern int ui_buttons_length;

struct popup {
    int width;
    int height;
    int top_x;
    int top_y;
    int bottom_x;
    int bottom_y;
    ALLEGRO_COLOR bg_color;
    struct button** buttons;
    int buttons_length;
    bool visible;
};

extern struct popup menu;
extern struct popup yesno;

enum LAST_MOVE { NONE, LEFT, RIGHT, UP, DOWN };

struct game_animations {
    int frame;
    int click_frame;
    int grow_animation_idx;
    struct node* grow_animation_array;
    struct node* slide_animation_array;
    bool done_sliding;
    bool on_cooldown;
    bool click_cooldown;
    enum LAST_MOVE last_move;
};

extern struct game_animations animations;
