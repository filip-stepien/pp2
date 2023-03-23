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
	10		// wielkoœæ przerwy miêdzy klockami (10px)
};

struct game_window game;