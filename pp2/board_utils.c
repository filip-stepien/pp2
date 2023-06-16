//! Zignorowanie ostrzeżeń Visual Studio generowanych przez natywne funkcje C
#define _CRT_SECURE_NO_WARNINGS

/**
 * @file board_utils.c
 * @brief Funkcje pomocnicze
 */

#include "game_includes.h"
#include "game_structures.h"
#include "board_utils.h"
#include "game_music.h"

/**
 * @brief Sprawdzenie czy na planszy nastąpił ruch
 * @return czy nastąpił ruch
 */
bool did_board_change()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			if (board.prev_board_array[i][j].value != board.board_array[i][j].value)
				return true;
		}
	}

	return false;
}

/**
 * @brief Sprawdzenie czy gra się zakończyła
 * @return czy gra się zakończyła
 */
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

/**
 * @brief Aktualizacja najlepszego wyniku
 */
void compare_and_set_best_score()
{
	if (points.counter > best_points.counter)
	{
		best_points.counter = points.counter;
	}
}

/**
 * @brief Zapisanie najlepszego wyniku do pliku
 */
void save_best_score()
{
	if (best_points.counter == points.counter && points.counter > 0)
	{
		FILE* save_file = NULL;
		fopen_s(&save_file, "score.txt", "w");
		if (save_file != NULL)
		{
			fprintf_s(save_file, "%d", best_points.counter);
			fclose(save_file);
		}
	}
}

/**
 * @brief Obsługa kliknięć
 */
void handle_mouse_clicks()
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);

	int left_click = state.buttons & 1;
	if (game.current_popup == NULL)
	{
		for (int i = 0; i < ui_buttons_length; i++)
		{
			if (state.x >= ui_buttons[i]->top_x && 
				state.x <= ui_buttons[i]->bottom_x && 
				state.y >= ui_buttons[i]->top_y && 
				state.y <= ui_buttons[i]->bottom_y &&
				ui_buttons[i]->visible)
			{
				al_draw_filled_rounded_rectangle(
					ui_buttons[i]->top_x,
					ui_buttons[i]->top_y,
					ui_buttons[i]->bottom_x,
					ui_buttons[i]->bottom_y,
					10, 10,
					al_map_rgba(0, 0, 0, 20)
				);


				if (left_click && ui_buttons[i]->on_click != NULL)
				{
					al_draw_filled_rounded_rectangle(
						ui_buttons[i]->top_x,
						ui_buttons[i]->top_y,
						ui_buttons[i]->bottom_x,
						ui_buttons[i]->bottom_y,
						10, 10,
						al_map_rgba(0, 0, 0, 10)
					);

					if (!animations.click_cooldown)
					{
						ui_buttons[i]->on_click();
						play_click_sound();
					}
				}
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < game.current_popup->buttons_length; i++)
		{
			if (state.x >= game.current_popup->buttons[i]->top_x && 
				state.x <= game.current_popup->buttons[i]->bottom_x && 
				state.y >= game.current_popup->buttons[i]->top_y &&
				state.y <= game.current_popup->buttons[i]->bottom_y &&
				game.current_popup->buttons[i]->visible)
			{
				al_draw_filled_rounded_rectangle(
					game.current_popup->buttons[i]->top_x,
					game.current_popup->buttons[i]->top_y,
					game.current_popup->buttons[i]->bottom_x,
					game.current_popup->buttons[i]->bottom_y,
					10, 10,
					al_map_rgba(0, 0, 0, 20)
				);


				if (left_click && game.current_popup->buttons[i]->on_click != NULL)
				{
					al_draw_filled_rounded_rectangle(
						game.current_popup->buttons[i]->top_x,
						game.current_popup->buttons[i]->top_y,
						game.current_popup->buttons[i]->bottom_x,
						game.current_popup->buttons[i]->bottom_y,
						10, 10,
						al_map_rgba(0, 0, 0, 20)
					);

					if (!animations.click_cooldown)
					{
						game.current_popup->buttons[i]->on_click();
						play_click_sound();
					}
				}
				break;
			}
		}
	}
}