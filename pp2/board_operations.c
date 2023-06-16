/**
 * @file board_operations.c
 * @brief Operacje na planszy gry
 */

#include "board_operations.h"
#include "game_structures.h"
#include "board_utils.h"
#include "board_animations.h"
#include "game_music.h"

#include <time.h>
#include <math.h>
#include <stdio.h>

/**
 * @brief Generowanie losowego klocka
 */
void generate_random_node()
{
	int col = -1, row = -1;
	int random;
	bool inserted = false;
	bool changed = did_board_change();

	while (!inserted && changed || board.first_turn)
	{
		col = rand() % board.y_size;
		row = rand() % board.x_size;

		if (board.board_array[col][row].value == 0)
		{
			random = rand() % 10 + 1;

			if (random == 1)
				board.board_array[col][row].value = 4;
			else
				board.board_array[col][row].value = 2;

			inserted = true;
			board.first_turn = false;

			color_nodes();
			push_to_grow_animation_array(board.board_array[col][row]);

			play_grow_sound();
		}
	}
}

/**
 * @brief Wstawianie klocka w określone miejsce
 * @param x koordynata x
 * @param y koordynata y
 * @param value wartość klocka
 */
void insert_node(int x, int y, int value)
{
	board.board_array[y][x].value = value;
}

/**
 * @brief Interpolacja koloru klocka
 * @param target klocek
 * @return nowy kolor klocka
 */
ALLEGRO_COLOR interpolate_node_color(struct node target)
{
	if (target.value < cfg.node_min_interpolation) return al_map_rgb(255, 255, 255);
	if (target.value > cfg.node_max_interpolation)
		return al_map_rgb(
			cfg.node_max_color_r,
			cfg.node_max_color_g,
			cfg.node_max_color_b
		);

	double log_value = log2(target.value);
	double log_max = log2(cfg.node_max_interpolation);
	double normalized_value = log_value / log_max;

	unsigned char r = round(cfg.node_min_color_r + (cfg.node_max_color_r - cfg.node_min_color_r) * normalized_value);
	unsigned char g = round(cfg.node_min_color_g + (cfg.node_max_color_g - cfg.node_min_color_g) * normalized_value);
	unsigned char b = round(cfg.node_min_color_b + (cfg.node_max_color_b - cfg.node_min_color_b) * normalized_value);

	return al_map_rgb(r, g, b);
}

/**
 * @brief Kolorowanie klocków
 */
void color_nodes()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
		for (j = 0; j < board.x_size; j++)
			board.board_array[i][j].color = interpolate_node_color(board.board_array[i][j]);
}

/**
 * @brief Zapisanie stanu planszy
 */
void save_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
		for (j = 0; j < board.x_size; j++)
			board.prev_board_array[i][j] = board.board_array[i][j];
}

/**
 * @brief Zresetowanie planszy
 */
void reset_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			board.prev_board_array[i][j].value = 0;
			board.board_array[i][j].value = 0;
		}
	}

	board.first_turn = true;
	points.counter = 0;
}