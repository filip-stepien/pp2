// Plik zawieraj�cy deklaracj� struktur zdefiniowanych w game_data.h

#include "game_data.h"

struct config cfg = { 
	800,	// szeroko�� okna
	600,	// wysoko�� okna
	24,		// wielko�� czcionki
	30,		// fps
	4,		// maksymalna ilo�� klock�w na osi X
	4,		// maksymalna ilo�� klock�w na osi Y
	100,	// wielko�� klocka (px)
	10,		// wielko�� przerwy mi�dzy klockami (10px)
	2,		// minimalna warto�� dla kt�rej obliczany jest gradient koloru
	2048,	// maksymalna warto�� dla kt�rej obliczany jest gradient koloru
	250,	// warto�� minimalna gradientu (r)
	250,	// warto�� minimalna gradientu (g)
	0,		// warto�� minimalna gradientu (b)
	255,	// warto�� maksymalna gradientu (r)
	0,		// warto�� maksymalna gradientu (g)
	120		// warto�� maksymalna gradientu (b)
};

struct game_window game;