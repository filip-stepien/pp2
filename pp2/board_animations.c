/**
 * @file board_animations.c
 * @brief Animacje gry
 */

#include "board_animations.h"
#include "game_structures.h"

#include <stdio.h>

/**
 * @brief Dodanie klocka do tablicy klocków wymagających wykonania animacji rozszerzenia
 * @param curent_node klocek
 */
void push_to_grow_animation_array(struct node current_node) {
	animations.grow_animation_array[animations.grow_animation_idx] = current_node;
	animations.grow_animation_idx++;
}

/**
 * @brief Wyczyszczenie tablicy klocków wymagających wykonania animacji rozszerzenia
 */
void clear_grow_animation_array()
{
	memset(animations.grow_animation_array, 0, board.total_size * sizeof(struct node));
	animations.grow_animation_idx = 0;
}

/**
 * @brief Wykonanie animacji rozszerzenia na klocku
 * @param curent_node klocek
 * @param current_frame klatka gry
 */
void grow_animation(struct node current_node, int current_frame)
{
	int step = current_frame;

	if (current_frame > cfg.grow_animation_duration / 2) {
		step = cfg.grow_animation_duration - current_frame;
	}

	al_draw_filled_rounded_rectangle(
		current_node.top_x - step,
		current_node.top_y - step,
		current_node.bottom_x + step,
		current_node.bottom_y + step,
		10, 10,
		current_node.color
	);

	if (current_node.value)
	{
		al_draw_textf(
			game.font,
			al_map_rgb(0, 0, 0),
			current_node.top_x + current_node.size / 2,
			current_node.top_y + current_node.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			current_node.value
		);
	}
}

/**
 * @brief Wykonanie animacji rozszerzenia na wszystkich wymagających tego klockach
 * @param frame klatka gry
 */
void grow_animate_nodes(int frame) {
	for (int i = 0; i < board.total_size; i++) {
		if (animations.grow_animation_array[i].top_x != 0 && animations.grow_animation_array[i].top_y != 0) {
			grow_animation(animations.grow_animation_array[i], frame);
		}
	}
}

/**
 * @brief Wyczyszczenie tablicy klocków wymagających wykonania animacji przesunięcia
 */
void clear_slide_animation_array() {
	memset(animations.slide_animation_array, 0, board.total_size * sizeof(struct node));
}

/**
 * @brief Wykonanie animacji przesunięcia na klocku (od lewej do prawej)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_left_to_right(struct node from, struct node to, int current_frame)
{
	int step = (current_frame + 1) * cfg.slide_animation_speed;

	if (from.top_x + step > to.top_x) 
	{
		al_draw_filled_rounded_rectangle(
			to.top_x,
			to.top_y,
			to.bottom_x,
			to.bottom_y,
			10, 10,
			to.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else if (from.top_x + step == to.top_x)
	{
		animations.done_sliding = true;
	}
	else 
	{
		al_draw_filled_rounded_rectangle(
			from.top_x + step,
			from.top_y,
			from.bottom_x + step,
			from.bottom_y,
			10, 10,
			from.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			from.top_x + step + from.size / 2,
			from.top_y + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

/**
 * @brief Wykonanie animacji przesunięcia na klocku (od prawej do lewej)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_right_to_left(struct node from, struct node to, int current_frame)
{
	int step = (current_frame + 1) * cfg.slide_animation_speed;

	if (from.bottom_x - step < to.bottom_x) 
	{
		al_draw_filled_rounded_rectangle(
			to.top_x,
			to.top_y,
			to.bottom_x,
			to.bottom_y,
			10, 10,
			to.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else if (from.bottom_x - step == to.bottom_x)
	{
		animations.done_sliding = true;
	}
	else 
	{
		al_draw_filled_rounded_rectangle(
			from.top_x - step,
			from.top_y,
			from.bottom_x - step,
			from.bottom_y,
			10, 10,
			from.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			from.top_x - step + from.size / 2,
			from.top_y + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

/**
 * @brief Wykonanie animacji przesunięcia na klocku (z dołu na górę)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_down_to_up(struct node from, struct node to, int current_frame)
{
	int step = (current_frame + 1) * cfg.slide_animation_speed;

	if (from.bottom_y - step < to.bottom_y) {
		al_draw_filled_rounded_rectangle(
			to.top_x,
			to.top_y,
			to.bottom_x,
			to.bottom_y,
			10, 10,
			to.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else if (from.bottom_y - step == to.bottom_y)
	{
		animations.done_sliding = true;
	}
	else 
	{
		al_draw_filled_rounded_rectangle(
			from.top_x,
			from.top_y - step,
			from.bottom_x,
			from.bottom_y - step,
			10, 10,
			from.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			from.top_x + from.size / 2,
			from.top_y - step + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

/**
 * @brief Wykonanie animacji przesunięcia na klocku (z góry na dół)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_up_to_down(struct node from, struct node to, int current_frame)
{
	int step = (current_frame + 1) * cfg.slide_animation_speed;

	if (from.top_y + step > to.top_y) 
	{
		al_draw_filled_rounded_rectangle(
			to.top_x,
			to.top_y,
			to.bottom_x,
			to.bottom_y,
			10, 10,
			to.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r,
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else if (from.top_y + step == to.top_y)
	{
		animations.done_sliding = true;
	}
	else 
	{
		al_draw_filled_rounded_rectangle(
			from.top_x,
			from.top_y + step,
			from.bottom_x,
			from.bottom_y + step,
			10, 10,
			from.color
		);

		al_draw_textf(
			game.font,
			al_map_rgb(
				cfg.node_text_color_r, 
				cfg.node_text_color_g,
				cfg.node_text_color_b
			),
			from.top_x + from.size / 2,
			from.top_y + step + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu od lewej do prawej)
 */
