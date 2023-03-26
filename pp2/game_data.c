// Plik zawieraj¹cy deklaracjê struktur zdefiniowanych w game_data.h

#include "game_data.h"

struct config cfg = { 
	800,	// szerokoœæ okna
	600,	// wysokoœæ okna
	24,		// wielkoœæ czcionki
	30,		// fps
	4,		// maksymalna iloœæ klocków na osi X
	4,		// maksymalna iloœæ klocków na osi Y
	100,	// wielkoœæ klocka (px)
	10,		// wielkoœæ przerwy miêdzy klockami (10px)
	2,		// minimalna wartoœæ dla której obliczany jest gradient koloru
	2048,	// maksymalna wartoœæ dla której obliczany jest gradient koloru
	250,	// wartoœæ minimalna gradientu (r)
	250,	// wartoœæ minimalna gradientu (g)
	0,		// wartoœæ minimalna gradientu (b)
	255,	// wartoœæ maksymalna gradientu (r)
	0,		// wartoœæ maksymalna gradientu (g)
	120		// wartoœæ maksymalna gradientu (b)
};

struct game_window game;