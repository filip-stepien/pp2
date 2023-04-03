// Plik zawieraj�cy deklaracj� struktur zdefiniowanych w game_data.h

#include "game_structures.h"

struct config cfg = { 
	450,			// szeroko�� okna
	600,			// wysoko�� okna
	24,				// wielko�� czcionki
	30,				// fps
	4,				// maksymalna ilo�� klock�w na osi X
	4,				// maksymalna ilo�� klock�w na osi Y
	100,			// wielko�� klocka (px)
	10,				// wielko�� przerwy mi�dzy klockami (10px)
	0, 0, 0,		// kolor t�a (r, g, b)
	2,				// minimalna warto�� dla kt�rej obliczany jest gradient koloru
	2048,			// maksymalna warto�� dla kt�rej obliczany jest gradient koloru
	250, 250, 0,	// warto�� minimalna gradientu (r, g, b)
	255, 0 , 120	// warto�� maksymalna gradientu (r,, g, b)
};

struct game_window game;
struct game_board board;
struct game_points points;