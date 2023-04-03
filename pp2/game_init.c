#include "game_init.h"
#include "game_structures.h"

extern struct game_board board;
extern struct config cfg;
extern struct game_points points;

// funkcja inicjuj¹ca planszê gry
void initialize_board()
{
	// przypisanie strukturze board zmiennych ze struktury config zawieraj¹c¹ konfiguracjê gry
	board.x_size = cfg.board_x_size;
	board.y_size = cfg.board_y_size;
	board.node_size = cfg.board_node_size;
	board.gap = cfg.board_gap;
	board.first_turn = true;

	// dynamiczna alokacja pamiêci dla planszy z klockami
	board.board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));
	board.prev_board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));

	int i;
	for (i = 0; i < board.y_size; i++)
	{
		board.board_array[i] = (struct node*)calloc(board.x_size, sizeof(struct node));
		board.prev_board_array[i] = (struct node*)calloc(board.x_size, sizeof(struct node));
	}
}

// funkcja wstêpnie inicjuj¹ca klocki
// przyjmuje koordynaty x i y, w których ma zostaæ wygenerowana plansza
void initialize_nodes(int render_x, int render_y)
{
	int i, j;
	int x = render_x, y = render_y;	// liczenie koordynatów x i y rozpoczyna siê od koordynatów w których ma znajdowaæ siê plansza

	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			struct node current_node = {
				0,							// pocz¹tkowa wartoœæ klocka

				x,							// klocki rysowane s¹ od lewego górnego rogu a wiêc górne x i y to kolejne
				y,							// wielokrotnoœci d³ugoœci boku i przerwy miêdzy nimi licz¹c od zera (patrz ni¿ej)

				x + board.node_size,		// aby otrzymaæ "dolne" x i y, ka¿dorazowo nale¿y
				y + board.node_size,		// dodaæ do nich d³ugoœæ boku (patrz ni¿ej)

				board.node_size,			// d³ugoœæ boku
				al_map_rgb(255, 255, 255)	// kolor klocka
			};

			board.board_array[i][j] = current_node;		// wstawianie wygenerowanego klocka do tablicy
			x += board.node_size + board.gap;			// kolejna iteracja na osi X = zwiêkszenie x o d³ugoœæ boku i przerwê miêdzy klockami
		}

		x = render_x;						// resetowanie x do pocz¹tkowej wartoœci, aby rozpocz¹æ od pocz¹tku wiersza
		y += board.node_size + board.gap;	// kolejna iteracja na osi Y = zwiêkszenie y o d³ugoœæ boku i przerwê miêdzy klockami
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

// funkcja zwalniaj¹ca pamiêæ zaalokowan¹ dla planszy gry
void board_cleanup()
{
	// zwalnianie pamiêci w kolejnoœci odwrotnej w stosunku do alokacji
	int i;
	for (i = board.y_size - 1; i >= 0; i--)
		free(board.board_array[i]);

	free(board.board_array);
	board.board_array = NULL;	// unikniêciê "wisz¹cego wskaŸnika"
}

// funkcja inicjujaca liczninik punktów
void initialize_points(int render_x, int render_y, int width, int height, int font_size)
{
	// przypisanie strukturze points zmiennych z parametrów funkcji
	points.width = width;
	points.height = height;
	points.top_x = render_x;
	points.top_y = render_y;
	points.bottom_x = render_x + width;
	points.bottom_y = render_y + height;
	points.counter = 0;
}