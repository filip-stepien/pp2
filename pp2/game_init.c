#include "game_includes.h"
#include "game_init.h"
#include "game_structures.h"

// funkcja inicjuj�ca plansz� gry
void initialize_board()
{
	// przypisanie strukturze board zmiennych ze struktury config zawieraj�c� konfiguracj� gry
	board.x_size = cfg.board_x_size;
	board.y_size = cfg.board_y_size;
	board.total_size = cfg.board_y_size * cfg.board_y_size;
	board.node_size = cfg.board_node_size;
	board.gap = cfg.board_gap;
	board.first_turn = true;

	animations.grow_animation_array = (struct node*)calloc(board.total_size, sizeof(struct node));
	animations.slide_animation_array = (struct node*)calloc(board.total_size, sizeof(struct node));

	// dynamiczna alokacja pami�ci dla planszy z klockami
	board.board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));
	board.prev_board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));

	int i;
	for (i = 0; i < board.y_size; i++)
	{
		board.board_array[i] = (struct node*)calloc(board.x_size, sizeof(struct node));
		board.prev_board_array[i] = (struct node*)calloc(board.x_size, sizeof(struct node));
	}
}

// funkcja wst�pnie inicjuj�ca klocki
// przyjmuje koordynaty x i y, w kt�rych ma zosta� wygenerowana plansza
void initialize_nodes(int render_x, int render_y)
{
	int i, j;
	int x = render_x, y = render_y;	// liczenie koordynat�w x i y rozpoczyna si� od koordynat�w w kt�rych ma znajdowa� si� plansza

	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			struct node current_node = {
				0,							// pocz�tkowa warto�� klocka

				x,							// klocki rysowane s� od lewego g�rnego rogu a wi�c g�rne x i y to kolejne
				y,							// wielokrotno�ci d�ugo�ci boku i przerwy mi�dzy nimi licz�c od zera (patrz ni�ej)

				x + board.node_size,		// aby otrzyma� "dolne" x i y, ka�dorazowo nale�y
				y + board.node_size,		// doda� do nich d�ugo�� boku (patrz ni�ej)

				board.node_size,			// d�ugo�� boku
				al_map_rgb(255, 255, 255)	// kolor klocka
			};

			board.board_array[i][j] = current_node;		// wstawianie wygenerowanego klocka do tablicy
			x += board.node_size + board.gap;			// kolejna iteracja na osi X = zwi�kszenie x o d�ugo�� boku i przerw� mi�dzy klockami
		}

		x = render_x;						// resetowanie x do pocz�tkowej warto�ci, aby rozpocz�� od pocz�tku wiersza
		y += board.node_size + board.gap;	// kolejna iteracja na osi Y = zwi�kszenie y o d�ugo�� boku i przerw� mi�dzy klockami
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

// funkcja zwalniaj�ca pami�� zaalokowan� dla planszy gry
void board_cleanup()
{
	// zwalnianie pami�ci w kolejno�ci odwrotnej w stosunku do alokacji
	int i;
	for (i = board.y_size - 1; i >= 0; i--)
		free(board.board_array[i]);

	free(board.board_array);
	board.board_array = NULL;	// unikni�ci� "wisz�cego wska�nika"

	free(animations.grow_animation_array);
	animations.grow_animation_array = NULL;
}

// funkcja inicjujaca liczninik punkt�w
void initialize_points(int render_x, int render_y, int width, int height, int font_size)
{
	// przypisanie strukturze points zmiennych z parametr�w funkcji
	points.width = width;
	points.height = height;
	points.top_x = render_x;
	points.top_y = render_y;
	points.bottom_x = render_x + width;
	points.bottom_y = render_y + height;
	points.counter = 0;
}