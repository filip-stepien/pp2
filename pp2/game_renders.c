//! Zignorowanie ostrzeżeń Visual Studio generowanych przez natywne funkcje C
#define _CRT_SECURE_NO_WARNINGS

/**
 * @file game_renders.c
 * @brief Rysowanie elementów gry
 */

#include "game_includes.h"
#include "game_renders.h"
#include "game_structures.h"

#include <stdio.h>

/**
 * @brief Rysowanie planszy
 */
void draw_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			struct node current_node = board.board_array[i][j];

			al_draw_filled_rounded_rectangle(
				current_node.top_x,
				current_node.top_y,
				current_node.bottom_x,
				current_node.bottom_y,
				10, 10,
				current_node.color
			);

			if (current_node.value)
			{
				al_draw_textf(
					game.font,
					al_map_rgb(cfg.node_text_color_r, cfg.node_text_color_g, cfg.node_text_color_b),
					current_node.top_x + current_node.size / 2,
					current_node.top_y + current_node.size / 2 - cfg.font_size / 2,
					ALLEGRO_ALIGN_CENTER,
					"%d",
					current_node.value
				);
			}
		}
	}
}

/**
 * @brief Rysowanie wyniku
 */
void draw_points()
{
	al_draw_filled_rounded_rectangle(
		points.top_x,
		points.top_y,
		points.bottom_x,
		points.bottom_y,
		10, 10,
		al_map_rgb(cfg.points_bg_color_r, cfg.points_bg_color_g, cfg.points_bg_color_b)
	);

	al_draw_multiline_textf(
		game.points_font,
		al_map_rgb(cfg.points_text_color_r, cfg.points_text_color_g, cfg.points_text_color_b),
		points.top_x + points.width / 2,
		points.top_y + points.height / 2 - cfg.font_size - al_get_font_descent(game.points_font) / 2,
		points.width - 2 * board.gap,
		al_get_font_line_height(game.points_font) + cfg.points_text_leading,
		ALLEGRO_ALIGN_CENTER,
		"Wynik\n%d",
		points.counter
	);
}

/**
 * @brief Rysowanie najlepszego wyniku
 */
void draw_best_points()
{
	al_draw_filled_rounded_rectangle(
		best_points.top_x,
		best_points.top_y,
		best_points.bottom_x,
		best_points.bottom_y,
		10, 10,
		al_map_rgb(cfg.points_bg_color_r, cfg.points_bg_color_g, cfg.points_bg_color_b)
	);

	al_draw_multiline_textf(
		game.points_font,
		al_map_rgb(cfg.points_text_color_r, cfg.points_text_color_g, cfg.points_text_color_b),
		best_points.top_x + best_points.width / 2,
		best_points.top_y + best_points.height / 2 - cfg.font_size - al_get_font_descent(game.points_font) / 2,
		best_points.width - 2 * board.gap,
		al_get_font_line_height(game.points_font) + cfg.points_text_leading,
		ALLEGRO_ALIGN_CENTER,
		"Najlepszy\n%d",
		best_points.counter
	);
}

/**
 * @brief Rysowanie przycisku menu
 */
void draw_menu_button()
{
	al_draw_filled_rounded_rectangle(
		menu_button.top_x,
		menu_button.top_y,
		menu_button.bottom_x,
		menu_button.bottom_y,
		10, 10,
		menu_button.bg_color
	);

	if (menu_button.img != NULL)
	{
		al_draw_bitmap(
			menu_button.img,
			menu_button.top_x + menu_button.img_padding,
			menu_button.top_y + menu_button.img_padding,
			0
		);
	}
}

/**
 * @brief Rysowanie przycisku restart
 */
void draw_restart_button()
{
	al_draw_filled_rounded_rectangle(
		restart_button.top_x,
		restart_button.top_y,
		restart_button.bottom_x,
		restart_button.bottom_y,
		10, 10,
		restart_button.bg_color
	);

	if (restart_button.img != NULL)
	{
		al_draw_bitmap(
			restart_button.img,
			restart_button.top_x + restart_button.img_padding,
			restart_button.top_y + restart_button.img_padding,
			0
		);
	}
}

/**
 * @brief Rysowanie okna menu
 */
