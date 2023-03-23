#include "game_board.h" // za�adowanie definicji z pliku nag��wkowego
#include "game_data.h"  // plik nag��wkowy z podstawowymi strukturami gry

extern struct game_window game; // definicja zewn�trznej struktury zawieraj�cej g��wne zmienne okna gry
extern struct config cfg;       // definicja zewn�trznej struktury z podstawow� konfiguracj� gry

struct node {
	int value;				// warto��, jak� przechowuje klocek (2, 4, 8, 16, 32...)
	int top_x;				// koordynata X klocka w lewym g�rnym rogu (px)
	int top_y;				// koordynata Y klocka w lewym g�rnym rogu (px)
	int bottom_x;			// koordynata X klocka w prawym dolnym rogu (px)
	int bottom_y;			// koordynata Y klocka w prawym dolnym rogu (px)
	int size;				// wielko�� boku klocka (px)
	ALLEGRO_COLOR color;	// kolor klocka
};

struct game_board {
	int x_size;						// maksymalna ilo�� klock�w na osi X
	int y_size;						// maksymalna ilo�� klock�w na osi Y
	int node_size;					// wielko�� klocka (px)
	int gap;						// wielko�� przerwy mi�dzy klockami (10px)
	struct node** board_array;		// plansza z klockami
} board;

// funkcja inicjuj�ca plansz� gry
void initialize_board()
{
	// przypisanie strukturze board zmiennych ze struktury config zawieraj�c� konfiguracj� gry
	board.x_size = cfg.board_x_size;
	board.y_size = cfg.board_y_size;
	board.node_size = cfg.board_node_size;
	board.gap = cfg.board_gap;

	// dynamiczna alokacja pami�ci dla planszy z klockami
	board.board_array = (struct node **)calloc(board.y_size, sizeof(struct node *));

	int i;
	for (i = 0; i < board.y_size; i++)
		board.board_array[i] = (struct node *)calloc(board.x_size, sizeof(struct node));
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
}

// funkcja rysuj�ca plansz�
void draw_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for(j = 0; j < board.x_size; j++)
		{
			struct node current_node = board.board_array[i][j];	// aktualnie rysowany klocek

			// rysowanie klocka, wykorzystuj�c pola wygenerowane funkcj� generate_board()
			al_draw_filled_rectangle(
				current_node.top_x,					
				current_node.top_y, 
				current_node.bottom_x, 
				current_node.bottom_y,
				current_node.color
			);

			if (current_node.value)	// je�eli warto�� klocka != 0
			{
				// rysowanie warto�ci wewn�trz klocka
				al_draw_textf(
					game.font,
					al_map_rgb(255, 255, 255),
					current_node.top_x + current_node.size / 2,						// po�owa klocka na osi X = g�rne x + po�owa d�ugo�ci boku
					current_node.top_y + current_node.size / 2 - cfg.font_size / 2,	// po�owa klocka na osi Y = y + po�owa d�ugo�ci boku, dalsza cz�� - patrz ni�ej
					ALLEGRO_ALIGN_CENTER,	// wycentrowanie tekstu przez allegro, ale tylko w osi X, w osi Y nale�y odj�� od y po�ow� wielko�ci czcionki
					"%d",					// ci�g formatuj�cy rysowany tekst
					current_node.top_y		// tekst do narysowania
				);
			}
		}
	}
}

// funkcja wstawiaj�ca klocek do planszy
// przyjmuje koordynaty klocka na planszy i warto�� klocka
void insert_node(int x, int y, int value)
{
	struct node *current_node = &board.board_array[y][x];	// aktualnie wstawiany klocek
	current_node->value = value;							// zmiana warto��i klocka (od teraz b�dzie rysowany)
	current_node->color = al_map_rgb(255, 0, 0);			// zmiana koloru klocka
}
