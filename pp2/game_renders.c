#define _CRT_SECURE_NO_WARNINGS

#include "game_includes.h"
#include "game_renders.h"
#include "game_structures.h"

#include <stdio.h>

// funkcja rysuj�ca plansz�
void draw_board()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			struct node current_node = board.board_array[i][j];	// aktualnie rysowany klocek

			// rysowanie klocka, wykorzystuj�c pola wygenerowane funkcj� generate_board()
			al_draw_filled_rounded_rectangle(
				current_node.top_x,
				current_node.top_y,
				current_node.bottom_x,
				current_node.bottom_y,
				10, 10,
				current_node.color
			);

			if (current_node.value)	// je�eli warto�� klocka != 0
			{
				// rysowanie warto�ci wewn�trz klocka
				al_draw_textf(
					game.font,
					al_map_rgb(0, 0, 0),
					current_node.top_x + current_node.size / 2,						// po�owa klocka na osi X = g�rne x + po�owa d�ugo�ci boku
					current_node.top_y + current_node.size / 2 - cfg.font_size / 2,	// po�owa klocka na osi Y = y + po�owa d�ugo�ci boku, dalsza cz�� - patrz ni�ej
					ALLEGRO_ALIGN_CENTER,	// wycentrowanie tekstu przez allegro, ale tylko w osi X, w osi Y nale�y odj�� od y po�ow� wielko�ci czcionki
					"%d",					// ci�g formatuj�cy rysowany tekst
					current_node.value		// tekst do narysowania
				);
			}
		}
	}
}

// funkcja rysuj�ca licznik punkt�w
void draw_points()
{
	int points_length = snprintf(NULL, 0, "%d", points.counter) + strlen("Wynik: ");	// obliczenie ilo�ci pami�ci na �a�cuch z wynikiem
	char* points_string = (char*)malloc(points_length + 1);		// rezerwacja pami�ci dla �a�cucha z wynikiem

	if (points_string != NULL)
		sprintf(points_string, "Wynik: %d", points.counter);	// zamiana wyniku cyfrowego na �a�cuch

	int font_size = cfg.font_size;	// aktualny rozmiar czcionki
	while (al_get_text_width(game.font, points_string) > points.width)	// dop�ki czcionka nie mie�ci si� w liczniku
		game.font = al_load_font("Arial.ttf", font_size--, NULL);		// zmniejszaj rozmiar czcionki

	// rysowanie licznika
	al_draw_rectangle(
		points.top_x,
		points.top_y,
		points.bottom_x,
		points.bottom_y,
		al_map_rgb(255, 255, 255),
		1
	);

	// rysowanie punkt�w
	al_draw_text(
		game.font, 
		al_map_rgb(255, 255, 255), 
		points.top_x + points.width / 2,
		points.top_y + points.height / 2 - cfg.font_size / 2,
		ALLEGRO_ALIGN_CENTER,
		points_string
	);

	al_load_font("Arial.ttf", cfg.font_size, NULL);	// przywr�cenie domy�lnego rozmiaru czcionki
	free(points_string);	// zwolnienie pami�ci �a�cucha z wynikiem
}

// funkcja czyszcz�ca ekran gry
void clear()
{
	// prostok�t o kolorze t�a jest rysowany na ca�ym oknie
	al_draw_filled_rectangle(
		0,
		0,
		cfg.width,
		cfg.height,
		al_map_rgb(cfg.bg_color_r, cfg.bg_color_g, cfg.bg_color_b)
	);
}