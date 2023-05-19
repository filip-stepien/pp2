// Plik zawieraj�cy deklaracj� struktur zdefiniowanych w game_data.h

#include "game_includes.h"
#include "game_structures.h"

struct config cfg = { 
	600,			// szeroko�� okna
	800,			// wysoko�� okna
	"Arial.ttf",
	24,				// wielko�� czcionki
	100,
	40,
	20,				// wielko�� czcionki licznik�w punkt�w
	10,				// interlinia licznik�w punkt�w
	60,				// fps
	4,				// maksymalna ilo�� klock�w na osi X
	4,				// maksymalna ilo�� klock�w na osi Y
	100,			// wielko�� klocka (px)
	10,				// wielko�� przerwy mi�dzy klockami (10px)
	200,			// szeroko�� licznika punkt�w
	100,			// wysoko�� licznika punkt�w
	200,			// szeroko�� licznika najlepszego wyniku
	100,			// wysoko�� licznika najlepszego wyniku
	60,
	60,
	10,
	300,
	100,
	10,
	20,
	255, 255, 255,
	255, 255, 255,
	60,
	60,
	10,
	255, 255, 255,
	0, 0, 0,		// kolor t�a (r, g, b)
	255, 255, 255,	// kolor t�a licznika (r, g, b)
	0, 0, 0,		// kolor klocka bez warto�ci (r, g, b)
	0, 0, 0,		// kolor tekstu licznika (r, g, b)
	0, 0, 0,		// kolor tekstu klocka (r, g, b)
	255, 255, 255,
	0, 0, 0,
	2,				// minimalna warto�� dla kt�rej obliczany jest gradient koloru
	2048,			// maksymalna warto�� dla kt�rej obliczany jest gradient koloru
	250, 250, 0,	// warto�� minimalna gradientu (r, g, b)
	255, 0 , 120,	// warto�� maksymalna gradientu (r, g, b)
	10,				// d�ugo�� animacjki tworzenia klocka (klatki)
	50,				// szybko�� animacji przesuwania klock�w (klatki/s)
	10,
	255,
	189,
	132
};

struct game_window game;
struct game_board board;
struct game_points points;
struct game_points best_points;
struct game_animations animations;
struct popup menu;
struct popup yesno;

struct button menu_button;
struct button restart_button;
struct button button_4x4;
struct button button_5x5;
struct button button_6x6;
struct button start;
struct button back;
struct button mute;
struct button yes;
struct button no;

struct button* buttons[10] = { 
	&menu_button,
	&restart_button,
	&button_4x4,
	&button_5x5,
	&button_6x6,
	&start,
	&back,
	&mute,
	&yes,
	&no
};
int buttons_length = 10;