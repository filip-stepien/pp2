#include "game_board.h" // za³adowanie definicji z pliku nag³ówkowego
#include "game_data.h"  // plik nag³ówkowy z podstawowymi strukturami gry
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

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
	bool first_turn;
	struct node** prev_board_array;
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
	board.first_turn = true;

	// dynamiczna alokacja pamiêci dla planszy z klockami
	board.board_array = (struct node **)calloc(board.y_size, sizeof(struct node *));
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

// funkcja do zapisu stanu planszy
void save_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
		for (j = 0; j < board.x_size; j++)
			board.prev_board_array[i][j].value = board.board_array[i][j].value;
}

// funkcja do resetu planszy
void reset_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			board.prev_board_array[i][j].value = 0;	// wyzerowanie zapisanej planszy gry
			board.board_array[i][j].value = 0;		// wyzerowanie aktulanej planszy gry
		}
	}

	board.first_turn = true;	// nowa gra zacznie siê od pierwszej tury
}

// funkcja sprawdzaj¹ca czy na planszy nast¹pi³ ruch
bool did_board_change()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			if (board.prev_board_array[i][j].value != board.board_array[i][j].value)	// porównanie planszy aktualnej z zapisan¹
				return true;
		}
	}

	return false;
}

// funkcja sprawdzaj¹ca czy mo¿liwe jest wykonanie ruchu na planszy
bool did_game_end() 
{
	int i, j;
	for (i = 0; i < board.y_size; i++) {
		for (j = 0; j < board.x_size; j++) {
			if (board.board_array[i][j].value == 0)
				return false;
			if (i > 0 && board.board_array[i][j].value == board.board_array[i - 1][j].value)
				return false;
			if (j > 0 && board.board_array[i][j].value == board.board_array[i][j - 1].value)
				return false;
			if (i < board.y_size - 1 && board.board_array[i][j].value == board.board_array[i + 1][j].value)
				return false;
			if (j < board.x_size - 1 && board.board_array[i][j].value == board.board_array[i][j + 1].value)
				return false;
		}
	}
	return true;
}

// funkcje przesuwaj¹ce klocki 
// TODO: OPISAÆ DZIA£ANIE
void move_down() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 0; i < board.y_size - 1; i++) {
				if (board.board_array[i+1][row].value == 0 && board.board_array[i][row].value != 0) {
					board.board_array[i+1][row].value = board.board_array[i][row].value;
					board.board_array[i][row].value = 0;
				}
			}
		}
	}
}

void move_up() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 1; i < board.y_size; i++) {
				if (board.board_array[i-1][row].value == 0 && board.board_array[i][row].value != 0) {
					board.board_array[i-1][row].value = board.board_array[i][row].value;
					board.board_array[i][row].value = 0;
				}
			}
		}
	}
}

void move_right() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 0; i < board.y_size - 1; i++) {
				if (board.board_array[col][i+1].value == 0 && board.board_array[col][i].value != 0) 
				{
					board.board_array[col][i+1].value = board.board_array[col][i].value;
					board.board_array[col][i].value = 0;
				}
			}
		}
	}
}

void move_left() {
	int row, col, i;
	for (row = 0; row < board.y_size; row++) {
		for (col = 0; col < board.x_size; col++) {
			for (i = 1; i < board.y_size; i++) {
				if (board.board_array[col][i - 1].value == 0 && board.board_array[col][i].value != 0) {
					board.board_array[col][i - 1].value = board.board_array[col][i].value;
					board.board_array[col][i].value = 0;
				}
			}
		}
	}
}

// funkcje ³¹cz¹ce klocki
// TODO: OPISAÆ DZIA£ANIE
void stack_down() {
	int i, j, stacked = -1;
	save_board();
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
	save_board();
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
	save_board();
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
	save_board();
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

// funkcja generuj¹ca losowy klocek
void generate_random_node()
{
	int col, row;
	int random;
	bool inserted = false;	// zmienna steruj¹ca pêtl¹ od generowania klocka
	bool changed = did_board_change();	// sprawdzenie, czy plansza zmieni³a siê od ostatniego ruchu

	// dopóki:
	// nie zosta³ wstawiony klocek i plansza zmieni³a siê od ostatniego ruchu
	// albo jest pierwsza tura gry
	// to wstaw klocek
	while (!inserted && changed || board.first_turn)
	{
		col = rand() % 4;	// losowa kolumna od 0 do 3
		row = rand() % 4;	// losowy wiersz od 0 do 3

		if(board.board_array[col][row].value == 0)	// je¿eli pole jest puste
		{
			random = rand() % 10 + 1;				// 10% szans na wygenerowanie klocka o wartosci 2

			if (random == 1)
				board.board_array[col][row].value = 4;
			else
				board.board_array[col][row].value = 2;

			inserted = true;	// zakoñczenie pêtli
			board.first_turn = false;	// po wstawieniu klocka minê³a pierwsza tura
		}
	}
}

// funkcja mapuj¹ca wartoœæ klocka (miêdzy node_min_interpolation a node_max_interpolation z konfiguracji)
// na kolor rgb (miêdzy node_min_color_(...) a node_max_color_(...))
ALLEGRO_COLOR interpolate_node_color(struct node target)
{
	if (target.value < cfg.node_min_interpolation) return al_map_rgb(255, 255, 255); // je¿eli wartoœæ klocka jest <2 to zwróæ bia³y kolor
	if (target.value > cfg.node_max_interpolation)	// je¿eli wartoœæ klocka jest >2048 to zwróæ kolor z konfiguracji
		return al_map_rgb(
			cfg.node_max_color_r,
			cfg.node_max_color_g,
			cfg.node_max_color_b
		);

	// mapowanie wartoœci 2, 4, 8, 16 ... na zakres od 1 do log z maksymalnej wartoœci z konfiguracji (2048 = 11)
	double log_value = log2(target.value);
	double log_max = log2(cfg.node_max_interpolation);
	double normalized_value = log_value / log_max;		// mapowanie otrzymanego zakresu na wartosci od 0 do 1

	// zamiana otrzymanej wartosci na nowy kolor rgb
	unsigned char r = round(cfg.node_min_color_r + (cfg.node_max_color_r - cfg.node_min_color_r) * normalized_value);
	unsigned char g = round(cfg.node_min_color_g + (cfg.node_max_color_g - cfg.node_min_color_g) * normalized_value);
	unsigned char b = round(cfg.node_min_color_b + (cfg.node_max_color_b - cfg.node_min_color_b) * normalized_value);

	// zwrócenie koloru rgb w postaci struktury ALLEGRO_COLOR
	return al_map_rgb(r, g, b);
}

// funkcja koloruj¹ca ka¿dy klocek zale¿nie od jego wartoœci
void color_nodes()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
		for (j = 0; j < board.x_size; j++)
			board.board_array[i][j].color = interpolate_node_color(board.board_array[i][j]);
}