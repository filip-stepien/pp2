#include "board_animations.h"
#include "game_structures.h"

#include <stdio.h>

void push_to_animation_array(struct node current_node) {
	board.animation_array[board.animation_idx] = current_node;
	board.animation_idx++;
}

void clear_animation_array()
{
	memset(board.animation_array, 0, board.total_size * sizeof(struct node));
	board.animation_idx = 0;
}

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

	if (current_node.value)	// je¿eli wartoœæ klocka != 0
	{
		// rysowanie wartoœci wewn¹trz klocka
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

void get_nodes_to_grow_animate() {
	for (int i = 0; i < board.y_size; i++) {
		for (int j = 0; j < board.x_size; j++) {
			if (board.board_array[i][j].value != board.prev_board_array[i][j].value && board.prev_board_array[i][j].value != 0 && board.board_array[i][j].value != 0)
				push_to_animation_array(board.board_array[i][j]);
		}
	}
}

void grow_animate_nodes(int frame) {
	for (int i = 0; i < board.total_size; i++) {
		if (board.animation_array[i].top_x != 0 && board.animation_array[i].top_y != 0) {
			grow_animation(board.animation_array[i], frame);
		}
	}
}

void slide_animation_left_to_right(struct node from, struct node to, int current_frame, struct node* arr, int i) 
{
	int step = current_frame * 50;

	if (from.top_x + step > to.top_x) {
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
			al_map_rgb(0, 0, 0),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else {
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
			al_map_rgb(0, 0, 0),
			from.top_x + step + from.size / 2,
			from.top_y + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

void slide_animation_right_to_left(struct node from, struct node to, int current_frame) 
{
	int step = current_frame * 50;

	if (from.bottom_x - step < to.bottom_x) {
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
			al_map_rgb(0, 0, 0),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else {
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
			al_map_rgb(0, 0, 0),
			from.top_x - step + from.size / 2,
			from.top_y + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

void slide_animation_down_to_up(struct node from, struct node to, int current_frame) 
{
	int step = current_frame * 50;

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
			al_map_rgb(0, 0, 0),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else {
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
			al_map_rgb(0, 0, 0),
			from.top_x + from.size / 2,
			from.top_y - step + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

void slide_animation_up_to_down(struct node from, struct node to, int current_frame) 
{
	int step = current_frame * 50;

	if (from.top_y + step > to.top_y) {
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
			al_map_rgb(0, 0, 0),
			to.top_x + to.size / 2,
			to.top_y + to.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			to.value
		);
	}
	else {
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
			al_map_rgb(0, 0, 0),
			from.top_x + from.size / 2,
			from.top_y + step + from.size / 2 - cfg.font_size / 2,
			ALLEGRO_ALIGN_CENTER,
			"%d",
			from.value
		);
	}
}

void get_nodes_to_slide_animate_left_to_right(struct node* arr) 
{
	int idx = 0;

	for (int i = 0; i < board.y_size; i++) 
	{
		int m;
		for (m = 0; m < board.x_size; m++) {
			if (board.board_array[i][m].value != board.prev_board_array[i][m].value) break;
		}
		if (m == board.x_size) continue;

		struct node current_node = { 0 };
		for (int j = 0; j < board.x_size; j++) 
		{
			if (board.prev_board_array[i][j].value != 0)
			{
				current_node = board.prev_board_array[i][j];
				for (int k = j; k < board.x_size; k++)
				{
					if (current_node.top_x != board.board_array[i][k].top_x && board.board_array[i][k].value != 0)
					{
						arr[idx] = current_node;
						arr[idx + 1] = board.board_array[i][k];
						idx += 2;
						break;
					}
				}
			}
		}
	}
}

void get_nodes_to_slide_animate_right_to_left(struct node* arr) 
{
	int idx = 0;

	for (int i = 0; i < board.y_size; i++)
	{
		int m;
		for (m = 0; m < board.x_size; m++) {
			if (board.board_array[i][m].value != board.prev_board_array[i][m].value) break;
		}
		if (m == board.x_size) continue;

		struct node current_node = { 0 };
		for (int j = board.x_size-1; j >= 0; j--)
		{
			if (board.prev_board_array[i][j].value != 0)
			{
				current_node = board.prev_board_array[i][j];
				for (int k = j; k >= 0; k--)
				{
					if (current_node.top_x != board.board_array[i][k].top_x && board.board_array[i][k].value != 0)
					{
						arr[idx] = current_node;
						arr[idx + 1] = board.board_array[i][k];
						idx += 2;
						break;
					}
				}
			}
		}
	}
}