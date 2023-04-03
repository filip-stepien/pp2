#include "game_structures.h"
#include "board_utils.h"

extern struct game_board board;

// funkcja sprawdzaj¹ca czy na planszy nast¹pi³ ruch
bool did_board_change()
{
	int i, j;
	for (i = 0; i < board.y_size; i++)
	{
		for (j = 0; j < board.x_size; j++)
		{
			if (board.prev_board_array[i][j].value != board.board_array[i][j].value)	// porównanie planszy aktualnej z zapisan¹
				return true;
		}
	}

	return false;
}

// funkcja sprawdzaj¹ca czy mo¿liwe jest wykonanie ruchu na planszy
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