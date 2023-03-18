// Przyk³adowy plik z definicj¹ czêœci logiki gry

#include "example.h"	// za³adowanie definicji z pliku nag³ówkowego
						// ka¿dy modu³ musi zawieraæ plik nag³ówkowy z definicj¹ (definicjami) tworzonych funkcji					

#include "game_data.h"	// za³adowanie podstawowych struktur i bibliotek gry
						// daje dostêp do zmiennych biblioteki i struktur okna gry

extern struct game_window game; // definicja zewnêtrznej struktury zawieraj¹cej g³ówne zmienne okna gry

int x = 0;
int y = 0;

// przyk³adowa funkcja z logik¹ gry
void example_render()
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(game.font, al_map_rgb(255, 0, 0), x++, y++, NULL, "Hello world!");
}