void draw_menu_popup()
{
	int title_width = al_get_text_width(game.title_font, "2048");
	int title_center_x = cfg.width / 2;
	char* options[5] = { "4 x 4", "5 x 5", "6 x 6", "Anuluj", ""};

	al_draw_filled_rectangle(
		menu.top_x,
		menu.top_y,
		menu.bottom_x,
		menu.bottom_y,
		al_map_rgb(
			cfg.menu_bg_color_r,
			cfg.menu_bg_color_g,
			cfg.menu_bg_color_b
		)
	);

	al_draw_text(
		game.title_font, 
		al_map_rgb(
			cfg.title_text_color_r,
			cfg.title_text_color_g,
			cfg.title_text_color_b
		), 
		title_center_x, 
		100, 
		ALLEGRO_ALIGN_CENTRE,
		"2048"
	);

	al_draw_text(
		game.font,
		al_map_rgb(
			cfg.title_text_color_r,
			cfg.title_text_color_g,
			cfg.title_text_color_b
		),
		title_center_x,
		250,
		ALLEGRO_ALIGN_CENTRE,
		"Rozmiar planszy"
	);
	
	for (int i = 0; i < menu.buttons_length; i++)
	{
		if (menu.buttons[i]->visible)
		{
			al_draw_filled_rounded_rectangle(
				menu.buttons[i]->top_x,
				menu.buttons[i]->top_y,
				menu.buttons[i]->bottom_x,
				menu.buttons[i]->bottom_y,
				10, 10,
				al_map_rgb(
					cfg.option_bg_color_r,
					cfg.option_bg_color_g,
					cfg.option_bg_color_b
				)
			);

			al_draw_text(
				game.option_font,
				al_map_rgb(
					cfg.option_text_color_r,
					cfg.option_text_color_g,
					cfg.option_text_color_b
				),
				menu.buttons[i]->top_x + menu.buttons[i]->width / 2,
				menu.buttons[i]->top_y + menu.buttons[i]->height / 2 - cfg.option_font_size / 2,
				ALLEGRO_ALIGN_CENTRE,
				options[i]
			);
		}
	}
}

/**
 * @brief Rysowanie okna końca gry
 */
void draw_end_popup()
{
	al_draw_filled_rounded_rectangle(
		end.top_x,
		end.top_y,
		end.bottom_x,
		end.bottom_y,
		10, 10,
		end.bg_color
	);

	al_draw_textf(
		game.title_font,
		al_map_rgb(
			cfg.end_title_color_r,
			cfg.end_title_color_g,
			cfg.end_title_color_b
		),
		end.top_x + end.width / 2,
		end.top_y + cfg.end_popup_padding,
		ALLEGRO_ALIGN_CENTRE,
		"Koniec gry!"
	);

	al_draw_filled_rounded_rectangle(
		end.buttons[0]->top_x,
		end.buttons[0]->top_y,
		end.buttons[0]->bottom_x,
		end.buttons[0]->bottom_y,
		10, 10,
		al_map_rgb(
			cfg.end_button_bg_color_r,
			cfg.end_button_bg_color_g,
			cfg.end_button_bg_color_b
		)
	);

	al_draw_text(
		game.option_font,
		al_map_rgb(
			cfg.end_button_text_color_r,
			cfg.end_button_text_color_g,
			cfg.end_button_text_color_b
		),
		end.buttons[0]->top_x + menu.buttons[0]->width / 2,
		end.buttons[0]->top_y + menu.buttons[0]->height / 2 - cfg.option_font_size / 2,
		ALLEGRO_ALIGN_CENTRE,
		"Restart"
	);
}

/**
 * @brief Rysowanie przycisku od wyciszenia dźwięków
 */
void draw_mute_button()
{
	al_draw_filled_rounded_rectangle(
		mute.top_x,
		mute.top_y,
		mute.bottom_x,
		mute.bottom_y,
		10, 10,
		mute.bg_color
	);

	if (mute.img != NULL)
	{
		al_draw_bitmap(
			mute.img,
			mute.top_x + mute.img_padding,
			mute.top_y + mute.img_padding,
			0
		);
	}
}

/**
 * @brief Wyczyszczenie ekranu gry
 */
void clear()
{
	al_draw_filled_rectangle(
		0,
		0,
		cfg.width,
		cfg.height,
		al_map_rgb(cfg.bg_color_r, cfg.bg_color_g, cfg.bg_color_b)
	);
}