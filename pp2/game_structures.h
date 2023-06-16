#pragma once

/**
 * @file game_structures.h
 * @brief Podstawowe struktury gry - deklaracje
 */

#include "game_includes.h"

#include <stdio.h>

//! Struktura zawierająca podstawową konfigurację gry
struct config {
    int width;
    int height;
    char* font_name;
    char* restart_button_filename;
    char* menu_button_filename;
    char* mute_button_filenames[2];
    char* music_filename;
    char* click_sounds_filenames[3];
    char* grow_sounds_filenames[3];
    int click_sounds_length;
    int grow_sounds_length;
    float music_volume;
    float sfx_volume;
    int font_size;
    int title_font_size;
    int option_font_size;
    int points_font_size;
    int points_text_leading;  
    int fps;
    int board_x_size;
    int board_y_size;
    int board_node_size;
    int board_gap;
    int points_width;
    int points_height;
    int best_points_width;
    int best_points_height;
    int restart_button_width;
    int restart_button_height;
    int restart_button_img_padding;
    int option_width;
    int option_height;
    int option_padding;
    int option_gap;
    int mute_button_width;
    int mute_button_height;
    int end_popup_width;
    int end_popup_height;
    int end_popup_padding;
    unsigned char end_bg_color_r;
    unsigned char end_bg_color_g;
    unsigned char end_bg_color_b;
    unsigned char end_bg_color_a;
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
    unsigned char bg_color_r;               
    unsigned char bg_color_g;               
    unsigned char bg_color_b;               
    unsigned char points_bg_color_r;        
    unsigned char points_bg_color_g;        
    unsigned char points_bg_color_b;        
    unsigned char default_node_color_r;     
    unsigned char default_node_color_g;     
    unsigned char default_node_color_b;     
    unsigned char points_text_color_r;      
    unsigned char points_text_color_g;      
    unsigned char points_text_color_b;      
    unsigned char node_text_color_r;        
    unsigned char node_text_color_g;        
    unsigned char node_text_color_b;        
    unsigned char title_text_color_r;       
    unsigned char title_text_color_g;       
    unsigned char title_text_color_b;    
    unsigned char option_text_color_r;
    unsigned char option_text_color_g;
    unsigned char option_text_color_b;
    unsigned char end_title_color_r;
    unsigned char end_title_color_g;
    unsigned char end_title_color_b;
    unsigned char end_button_text_color_r;
    unsigned char end_button_text_color_g;
    unsigned char end_button_text_color_b;
    unsigned char end_button_bg_color_r;
    unsigned char end_button_bg_color_g;
    unsigned char end_button_bg_color_b;
    int node_min_interpolation;             
    int node_max_interpolation;             
    unsigned char node_min_color_r;         
    unsigned char node_min_color_g;        
    unsigned char node_min_color_b;         
    unsigned char node_max_color_r;         
    unsigned char node_max_color_g;         
    unsigned char node_max_color_b;         
    int grow_animation_duration;            
    int slide_animation_speed;              
    int move_cooldown;                      
    int click_cooldown;
    unsigned char menu_bg_color_r;
    unsigned char menu_bg_color_g;
    unsigned char menu_bg_color_b;
};

//! Konfiguracja gry
extern struct config cfg;

//! Struktura zawierająca zmienne dźwięków i muzyki
struct sounds {
    ALLEGRO_SAMPLE_INSTANCE* music;
    ALLEGRO_SAMPLE_INSTANCE** click_sounds;
    ALLEGRO_SAMPLE_INSTANCE** grow_sounds;
    int last_grow_sound;
    int last_click_sound;
};

//! Dźwięki
extern struct sounds sounds;

//! Struktura zawierająca główne zmienne okna gry
struct game_window {
    bool game_initialized;
    bool keyboard_initialized;
    bool primitive_shapes_addon_initialized;    
    bool font_addon_initialized;                
    bool ttf_addon_initialized;                 
    bool image_addon_initialized;
    bool audio_addon_initialized;
    bool acodec_addon_initialized;
    bool mouse_initialized;
    bool started;
    bool muted;
    ALLEGRO_DISPLAY* display;                   
    ALLEGRO_EVENT_QUEUE* queue;                 
    ALLEGRO_FONT* font;                         
    ALLEGRO_FONT* points_font;                  
    ALLEGRO_FONT* title_font;
    ALLEGRO_FONT* option_font;
    ALLEGRO_TIMER* timer;                       
    struct popup* current_popup;
};

//! Zmienne gry
extern struct game_window game;

//! Struktura reprezentująca klocek planszy
struct node {
    int value;
    int top_x;
    int top_y;
    int bottom_x;
    int bottom_y;
    int size;
    ALLEGRO_COLOR color;
};

//! Struktura zawierające zmienne planszy gry
struct game_board {
    int x_size;						
    int y_size;						
    int total_size;
    int node_size;					
    int gap;						
    bool first_turn;                
    struct node** prev_board_array; 
    struct node** board_array;		
};

//! Plansza
extern struct game_board board;

//! Struktura ze zmiennymi tabeli punktowej
struct game_points {
    int counter;    
    int width;      
    int height;     
    int top_x;      
    int top_y;      
    int bottom_x;   
    int bottom_y;   
};

//! Wynik
extern struct game_points points;

//! Najlepszy wynik
extern struct game_points best_points;

//! Struktura reprezentująca przycisk
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

//! Przycisk menu
extern struct button menu_button;

//! Przycisk restart
extern struct button restart_button;

//! Przycisk planszy 4x4
extern struct button button_4x4;

//! Przycisk planszy 5x5
extern struct button button_5x5;

//! Przycisk planszy 6x6
extern struct button button_6x6;

//! Przycisk powrotu
extern struct button back;

//! Przycisk wyciszenia dźwięków
extern struct button mute;

//! Przycisk nowej gry
extern struct button new_game;

//! Przyciski interfejsu
extern struct button* ui_buttons[3];

//! Ilość przycisków interfejsu
extern int ui_buttons_length;

//! Struktura reprezentująca okno gry
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

//! Okno menu
extern struct popup menu;

//! Okno końca gry
extern struct popup end;

//! Enumerator stanowiący prefix dla kierunku ruchu
enum LAST_MOVE { NONE, LEFT, RIGHT, UP, DOWN };

//! Struktura ze zmiennymi dla animacji
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

//! Animacje
extern struct game_animations animations;
