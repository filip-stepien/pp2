/**
 * @file board_movement.c
 * @brief Przesuwanie klocków
 */

#include "game_includes.h"
#include "board_movement.h"
#include "game_structures.h"
#include "board_operations.h"

/**
 * @brief Przesuwanie klocków w dół
 */
void move_down() {
	int i, j, k;
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			for (k = 0; k < board.y_size - 1; k++) 
			{
				if (board.board_array[k + 1][j].value == 0 && board.board_array[k][j].value != 0) 
				{
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
				}
			}
		}
	}
}

/**
 * @brief Przesuwanie klocków do góry
 */
void move_up() {
	int i, j, k;
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			for (k = 1; k < board.y_size; k++) 
			{
				if (board.board_array[k - 1][j].value == 0 && board.board_array[k][j].value != 0) 
				{
					board.board_array[k - 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
				}
			}
		}
	}
}

/**
 * @brief Przesuwanie klocków w prawo
 */
void move_right() {
	int i, j, k;
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			for (k = 0; k < board.y_size - 1; k++) 
			{
				if (board.board_array[i][k + 1].value == 0 && board.board_array[i][k].value != 0)
				{
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
				}
			}
		}
	}
}

/**
 * @brief Przesuwanie klocków w lewo
 */
void move_left() {
	int i, j, k;
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			for (k = 1; k < board.y_size; k++) 
			{
				if (board.board_array[i][k - 1].value == 0 && board.board_array[i][k].value != 0) 
				{
					board.board_array[i][k - 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
				}
			}
		}
	}
}

/**
 * @brief Łączenie klocków w dół
 */
void merge_down() 
{
	int i, j, stacked = -1;
	save_board();
	for (j = 0; j < board.x_size; j++) 
	{
		for (i = board.y_size - 2; i >= 0; i--) 
		{
			if (board.board_array[i][j].value != 0 && i != stacked) 
			{
				int k = i;
				while (k < 2 && board.board_array[k + 1][j].value == 0) 
				{
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
					k++;
				}
				if (board.board_array[k + 1][j].value == board.board_array[k][j].value) 
				{
					board.board_array[k + 1][j].value *= 2;
					board.board_array[k][j].value = 0;

					points.counter += board.board_array[k + 1][j].value;

					compare_and_set_best_score();

					stacked = k + 1;
				}
			}
		}
		stacked = -1;
	}
}

/**
 * @brief Łączenie klocków do góry
 */
void merge_up()
{
	int i, j, stacked = -1;
	save_board();
	for (j = 0; j < board.x_size; j++) 
	{
		for (i = 0; i < board.y_size - 1; i++)
		{
			if (board.board_array[i][j].value != 0 && i != stacked) 
			{
				int k = i;
				while (k < 2 && board.board_array[k + 1][j].value == 0) 
				{
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
					k++;
				}
				if (board.board_array[k + 1][j].value == board.board_array[k][j].value) 
				{
					board.board_array[k + 1][j].value *= 2;
					board.board_array[k][j].value = 0;

					points.counter += board.board_array[k + 1][j].value;

					compare_and_set_best_score();

					stacked = k + 1;
				}
			}
		}
		stacked = -1;
	}
}

/**
 * @brief Łączenie klocków w lewo
 */
void merge_left() 
{
	int i, j, stacked = -1;
	save_board();
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size - 1; j++) 
		{
			if (board.board_array[i][j].value != 0 && j != stacked) 
			{
				int k = j;
				while (k < 2 && board.board_array[i][k + 1].value == 0) 
				{
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
					k++;
				}
				if (board.board_array[i][k + 1].value == board.board_array[i][k].value) 
				{
					board.board_array[i][k + 1].value *= 2;
					board.board_array[i][k].value = 0;

					points.counter += board.board_array[i][k + 1].value;

					compare_and_set_best_score();

					stacked = k + 1;
				}
			}
		}
		stacked = -1;
	}
}

/**
 * @brief Łączenie klocków w prawo
 */
void merge_right() 
{
	int i, j, stacked = -1;
	save_board();
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = board.x_size - 2; j >= 0; j--) 
		{
			if (board.board_array[i][j].value != 0 && j != stacked) 
			{
				int k = j;
				while (k < 2 && board.board_array[i][k + 1].value == 0) 
				{
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
					k++;
				}
				if (board.board_array[i][k + 1].value == board.board_array[i][k].value) 
				{
					board.board_array[i][k + 1].value *= 2;
					board.board_array[i][k].value = 0;

					points.counter += board.board_array[i][k + 1].value;

					compare_and_set_best_score();

					stacked = k + 1;
				}
			}
		}
		stacked = -1;
	}
}