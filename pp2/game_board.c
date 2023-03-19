#include "game_board.h" // za³adowanie definicji z pliku nag³ówkowego
#include "game_data.h"  // plik nag³ówkowy z podstawowymi strukturami gry
#include <string.h>

extern struct game_window game; // definicja zewnêtrznej struktury zawieraj¹cej g³ówne zmienne okna gry
extern struct config cfg;       // definicja zewnêtrznej struktury z podstawow¹ konfiguracj¹ gry

int x_size = 4;			// maksymalna iloœæ klocków na osi X
int y_size = 4;			// maksymalna iloœæ klocków na osi Y
int node_size = 100;	// wielkoœæ klocka (px)
int gap = 10;			// wielkoœæ przerwy miêdzy klockami (10px)

struct node {
	int value;				// wartoœæ, jak¹ przechowuje klocek (2, 4, 8, 16, 32...)
	int top_x;				// koordynata X klocka w lewym górnym rogu (px)
	int top_y;				// koordynata Y klocka w lewym górnym rogu (px)
	int bottom_x;			// koordynata X klocka w prawym dolnym rogu (px)
	int bottom_y;			// koordynata Y klocka w prawym dolnym rogu (px)
	int size;				// wielkoœæ boku klocka (px)
	ALLEGRO_COLOR color;	// kolor klocka
};

struct node board[4][4];	// tablica 2D reprezentuj¹ca planszê

// funkcja wstêpnie wype³niaj¹ca planszê (tablicê 2D) klockami o wartoœci 0
// przyjmuje koordynaty x i y, w których ma zostaæ wygenerowana plansza
void generate_board(int board_x, int board_y)
{
	int i, j;
	int x = board_x, y = board_y;	// liczenie koordynatów x i y rozpoczyna siê od koordynatów w których ma znajdowaæ siê plansza

	for (i = 0; i < y_size; i++)
	{
		for (j = 0; j < x_size; j++)
		{
			struct node current_node = { 
				0,							// pocz¹tkowa wartoœæ klocka

				x,							// klocki rysowane s¹ od lewego górnego rogu a wiêc górne x i y to kolejne
				y,							// wielokrotnoœci d³ugoœci boku i przerwy miêdzy nimi licz¹c od zera (patrz ni¿ej)

				x + node_size,				// aby otrzymaæ "dolne" x i y, ka¿dorazowo nale¿y
				y + node_size,				// dodaæ do nich d³ugoœæ boku (patrz ni¿ej)

				node_size,					// d³ugoœæ boku
				al_map_rgb(255, 255, 255)	// kolor klocka
			};

			board[i][j] = current_node;		// wstawianie wygenerowanego klocka do tablicy
			x += node_size + gap;			// kolejna iteracja na osi X = zwiêkszenie x o d³ugoœæ boku i przerwê miêdzy klockami
		}

		x = board_x;			// resetowanie x do pocz¹tkowej wartoœci, aby rozpocz¹æ od pocz¹tku wiersza
		y += node_size + gap;	// kolejna iteracja na osi Y = zwiêkszenie y o d³ugoœæ boku i przerwê miêdzy klockami
	}

	/*

	(x,y)							 (x+n+gap,y)
		O********			|	  |			O********
		*		*			|	  |			*		*
		*		* n			| gap |			*		*
		*		*			|	  |			*		*
		********O			|	  |			********O
			n	(x+n, y+n)							(x+2n+gap,y+n)

		---------
		   gap
		---------

	(x,y+n+gap)
		O********
		*		*
		*		* n
		*		*
		********O
			n	(x+n,y+2n+gap)

	*/
}

// funkcja rysuj¹ca planszê
void draw_board()
{
	int i, j;
	for (i = 0; i < y_size; i++)
	{
		for(j = 0; j < x_size; j++)
		{
			struct node current_node = board[i][j];	// aktualnie rysowany klocek

			// rysowanie klocka, wykorzystuj¹c pola wygenerowane funkcj¹ generate_board()
			al_draw_filled_rectangle(
				current_node.top_x,					
				current_node.top_y, 
				current_node.bottom_x, 
				current_node.bottom_y,
				current_node.color
			);

			if (current_node.value)	// je¿eli wartoœæ klocka != 0
			{
				// rysowanie wartoœci wewn¹trz klocka
				al_draw_textf(
					game.font,
					al_map_rgb(255, 255, 255),
					current_node.top_x + current_node.size / 2,						// po³owa klocka na osi X = górne x + po³owa d³ugoœci boku
					current_node.top_y + current_node.size / 2 - cfg.font_size / 2,	// po³owa klocka na osi Y = y + po³owa d³ugoœci boku, dalsza czêœæ - patrz ni¿ej
					ALLEGRO_ALIGN_CENTER,	// wycentrowanie tekstu przez allegro, ale tylko w osi X, w osi Y nale¿y odj¹æ od y po³owê wielkoœci czcionki
					"%d",					// ci¹g formatuj¹cy rysowany tekst
					current_node.top_y		// tekst do narysowania
				);
			}
		}
	}
}

// funkcja wstawiaj¹ca klocek do planszy
void insert_node(int x, int y, int value)
{
	struct node *current_node = &board[y][x];		// aktualnie wstawiany klocek
	current_node->value = value;					// zmiana wartoœæi klocka (od teraz bêdzie rysowany)
	current_node->color = al_map_rgb(255, 0, 0);	// zmiana koloru klocka
}
