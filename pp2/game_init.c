//! Zignorowanie ostrzeżeń Visual Studio generowanych przez natywne funkcje C
#define _CRT_SECURE_NO_WARNINGS

/**
 * @file game_init.c
 * @brief Inicjalizacja elementów gry
 */

#include "game_includes.h"
#include "game_init.h"
#include "game_structures.h"
#include "board_operations.h"
#include "game_music.h"
#include "board_utils.h"

/**
 * @brief Inicjalizacja dźwięków
 */
void initialize_sounds()
{
	al_reserve_samples(cfg.click_sounds_length + cfg.grow_sounds_length + 1);
	ALLEGRO_SAMPLE* music_sample = al_load_sample(cfg.music_filename);

	sounds.click_sounds = (ALLEGRO_SAMPLE_INSTANCE**)calloc(cfg.click_sounds_length, sizeof(ALLEGRO_SAMPLE_INSTANCE*));
	sounds.grow_sounds = (ALLEGRO_SAMPLE_INSTANCE**)calloc(cfg.grow_sounds_length, sizeof(ALLEGRO_SAMPLE_INSTANCE*));

	for (int i = 0; i < cfg.click_sounds_length; i++)
	{
		ALLEGRO_SAMPLE* sound_sample = al_load_sample(cfg.click_sounds_filenames[i]);
		sounds.click_sounds[i] = al_create_sample_instance(sound_sample);
		al_attach_sample_instance_to_mixer(sounds.click_sounds[i], al_get_default_mixer());
		al_set_sample_instance_gain(sounds.click_sounds[i], cfg.sfx_volume);
	}

	for (int i = 0; i < cfg.grow_sounds_length; i++)
	{
		ALLEGRO_SAMPLE* sound_sample = al_load_sample(cfg.grow_sounds_filenames[i]);
		sounds.grow_sounds[i] = al_create_sample_instance(sound_sample);
		al_attach_sample_instance_to_mixer(sounds.grow_sounds[i], al_get_default_mixer());
		al_set_sample_instance_gain(sounds.grow_sounds[i], cfg.sfx_volume);
	}

	sounds.music = al_create_sample_instance(music_sample);
	al_attach_sample_instance_to_mixer(sounds.music, al_get_default_mixer());
	al_set_sample_instance_gain(sounds.music, cfg.music_volume);
}

/**
 * @brief Inicjalizacja planszy gry
 */
void initialize_board()
{
	board.x_size = cfg.board_x_size;
	board.y_size = cfg.board_y_size;
	board.total_size = cfg.board_y_size * cfg.board_y_size;
	board.node_size = (cfg.width / cfg.board_x_size) - (cfg.board_gap * 2);
	board.gap = cfg.board_gap;
	board.first_turn = true;

	animations.grow_animation_array = (struct node*)calloc(board.total_size, sizeof(struct node));
	animations.slide_animation_array = (struct node*)calloc(board.total_size, sizeof(struct node));
	animations.done_sliding = true;

	board.board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));
	board.prev_board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));

	int i;
	for (i = 0; i < board.y_size; i++)
	{
		board.board_array[i] = (struct node*)calloc(board.x_size, sizeof(struct node));
		board.prev_board_array[i] = (struct node*)calloc(board.x_size, sizeof(struct node));
	}
}

/**
 * @brief Inicjalizacja klocków
 * @param render_x koordynata x, od której będzie rysowana plansza
 * @param render_y koordynata y, od której będzie rysowana plansza
 */
void initialize_nodes(int render_x, int render_y)
{
	int i, j;
	int x = render_x, y = render_y;

	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			struct node current_node = {
				0,
				x,
				y,
				x + board.node_size,
				y + board.node_size,
				board.node_size,
				al_map_rgb(255, 255, 255)
			};

			board.board_array[i][j] = current_node;
			x += board.node_size + board.gap;
		}

		x = render_x;
		y += board.node_size + board.gap;
	}
}

/**
 * @brief Czyszczenie po planszy gry
 */
void board_cleanup()
{
	int i;
	for (i = board.y_size - 1; i >= 0; i--)
		free(board.board_array[i]);

	free(board.board_array);
	board.board_array = NULL;

	free(animations.grow_animation_array);
	animations.grow_animation_array = NULL;
}

