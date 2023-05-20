#define _CRT_SECURE_NO_WARNINGS

#include "game_includes.h"
#include "game_init.h"
#include "game_structures.h"

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

	free(menu.buttons);
	menu.buttons = NULL;
	menu.buttons_length = 0;

	if (best_points.counter == points.counter && points.counter > 0)
	{
		FILE* save_file = fopen("score.txt", "w");
		if (save_file != NULL)
		{
			fprintf_s(save_file, "%d", best_points.counter);
			fclose(save_file);
		}
	}
}

// funkcja inicjujaca liczninik punktów
void initialize_points(int render_x, int render_y)
{
	// przypisanie strukturze points zmiennych z parametrów funkcji
	points.width = cfg.points_width;
	points.height = cfg.points_height;
	points.top_x = render_x;
	points.top_y = render_y;
	points.bottom_x = render_x + cfg.points_width;
	points.bottom_y = render_y + cfg.points_height;
	points.counter = 0;
}

void initialize_best_points(int render_x, int render_y)
{
	// przypisanie strukturze points zmiennych z parametrów funkcji
	best_points.width = cfg.best_points_width;
	best_points.height = cfg.best_points_height;
	best_points.top_x = render_x;
	best_points.top_y = render_y;
	best_points.bottom_x = render_x + cfg.best_points_width;
	best_points.bottom_y = render_y + cfg.best_points_height;

	FILE* save_file = fopen("score.txt", "r");
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
	restart_button.on_click = restart_button_handler;
	restart_button.bg_color = al_map_rgb(
		cfg.restart_button_bg_color_r,
		cfg.restart_button_bg_color_g,
		cfg.restart_button_bg_color_b
	);
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
	menu_button.on_click = NULL;
	menu_button.bg_color = al_map_rgb(
		cfg.menu_button_bg_color_r,
		cfg.menu_button_bg_color_g,
		cfg.menu_button_bg_color_b
	);

}

void debug_handler()
{
	menu.visible = false;
	game.current_popup = NULL;
}

void initialize_menu_option_buttons(int render_x, int render_y)
{
	button_4x4.img = button_5x5.img = button_6x6.img = NULL;
	button_4x4.width = button_5x5.width = button_6x6.width = cfg.option_width;
	button_4x4.height = button_5x5.height = button_6x6.height = cfg.option_height;
	button_4x4.img_padding = button_5x5.img_padding = button_6x6.img_padding = 0;
	button_4x4.on_click = button_5x5.on_click = button_6x6.on_click = debug_handler;
	button_4x4.bg_color = button_5x5.bg_color = button_6x6.bg_color = al_map_rgb(
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

	menu.buttons_length = 3;
	menu.buttons = (struct button**)calloc(menu.buttons_length, sizeof(struct button*));
	menu.buttons[0] = &button_4x4;
	menu.buttons[1] = &button_5x5;
	menu.buttons[2] = &button_6x6;

	game.current_popup = &menu;
}