void get_nodes_to_slide_animate_left_to_right() 
{
	int idx = 0;

	for (int i = 0; i < board.y_size; i++) 
	{
		struct node current_node = { 0 };
		for (int j = 0; j < board.x_size; j++) 
		{
			if (board.prev_board_array[i][j].value != 0 && board.board_array[i][j].value == 0)
			{
				current_node = board.prev_board_array[i][j];
				for (int k = j + 1; k < board.x_size; k++)
				{
					if (current_node.top_x != board.board_array[i][k].top_x && board.board_array[i][k].value != 0)
					{
						animations.slide_animation_array[idx] = current_node;
						animations.slide_animation_array[idx + 1] = board.board_array[i][k];
						idx += 2;
						break;
					}
				}
			}
		}
	}
}

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu od prawej do lewej)
 */
void get_nodes_to_slide_animate_right_to_left() 
{
	int idx = 0;

	for (int i = 0; i < board.y_size; i++)
	{
		struct node current_node = { 0 };
		for (int j = board.x_size-1; j >= 0; j--)
		{
			if (board.prev_board_array[i][j].value != 0 && board.board_array[i][j].value == 0)
			{
				current_node = board.prev_board_array[i][j];
				for (int k = j; k >= 0; k--)
				{
					if (current_node.top_x != board.board_array[i][k].top_x && board.board_array[i][k].value != 0)
					{
						animations.slide_animation_array[idx] = current_node;
						animations.slide_animation_array[idx + 1] = board.board_array[i][k];
						idx += 2;
						break;
					}
				}
			}
		}
	}
}

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu z góry na dół)
 */
void get_nodes_to_slide_animate_up_to_down()
{
	int idx = 0;

	for (int i = 0; i < board.x_size; i++)
	{
		struct node current_node = { 0 };
		for (int j = 0; j < board.y_size; j++)
		{
			if (board.prev_board_array[j][i].value != 0 && board.board_array[j][i].value == 0)
			{
				current_node = board.prev_board_array[j][i];
				for (int k = j; k < board.y_size; k++)
				{
					if (current_node.top_y != board.board_array[k][i].top_y && board.board_array[k][i].value != 0)
					{
						animations.slide_animation_array[idx] = current_node;
						animations.slide_animation_array[idx + 1] = board.board_array[k][i];
						idx += 2;
						break;
					}
				}
			}
		}
	}
}

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu z dołu na górę)
 */
void get_nodes_to_slide_animate_down_to_up()
{
	int idx = 0;

	for (int i = 0; i < board.x_size; i++)
	{
		struct node current_node = { 0 };
		for (int j = board.x_size - 1; j >= 0; j--)
		{
			if (board.prev_board_array[j][i].value != 0 && board.board_array[j][i].value == 0)
			{
				current_node = board.prev_board_array[j][i];
				for (int k = j; k >= 0; k--)
				{
					if (current_node.top_y != board.board_array[k][i].top_y && board.board_array[k][i].value != 0)
					{
						animations.slide_animation_array[idx] = current_node;
						animations.slide_animation_array[idx + 1] = board.board_array[k][i];
						idx += 2;
						break;
					}
				}
			}
		}
	}
}

/**
 * @brief Uzupełnienie tablicy animacji rozszerzenia
 * @param frame klatka gry
 * 
 */
void slide_animate_nodes(int frame) 
{
	for (int i = 0; i < board.total_size; i += 2)
	{
		if (!animations.done_sliding && 
			animations.slide_animation_array[i].value == animations.slide_animation_array[i + 1].value && 
			animations.slide_animation_array[i].top_y != 0)
		{
			al_draw_filled_rounded_rectangle(
				animations.slide_animation_array[i + 1].top_x,
				animations.slide_animation_array[i + 1].top_y,
				animations.slide_animation_array[i + 1].bottom_x,
				animations.slide_animation_array[i + 1].bottom_y,
				10,
				10,
				al_map_rgb(
					cfg.default_node_color_r, 
					cfg.default_node_color_g,
					cfg.default_node_color_b
				)
			);
		}

		if (animations.slide_animation_array[i].value != 0 && animations.slide_animation_array[i + 1].value != 0)
		{
			switch (animations.last_move)
			{
			case LEFT:
				slide_animation_right_to_left(animations.slide_animation_array[i], animations.slide_animation_array[i + 1], frame);
				break;
			case RIGHT:
				slide_animation_left_to_right(animations.slide_animation_array[i], animations.slide_animation_array[i + 1], frame);
				break;
			case UP:
				slide_animation_down_to_up(animations.slide_animation_array[i], animations.slide_animation_array[i + 1], frame);
				break;
			case DOWN:
				slide_animation_up_to_down(animations.slide_animation_array[i], animations.slide_animation_array[i + 1], frame);
				break;
			}
		}
	}
}