/**
 * @brief Inicjalizacja licznika wyniku
 * @param render_x koordynata x, od której będzie rysowany licznik wyniku
 * @param render_y koordynata y, od której będzie rysowany licznik wyniku
 * @param new_width szerokość licznika
 */
void initialize_points(int render_x, int render_y, int new_width)
{
	points.width = new_width;
	points.height = cfg.points_height;
	points.top_x = render_x;
	points.top_y = render_y;
	points.bottom_x = render_x + new_width;
	points.bottom_y = render_y + cfg.points_height;
	points.counter = 0;
}

/**
 * @brief Inicjalizacja licznika najlepszego wyniku
 * @param render_x koordynata x, od której będzie rysowany licznik najlepszego wyniku
 * @param render_y koordynata y, od której będzie rysowany licznik najlepszego wyniku
 * @param new_width szerokość licznika
 */
void initialize_best_points(int render_x, int render_y, int new_width)
{
	best_points.width = new_width;
	best_points.height = cfg.best_points_height;
	best_points.top_x = render_x;
	best_points.top_y = render_y;
	best_points.bottom_x = render_x + new_width;
	best_points.bottom_y = render_y + cfg.best_points_height;

	FILE* save_file = NULL;
	fopen_s(&save_file, "score.txt", "r");
	if (save_file == NULL)
	{
		best_points.counter = 0;
	}
	else
	{
		int best_score;
		fscanf_s(save_file, "%d", &best_score);
		best_points.counter = best_score;
		fclose(save_file);
	}
}

/**
 * @brief Efekt po wciśnieciu przycisku restart
 */
void restart_button_handler()
{
	animations.click_frame = 0;
	animations.click_cooldown = true;
	animations.frame = 0;
	save_best_score();
	reset_board();
	clear_slide_animation_array();
	clear_grow_animation_array();
	generate_random_node();
}

/**
 * @brief Inicjalizacja przycisku restart
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 * @param img_name nazwa pliku z ikoną
 */
void initialize_restart_button(int render_x, int render_y, char* img_name)
{
	restart_button.img = al_load_bitmap(img_name);
	restart_button.width = cfg.restart_button_width;
	restart_button.height = cfg.restart_button_height;
	restart_button.top_x = render_x;
	restart_button.top_y = render_y;
	restart_button.bottom_x = render_x + cfg.restart_button_width;
	restart_button.bottom_y = render_y + cfg.restart_button_height;
	restart_button.img_padding = cfg.restart_button_img_padding;
	restart_button.visible = true;
	restart_button.on_click = restart_button_handler;
	restart_button.bg_color = al_map_rgb(
		cfg.restart_button_bg_color_r,
		cfg.restart_button_bg_color_g,
		cfg.restart_button_bg_color_b
	);
}

/**
 * @brief Efekt po wciśnieciu przycisku menu
 */
void menu_button_handler()
{
	menu.visible = true;
	game.current_popup = &menu;
}

/**
 * @brief Inicjalizacja przycisku menu
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 * @param img_name nazwa pliku z ikoną
 */
void initialize_menu_button(int render_x, int render_y, char* img_name)
{
	menu_button.img = al_load_bitmap(img_name);
	menu_button.width = cfg.menu_button_width;
	menu_button.height = cfg.menu_button_height;
	menu_button.top_x = render_x;
	menu_button.top_y = render_y;
	menu_button.bottom_x = render_x + cfg.menu_button_width;
	menu_button.bottom_y = render_y + cfg.menu_button_height;
	menu_button.img_padding = cfg.menu_button_img_padding;
	menu_button.visible = true;
	menu_button.on_click = menu_button_handler;
	menu_button.bg_color = al_map_rgb(
		cfg.menu_button_bg_color_r,
		cfg.menu_button_bg_color_g,
		cfg.menu_button_bg_color_b
	);

}

/**
 * @brief Rozpoczęcie nowej gry
 */
