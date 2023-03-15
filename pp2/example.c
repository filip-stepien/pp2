// Przyk�adowy plik z definicj� cz�ci logiki gry

#include "example.h"	// za�adowanie definicji z pliku nag��wkowego
						// ka�dy modu� musi zawiera� plik nag��wkowy z definicj� (definicjami) tworzonych funkcji					

#include "game_data.h"	// za�adowanie podstawowych struktur i bibliotek gry
						// daje dost�p do zmiennych biblioteki i struktur okna gry

extern struct game_window game; // definicja zewn�trznej struktury zawieraj�cej g��wne zmienne okna gry

// przyk�adowa funkcja z logik� gry
void example_render()
{
	al_draw_text(game.font, al_map_rgb(255, 0, 0), 100, 100, NULL, "Hello world!");
}