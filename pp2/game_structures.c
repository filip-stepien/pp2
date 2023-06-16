/**
 * @file game_structures.c
 * @brief Podstawowe struktury gry
 */

#include "game_includes.h"
#include "game_structures.h"

 //! Konfiguracja gry
struct config cfg = { 
	600,
	800,
	"Arial.ttf",
	"restart_button.png",
	"menu_button.png",
	{ "mute_button_on.png", "mute_button_off.png"},
	"music.wav",
	{ "slide1.wav", "slide2.wav", "slide3.wav" },
	{ "grow1.wav", "grow2.wav", "grow3.wav" },
	3, 
	3,
	0.2,
	0.1,
	24,				
	100,
	40,
	20,				
	10,				
	60,				
	4,				
	4,				
	100,			
	10,				
	200,			
	100,			
	200,			
	100,			
	60,
	60,
	6,
	300,
	80,
	10,
	20,
	50,
	50,
	560,
	280,
	20,
	70, 70, 70, 130,
	255, 230, 208,
	255, 255, 255,
	255, 255, 255,
	60,
	60,
	6,
	255, 255, 255,
	255, 230, 208,		
	255, 255, 255,	
	255, 255, 255,		
	50, 50, 50,		
	50, 50, 50,		
	50, 50, 50,
	50, 50, 50,
	50, 50, 50,
	255, 255, 255,
	50, 50, 50,
	2,				
	2048,			
	250, 250, 0,	
	255, 0 , 120,	
	16,				
	50,				
	10,
	30,
	255, 230, 208
};

//! Dźwięki
struct sounds sounds;

//! Zmienne gry
struct game_window game;

//! Plansza
struct game_board board;

//! Wynik
struct game_points points;

//! Najlepszy wynik
struct game_points best_points;

//! Animacje
struct game_animations animations;

//! Okno menu
struct popup menu;

//! Okno końca gry
struct popup end;

//! Przycisk menu
struct button menu_button;

//! Przycisk restart
struct button restart_button;

//! Przycisk planszy 4x4
struct button button_4x4;

//! Przycisk planszy 5x5
struct button button_5x5;

//! Przycisk planszy 6x6
struct button button_6x6;

//! Przycisk powrotu
struct button back;

//! Przycisk wyciszenia dźwięków
struct button mute;

//! Przycisk nowej gry
struct button new_game;

//! Przyciski interfejsu
struct button* ui_buttons[3] = { 
	&menu_button,
	&restart_button,
	&mute
};

//! Ilość przycisków interfejsu
int ui_buttons_length = 3;