void start_new_game()
{
	save_best_score();
	board_cleanup();
	initialize_board();

	int new_points_width = cfg.points_width - (cfg.board_x_size - 4) * (board.node_size / 16);
	int new_best_points_width = cfg.best_points_width - (cfg.board_x_size - 4) * (board.node_size / 16);
	int center_x = (cfg.width - (board.node_size * board.x_size) - (board.gap * (board.x_size - 1))) / 2;
	int best_points_x = center_x + new_points_width + board.gap;
	int points_center_y = (cfg.height - cfg.points_height - (board.gap * (board.y_size + 1)) - (board.node_size * board.y_size)) / 2;
	int board_center_y = points_center_y + cfg.points_height + board.gap;
	int restart_button_x = best_points_x + new_best_points_width + board.gap;
	int menu_button_x = restart_button_x + cfg.restart_button_width + board.gap;
	int restart_button_y = points_center_y + cfg.best_points_height - cfg.restart_button_height;
	int menu_button_y = points_center_y + cfg.best_points_height - cfg.menu_button_height;

	initialize_points(center_x, points_center_y, new_points_width);
	initialize_best_points(best_points_x, points_center_y, new_best_points_width);
	initialize_nodes(center_x, board_center_y);
	initialize_restart_button(restart_button_x, restart_button_y, cfg.restart_button_filename);
	initialize_menu_button(menu_button_x, menu_button_y, cfg.menu_button_filename);

	srand(time(NULL));
	generate_random_node();

	back.visible = true;
	animations.frame = 0;
}

/**
 * @brief Efekt po wciśnięciu przycisku restart w oknie końca gry
 */
void end_button_handler()
{
	restart_button_handler();
	game.current_popup = NULL;
	end.visible = false;
}

/**
 * @brief Inicjalizacja przycisku restartu w oknie końca gry
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 */
void initialize_end_button(int render_x, int render_y)
{
	new_game.img = NULL;
	new_game.width = cfg.option_width;
	new_game.height = cfg.option_height;
	new_game.top_x = render_x;
	new_game.top_y = render_y;
	new_game.bottom_x = render_x + cfg.option_width;
	new_game.bottom_y = render_y + cfg.option_height;
	new_game.img_padding = 0;
	new_game.visible = true;
	new_game.on_click = end_button_handler;
	new_game.bg_color = al_map_rgb(
		cfg.option_bg_color_r,
		cfg.option_bg_color_g,
		cfg.option_bg_color_b
	);
}

/**
 * @brief Inicjalizacja okna końca gry
 */
void initialize_end_popup()
{
	int center_x = (cfg.width - cfg.end_popup_width) / 2;
	int center_y = (cfg.height - cfg.end_popup_height) / 2;

	end.width = cfg.end_popup_width;
	end.height = cfg.end_popup_height;
	end.top_x = center_x;
	end.top_y = center_y;
	end.bottom_x = center_x + cfg.end_popup_width;
	end.bottom_y = center_y + cfg.end_popup_height;
	end.visible = false;
	end.bg_color = al_map_rgba(
		cfg.end_bg_color_r,
		cfg.end_bg_color_g,
		cfg.end_bg_color_b,
		cfg.end_bg_color_a
	);

	end.buttons_length = 1;
	end.buttons = (struct button**)calloc(end.buttons_length, sizeof(struct button*));

	end.buttons[0] = &new_game;
}

/**
 * @brief Wspólny efekt przycisków od wyboru wielkości planszy
 */
void common_option_handler()
{
	menu.visible = false;
	game.current_popup = NULL;
	game.started = true;

	start_new_game();
}

/**
 * @brief Efekt przycisku wyboru planszy (opcja 4x4)
 */
void option_4x4_hanlder()
{
	cfg.board_x_size = cfg.board_y_size = 4;
	common_option_handler();
}

/**
 * @brief Efekt przycisku wyboru planszy (opcja 5x5)
 */
void option_5x5_hanlder()
{
	cfg.board_x_size = cfg.board_y_size = 5;
	common_option_handler();
}

/**
 * @brief Efekt przycisku wyboru planszy (opcja 6x6)
 */
void option_6x6_hanlder()
{
	cfg.board_x_size = cfg.board_y_size = 6;
	common_option_handler();
}

/**
 * @brief Efekt przycisku powrotu do gry
 */
void back_handler()
{
	menu.visible = false;
	game.current_popup = NULL;
}

/**
 * @brief Efekt przycisku od dźwięku
 */
