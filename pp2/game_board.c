#include "game_board.h" // za³adowanie definicji z pliku nag³ówkowego
#include "game_data.h"  // plik nag³ówkowy z podstawowymi strukturami gry
#include <stdio.h>
#include <time.h>

extern struct game_window game; // definicja zewnêtrznej struktury zawieraj¹cej g³ówne zmienne okna gry
extern struct config cfg;       // definicja zewnêtrznej struktury z podstawow¹ konfiguracj¹ gry

struct node {
	int value;				// wartoœæ, jak¹ przechowuje klocek (2, 4, 8, 16, 32...)
	int top_x;				// koordynata X klocka w lewym górnym rogu (px)
	int top_y;				// koordynata Y klocka w lewym górnym rogu (px)
	int bottom_x;			// koordynata X klocka w prawym dolnym rogu (px)
	int bottom_y;			// koordynata Y klocka w prawym dolnym rogu (px)
	int size;				// wielkoœæ boku klocka (px)
	ALLEGRO_COLOR color;	// kolor klocka
};

struct game_board {
	int x_size;						// maksymalna iloœæ klocków na osi X
	int y_size;						// maksymalna iloœæ klocków na osi Y
	int node_size;					// wielkoœæ klocka (px)
	int gap;						// wielkoœæ przerwy miêdzy klockami (10px)
	struct node** board_array;		// plansza z klockami
} board;

// funkcja inicjuj¹ca planszê gry
void initialize_board()
{
	// przypisanie strukturze board zmiennych ze struktury config zawieraj¹c¹ konfiguracjê gry
	board.x_size = cfg.board_x_size;
	board.y_size = cfg.board_y_size;
	board.node_size = cfg.board_node_size;
	board.gap = cfg.board_gap;

	// dynamiczna alokacja pamiêci dla planszy z klockami
	board.board_array = (struct node **)calloc(board.y_size, sizeof(struct node *));

	int i;
	for (i = 0; i < board.y_size; i++)
		board.board_array[i] = (struct node *)calloc(board.x_size, sizeof(struct node));
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

// funkcja rysuj¹ca planszê
void draw_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for(j = 0; j < board.x_size; j++)
		{
			struct node current_node = board.board_array[i][j];	// aktualnie rysowany klocek

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
					al_map_rgb(0, 0, 0),
					current_node.top_x + current_node.size / 2,						// po³owa klocka na osi X = górne x + po³owa d³ugoœci boku
					current_node.top_y + current_node.size / 2 - cfg.font_size / 2,	// po³owa klocka na osi Y = y + po³owa d³ugoœci boku, dalsza czêœæ - patrz ni¿ej
					ALLEGRO_ALIGN_CENTER,	// wycentrowanie tekstu przez allegro, ale tylko w osi X, w osi Y nale¿y odj¹æ od y po³owê wielkoœci czcionki
					"%d",					// ci¹g formatuj¹cy rysowany tekst
					current_node.value		// tekst do narysowania
				);
			}
		}
	}
}

// funkcja wstawiaj¹ca klocek do planszy
// przyjmuje koordynaty klocka na planszy i wartoœæ klocka
void insert_node(int x, int y, int value)
{
	board.board_array[y][x].value = value;
}

// funkcja do debugowania wypisuj¹ca planszê w terminalu
void debug_print_board()
{
	int i, j;
	for(i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++) 
		{
			printf("%d\t", board.board_array[i][j].value);
		}
		printf("\n");
	}
}


// funkcje przesuwaj¹ce klocki 
// TODO: OPISAÆ DZIA£ANIE
void move_down() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 0; i < board.y_size - 1; i++) {
				if (board.board_array[i+1][row].value == 0) {
					board.board_array[i+1][row].value = board.board_array[i][row].value;
					board.board_array[i][row].value = 0;
				}
			}
		}
	}
	generate_random_node();
}

void move_up() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 1; i < board.y_size; i++) {
				if (board.board_array[i-1][row].value == 0) {
					board.board_array[i-1][row].value = board.board_array[i][row].value;
					board.board_array[i][row].value = 0;
				}
			}
		}
	}
	generate_random_node();
}

void move_right() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 0; i < board.y_size - 1; i++) {
				if (board.board_array[col][i+1].value == 0) {
					board.board_array[col][i+1].value = board.board_array[col][i].value;
					board.board_array[col][i].value = 0;
				}
			}
		}
	}
	generate_random_node();
}

void move_left() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 1; i < board.y_size; i++) {
				if (board.board_array[col][i - 1].value == 0) {
					board.board_array[col][i - 1].value = board.board_array[col][i].value;
					board.board_array[col][i].value = 0;
				}
			}
		}
	}
	generate_random_node();
}

// funkcje ³¹cz¹ce klocki
// TODO: OPISAÆ DZIA£ANIE
void stack_down() {
	int i, j, stacked = -1;
	for (i = 2; i >= 0; i--) 
	{
		for (j = 0; j < 4; j++) 
		{
			if (board.board_array[i][j].value == 0) continue;
			int k = i + 1;
			while (k < 4) 
			{
				if (board.board_array[k][j].value == 0) k++;                            
				else 
				{
					if (board.board_array[k][j].value == board.board_array[i][j].value && board.board_array[k][j].value != stacked)
					{
						board.board_array[k][j].value *= 2;
						board.board_array[i][j].value = 0;
						stacked = board.board_array[k][j].value;
					}
					break;
				}
			}
		}
	}
}

void stack_up() {
	int i, j, stacked = -1;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (board.board_array[i][j].value == 0) continue;
			int k = i - 1;
			while (k >= 0)
			{
				if (board.board_array[k][j].value == 0) k--;
				else
				{
					if (board.board_array[k][j].value == board.board_array[i][j].value && board.board_array[k][j].value != stacked)
					{
						board.board_array[k][j].value *= 2;
						board.board_array[i][j].value = 0;
						stacked = board.board_array[k][j].value;
					}
					break;
				}
			}
		}
	}
}

void stack_right() {
	int i, j, stacked = -1;
	for (i = 0; i < 4; i++)
	{
		for (j = 2; j >= 0; j--)
		{
			if (board.board_array[i][j].value == 0) continue;
			int k = j + 1;
			while (k < 4)
			{
				if (board.board_array[i][k].value == 0) k++;
				else
				{
					if (board.board_array[i][k].value == board.board_array[i][j].value && board.board_array[i][k].value != stacked)
					{
						board.board_array[i][k].value *= 2;
						board.board_array[i][j].value = 0;
						stacked = board.board_array[i][k].value;
					}
					break;
				}
			}
		}
	}
}

void stack_left() {
	int i, j, stacked = -1;
	for (i = 0; i < 4; i++)
	{
		for (j = 1; j < 4; j++)
		{
			if (board.board_array[i][j].value == 0) continue;
			int k = j - 1;
			while (k >= 0)
			{
				if (board.board_array[i][k].value == 0) k--;
				else
				{
					if (board.board_array[i][k].value == board.board_array[i][j].value && board.board_array[i][k].value != stacked)
					{
						board.board_array[i][k].value *= 2;
						board.board_array[i][j].value = 0;
						stacked = board.board_array[i][k].value;
					}
					break;
				}
			}
		}
	}
}

void generate_random_node()
{
	int col, row;
	int random;
	col = rand() % 4;
	row = rand() % 4;

	if(board.board_array[col][row].value == 0)
	{
		random = rand() % 10 + 1;             //10% szans na wygenerowanie klocka o wartosci 2
		if (random == 1)
		{
            board.board_array[col][row].value = 4;
		}
		else
		{
			board.board_array[col][row].value = 2;
		}
		
	}

}