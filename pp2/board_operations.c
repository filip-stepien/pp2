#include "board_operations.h"
#include "game_structures.h"
#include "board_utils.h"

#include <time.h>
#include <math.h>

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

		if (board.board_array[col][row].value == 0)	// je¿eli pole jest puste
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

// funkcja wstawiaj¹ca klocek do planszy
// przyjmuje koordynaty klocka na planszy i wartoœæ klocka
void insert_node(int x, int y, int value)
{
	board.board_array[y][x].value = value;
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
	points.counter = 0;			// resetuj licznik gry

	// TODO: USUN¥Æ FUNKCJE DO DEBUGOWANIA
	system("cls");	// wyczysc konsole
}