void mute_button_handler()
{
	animations.click_cooldown = true;
	animations.click_frame = 0;
	if (game.muted)
	{
		mute.img = al_load_bitmap(cfg.mute_button_filenames[0]);
		game.muted = false;
		unmute_game();
	}
	else
	{
		mute.img = al_load_bitmap(cfg.mute_button_filenames[1]);
		game.muted = true;
		mute_game();
	}
}

/**
 * @brief Inicjalizacja przycisku od dźwięku
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 */
void initialize_mute_button(int render_x, int render_y)
{
	mute.img = al_load_bitmap(cfg.mute_button_filenames[0]);
	mute.width = cfg.mute_button_width;
	mute.height = cfg.mute_button_height;
	mute.top_x = render_x;
	mute.top_y = render_y;
	mute.bottom_x = render_x + cfg.mute_button_width;
	mute.bottom_y = render_y + cfg.mute_button_height;
	mute.img_padding = 0;
	mute.visible = true;
	mute.on_click = mute_button_handler;
	mute.bg_color = al_map_rgb(
		cfg.mute_button_bg_color_r,
		cfg.mute_button_bg_color_g,
		cfg.mute_button_bg_color_b
	);
}

/**
 * @brief Inicjalizacja przycisków w menu
 * @param render_x koordynata x, od której będą rysowane przyciski
 * @param render_y koordynata y, od której będą rysowane przyciski
 */
void initialize_menu_option_buttons(int render_x, int render_y)
{
	button_4x4.img = button_5x5.img = button_6x6.img = back.img = NULL;
	button_4x4.width = button_5x5.width = button_6x6.width = back.width = cfg.option_width;
	button_4x4.height = button_5x5.height = button_6x6.height = back.height = cfg.option_height;
	button_4x4.img_padding = button_5x5.img_padding = button_6x6.img_padding = back.img_padding = 0;
	button_4x4.visible = button_5x5.visible = button_6x6.visible = back.visible = true;
	back.visible = false;
	button_4x4.on_click = option_4x4_hanlder;
	button_5x5.on_click = option_5x5_hanlder;
	button_6x6.on_click = option_6x6_hanlder;
	back.on_click = back_handler;
	button_4x4.bg_color = button_5x5.bg_color = button_6x6.bg_color = back.bg_color = al_map_rgb(
		cfg.option_text_color_r, 
		cfg.option_text_color_g, 
		cfg.option_text_color_b
	);

	button_4x4.top_x = render_x;
	button_4x4.top_y = render_y;
	button_4x4.bottom_x = render_x + cfg.option_width;
	button_4x4.bottom_y = render_y + cfg.option_height;

	button_5x5.top_x = render_x;
	button_5x5.top_y = button_4x4.bottom_y + cfg.option_gap;
	button_5x5.bottom_x = render_x + cfg.option_width;
	button_5x5.bottom_y = button_4x4.bottom_y + cfg.option_gap + cfg.option_height;

	button_6x6.top_x = render_x;
	button_6x6.top_y = button_5x5.bottom_y + cfg.option_gap;
	button_6x6.bottom_x = render_x + cfg.option_width;
	button_6x6.bottom_y = button_5x5.bottom_y + cfg.option_gap + cfg.option_height;

	back.top_x = render_x;
	back.top_y = button_6x6.bottom_y + cfg.option_gap;
	back.bottom_x = render_x + cfg.option_width;
	back.bottom_y = button_6x6.bottom_y + cfg.option_gap + cfg.option_height;
}

/**
 * @brief Inicjalizacja okna menu
 */
void initialize_menu_popup()
{
	menu.width = cfg.width;
	menu.height = cfg.height;
	menu.top_x = 0;
	menu.top_y = 0;
	menu.bottom_x = menu.top_x + cfg.width;
	menu.bottom_y = menu.bottom_x + cfg.height;
	menu.bg_color = al_map_rgb(
		cfg.menu_bg_color_r,
		cfg.menu_bg_color_g,
		cfg.menu_bg_color_b
	);
	menu.visible = true;

	menu.buttons_length = 5;
	menu.buttons = (struct button**)calloc(5, sizeof(struct button*));
	menu.buttons[0] = &button_4x4;
	menu.buttons[1] = &button_5x5;
	menu.buttons[2] = &button_6x6;
	menu.buttons[3] = &back;
	menu.buttons[4] = &mute;

	game.current_popup = &menu;
}