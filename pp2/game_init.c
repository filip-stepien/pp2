#define _CRT_SECURE_NO_WARNINGS

#include "game_includes.h"
#include "game_init.h"
#include "game_structures.h"
#include "board_operations.h"

// funkcja inicjuj¹ca planszê gry
void initialize_board()
{
	// przypisanie strukturze board zmiennych ze struktury config zawieraj¹c¹ konfiguracjê gry
	board.x_size = cfg.board_x_size;
	board.y_size = cfg.board_y_size;
	board.total_size = cfg.board_y_size * cfg.board_y_size;
	board.node_size = (cfg.width / cfg.board_x_size) - (cfg.board_gap * 2);
	board.gap = cfg.board_gap;
	board.first_turn = true;

	animations.grow_animation_array = (struct node*)calloc(board.total_size, sizeof(struct node));
	animations.slide_animation_array = (struct node*)calloc(board.total_size, sizeof(struct node));
	animations.done_sliding = true;

	// dynamiczna alokacja pamiêci dla planszy z klockami
	board.board_array = (struct node**)calloc(board.y_size, sizeof(struct node*));
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

	free(animations.grow_animation_array);
	animations.grow_animation_array = NULL;
}

// funkcja inicjujaca liczninik punktów
void initialize_points(int render_x, int render_y, int new_width)
{
	// przypisanie strukturze points zmiennych z parametrów funkcji
	points.width = new_width;
	points.height = cfg.points_height;
	points.top_x = render_x;
	points.top_y = render_y;
	points.bottom_x = render_x + new_width;
	points.bottom_y = render_y + cfg.points_height;
	points.counter = 0;
}

void initialize_best_points(int render_x, int render_y, int new_width)
{
	// przypisanie strukturze points zmiennych z parametrów funkcji
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

void restart_button_handler()
{
	animations.frame = 0;
	animations.click_cooldown = true;
	reset_board();
	clear_slide_animation_array();
	clear_grow_animation_array();
	generate_random_node();
}

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

void menu_button_handler()
{
	menu.visible = true;
	game.current_popup = &menu;
}

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

void start_new_game()
{
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

	initialize_points(center_x, points_center_y, new_points_width);             // inicjalizacja licznika punktów
	initialize_best_points(best_points_x, points_center_y, new_best_points_width);
	initialize_nodes(center_x, board_center_y);               // inicjalizacja klocków
	initialize_restart_button(restart_button_x, restart_button_y, cfg.restart_button_filename);
	initialize_menu_button(menu_button_x, menu_button_y, cfg.menu_button_filename);

	srand(time(NULL));
	generate_random_node();     // generowanie losowego klocka

	back.visible = true;
	animations.frame = 0;
}

void common_option_handler()
{
	menu.visible = false;
	game.current_popup = NULL;
	game.started = true;

	start_new_game();
}

void option_4x4_hanlder()
{
	cfg.board_x_size = cfg.board_y_size = 4;
	common_option_handler();
}

void option_5x5_hanlder()
{
	cfg.board_x_size = cfg.board_y_size = 5;
	common_option_handler();
}

void option_6x6_hanlder()
{
	cfg.board_x_size = cfg.board_y_size = 6;
	common_option_handler();
}

void back_handler()
{
	menu.visible = false;
	game.current_popup = NULL;
}

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

	menu.buttons_length = 4;
	menu.buttons = (struct button**)calloc(4, sizeof(struct button*));
	menu.buttons[0] = &button_4x4;
	menu.buttons[1] = &button_5x5;
	menu.buttons[2] = &button_6x6;
	menu.buttons[3] = &back;

	game.current_popup = &menu;
}