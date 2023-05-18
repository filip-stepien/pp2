// Plik zawieraj¹cy deklaracjê struktur zdefiniowanych w game_data.h

#include "game_includes.h"
#include "game_structures.h"

struct config cfg = { 
	450,			// szerokoœæ okna
	600,			// wysokoœæ okna
	24,				// wielkoœæ czcionki
	60,				// fps
	4,				// maksymalna iloœæ klocków na osi X
	4,				// maksymalna iloœæ klocków na osi Y
	100,			// wielkoœæ klocka (px)
	10,				// wielkoœæ przerwy miêdzy klockami (10px)
	0, 0, 0,		// kolor t³a (r, g, b)
	2,				// minimalna wartoœæ dla której obliczany jest gradient koloru
	2048,			// maksymalna wartoœæ dla której obliczany jest gradient koloru
	250, 250, 0,	// wartoœæ minimalna gradientu (r, g, b)
	255, 0 , 120,	// wartoœæ maksymalna gradientu (r, g, b)
	10,
	50
};

struct game_window game;
struct game_board board;
struct game_points points;
struct game_animations animations;