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
	10		// wielko�� przerwy mi�dzy klockami (10px)
};

struct game_window game;