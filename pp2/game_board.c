#include "game_board.h" // za�adowanie definicji z pliku nag��wkowego
#include "game_data.h"  // plik nag��wkowy z podstawowymi strukturami gry
#include <stdio.h>
#include <time.h>
#include <math.h>

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
					al_map_rgb(0, 0, 0),
					current_node.top_x + current_node.size / 2,						// po�owa klocka na osi X = g�rne x + po�owa d�ugo�ci boku
					current_node.top_y + current_node.size / 2 - cfg.font_size / 2,	// po�owa klocka na osi Y = y + po�owa d�ugo�ci boku, dalsza cz�� - patrz ni�ej
					ALLEGRO_ALIGN_CENTER,	// wycentrowanie tekstu przez allegro, ale tylko w osi X, w osi Y nale�y odj�� od y po�ow� wielko�ci czcionki
					"%d",					// ci�g formatuj�cy rysowany tekst
					current_node.value		// tekst do narysowania
				);
			}
		}
	}
}

// funkcja wstawiaj�ca klocek do planszy
// przyjmuje koordynaty klocka na planszy i warto�� klocka
void insert_node(int x, int y, int value)
{
	board.board_array[y][x].value = value;
}

// funkcja do debugowania wypisuj�ca plansz� w terminalu
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


// funkcje przesuwaj�ce klocki 
// TODO: OPISA� DZIA�ANIE
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

// funkcje ��cz�ce klocki
// TODO: OPISA� DZIA�ANIE
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

// funkcja mapuj�ca warto�� klocka (mi�dzy node_min_interpolation a node_max_interpolation z konfiguracji)
// na kolor rgb (mi�dzy node_min_color_(...) a node_max_color_(...))
ALLEGRO_COLOR interpolate_node_color(struct node target)
{
	if (target.value < cfg.node_min_interpolation) return al_map_rgb(255, 255, 255); // je�eli warto�� klocka jest <2 to zwr�� bia�y kolor
	if (target.value > cfg.node_max_interpolation)	// je�eli warto�� klocka jest >2048 to zwr�� kolor z konfiguracji
		return al_map_rgb(
			cfg.node_max_color_r,
			cfg.node_max_color_g,
			cfg.node_max_color_b
		);

	// mapowanie warto�ci 2, 4, 8, 16 ... na zakres od 1 do log z maksymalnej warto�ci z konfiguracji (2048 = 11)
	double log_value = log2(target.value);
	double log_max = log2(cfg.node_max_interpolation);
	double normalized_value = log_value / log_max;		// mapowanie otrzymanego zakresu na wartosci od 0 do 1

	// zamiana otrzymanej wartosci na nowy kolor rgb
	unsigned char r = round(cfg.node_min_color_r + (cfg.node_max_color_r - cfg.node_min_color_r) * normalized_value);
	unsigned char g = round(cfg.node_min_color_g + (cfg.node_max_color_g - cfg.node_min_color_g) * normalized_value);
	unsigned char b = round(cfg.node_min_color_b + (cfg.node_max_color_b - cfg.node_min_color_b) * normalized_value);

	// zwr�cenie koloru rgb w postaci struktury ALLEGRO_COLOR
	return al_map_rgb(r, g, b);
}

// funkcja koloruj�ca ka�dy klocek zale�nie od jego warto�ci
void color_nodes()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
		for (j = 0; j < board.x_size; j++)
			board.board_array[i][j].color = interpolate_node_color(board.board_array[i][j]);
}