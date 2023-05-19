// Plik zawieraj¹cy deklaracjê struktur zdefiniowanych w game_data.h

#include "game_includes.h"
#include "game_structures.h"

struct config cfg = { 
	600,			// szerokoœæ okna
	800,			// wysokoœæ okna
	"Arial.ttf",
	24,				// wielkoœæ czcionki
	100,
	40,
	20,				// wielkoœæ czcionki liczników punktów
	10,				// interlinia liczników punktów
	60,				// fps
	4,				// maksymalna iloœæ klocków na osi X
	4,				// maksymalna iloœæ klocków na osi Y
	100,			// wielkoœæ klocka (px)
	10,				// wielkoœæ przerwy miêdzy klockami (10px)
	200,			// szerokoœæ licznika punktów
	100,			// wysokoœæ licznika punktów
	200,			// szerokoœæ licznika najlepszego wyniku
	100,			// wysokoœæ licznika najlepszego wyniku
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
	0, 0, 0,		// kolor t³a (r, g, b)
	255, 255, 255,	// kolor t³a licznika (r, g, b)
	0, 0, 0,		// kolor klocka bez wartoœci (r, g, b)
	0, 0, 0,		// kolor tekstu licznika (r, g, b)
	0, 0, 0,		// kolor tekstu klocka (r, g, b)
	255, 255, 255,
	0, 0, 0,
	2,				// minimalna wartoœæ dla której obliczany jest gradient koloru
	2048,			// maksymalna wartoœæ dla której obliczany jest gradient koloru
	250, 250, 0,	// wartoœæ minimalna gradientu (r, g, b)
	255, 0 , 120,	// wartoœæ maksymalna gradientu (r, g, b)
	10,				// d³ugoœæ animacjki tworzenia klocka (klatki)
	50,				// szybkoœæ animacji przesuwania klocków (klatki/s)
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

struct button* ui_buttons[2] = { 
	&menu_button,
	&restart_button
};
int ui_buttons_length = 2;