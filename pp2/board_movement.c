#include "game_includes.h"
#include "board_movement.h"
#include "game_structures.h"
#include "board_operations.h"

// funkcja przesuwaj¹ce klocki w dó³
void move_down() {
	int i, j, k;
	// operacja wykonywana dla ka¿dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj nastêpny klocek a¿ do koñca kolumny
			for (k = 0; k < board.y_size - 1; k++) 
			{
				// je¿eli nastêpny klocek w kolumnie jest równy 0 i aktualny nie jest równy 0
				if (board.board_array[k + 1][j].value == 0 && board.board_array[k][j].value != 0) 
				{
					// zamieñ ich wartoœci = zamieñ ich miejscami
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
				}
			}
		}
	}
}

// funkcja przesuwaj¹ce klocki do góry
void move_up() {
	int i, j, k;
	// operacja wykonywana dla ka¿dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj poprzedni klocek a¿ do koñca kolumny
			for (k = 1; k < board.y_size; k++) 
			{
				// je¿eli poprzedni klocek w kolumnie jest równy 0 i aktualny nie jest równy 0
				if (board.board_array[k - 1][j].value == 0 && board.board_array[k][j].value != 0) 
				{
					// zamieñ ich wartoœci = zamieñ ich miejscami
					board.board_array[k - 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
				}
			}
		}
	}
}

// funkcja przesuwaj¹ce klocki w prawo
void move_right() {
	int i, j, k;
	// operacja wykonywana dla ka¿dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj nastêpny klocek a¿ do koñca wiersza
			for (k = 0; k < board.y_size - 1; k++) 
			{
				// je¿eli nastêpny klocek w wierszu jest równy 0 i aktualny nie jest równy 0
				if (board.board_array[i][k + 1].value == 0 && board.board_array[i][k].value != 0)
				{
					// zamieñ ich wartoœci = zamieñ ich miejscami
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
				}
			}
		}
	}
}

// funkcja przesuwaj¹ce klocki w lewo
void move_left() {
	int i, j, k;
	// operacja wykonywana dla ka¿dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj poprzedni klocek a¿ do koñca wiersza
			for (k = 1; k < board.y_size; k++) 
			{
				// je¿eli poprzedni klocek w wierszu jest równy 0 i aktualny nie jest równy 0
				if (board.board_array[i][k - 1].value == 0 && board.board_array[i][k].value != 0) 
				{
					// zamieñ ich wartoœci = zamieñ ich miejscami
					board.board_array[i][k - 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
				}
			}
		}
	}
}

// funkcja ³¹cz¹ca klocki w dó³
void merge_down() 
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (j = 0; j < board.x_size; j++) 
	{
		// ³¹czenie klocków od do³u kolumny
		for (i = board.y_size - 2; i >= 0; i--) 
		{
			// je¿eli klocek nie jest równy zero i nie zosta³ ju¿ wczeœniej po³¹czony
			if (board.board_array[i][j].value != 0 && i != stacked) 
			{
				int k = i;	// przeszukiwanie w do³ kolumny od aktualnego elementu
				// dopóki kolumna siê nie skoñczy³a, a nastêpny klocek jest równy 0
				while (k < 2 && board.board_array[k + 1][j].value == 0) 
				{
					// zamiana klocków miejscami
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
					k++;
				}
				// je¿eli napotkany element ma tak¹ sam¹ wartoœæ
				if (board.board_array[k + 1][j].value == board.board_array[k][j].value) 
				{
					// po³¹cz klocki
					board.board_array[k + 1][j].value *= 2;
					board.board_array[k][j].value = 0;

					// dodaj po³¹czenie do wyniku
					points.counter += board.board_array[k + 1][j].value;

					// ustaw znacznik po³¹czenia na bie¿¹cy element, aby nie móg³ byæ ponownie po³¹czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po³¹czenia
		stacked = -1;
	}
}

void merge_up()
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (j = 0; j < board.x_size; j++) 
	{
		// ³¹czenie klocków od góry kolumny
		for (i = 0; i < board.y_size - 1; i++)
		{
			// je¿eli klocek nie jest równy zero i nie zosta³ ju¿ wczeœniej po³¹czony
			if (board.board_array[i][j].value != 0 && i != stacked) 
			{
				int k = i;	// przeszukiwanie w górê kolumny od aktualnego elementu
				// dopóki kolumna siê nie skoñczy³a, a nastêpny klocek jest równy 0
				while (k < 2 && board.board_array[k + 1][j].value == 0) 
				{
					// zamiana klocków miejscami
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
					k++;
				}
				// je¿eli napotkany element ma tak¹ sam¹ wartoœæ
				if (board.board_array[k + 1][j].value == board.board_array[k][j].value) 
				{
					// po³¹cz klocki
					board.board_array[k + 1][j].value *= 2;
					board.board_array[k][j].value = 0;

					// dodaj po³¹czenie do wyniku
					points.counter += board.board_array[k + 1][j].value;

					// ustaw znacznik po³¹czenia na bie¿¹cy element, aby nie móg³ byæ ponownie po³¹czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po³¹czenia
		stacked = -1;
	}
}

void merge_left() 
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (i = 0; i < board.y_size; i++) 
	{
		// ³¹czenie klocków od pocz¹tku wiersza
		for (j = 0; j < board.x_size - 1; j++) 
		{
			// je¿eli klocek nie jest równy zero i nie zosta³ ju¿ wczeœniej po³¹czony
			if (board.board_array[i][j].value != 0 && j != stacked) 
			{
				int k = j;	// przeszukiwanie wiersza do przodu od aktualnego elementu
				// dopóki wiersz siê nie skoñczy³, a nastêpny klocek jest równy 0
				while (k < 2 && board.board_array[i][k + 1].value == 0) 
				{
					// zamiana klocków miejscami
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
					k++;
				}
				// je¿eli napotkany element ma tak¹ sam¹ wartoœæ
				if (board.board_array[i][k + 1].value == board.board_array[i][k].value) 
				{
					// po³¹cz klocki
					board.board_array[i][k + 1].value *= 2;
					board.board_array[i][k].value = 0;

					// dodaj po³¹czenie do wyniku
					points.counter += board.board_array[i][k + 1].value;

					// ustaw znacznik po³¹czenia na bie¿¹cy element, aby nie móg³ byæ ponownie po³¹czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po³¹czenia
		stacked = -1;
	}
}

void merge_right() 
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (i = 0; i < board.y_size; i++) 
	{
		// ³¹czenie klocków od koñca wiersza
		for (j = board.x_size - 2; j >= 0; j--) 
		{
			// je¿eli klocek nie jest równy zero i nie zosta³ ju¿ wczeœniej po³¹czony
			if (board.board_array[i][j].value != 0 && j != stacked) 
			{
				int k = j;	// przeszukiwanie wiersza od ty³u od aktualnego elementu
				// dopóki wiersz siê nie skoñczy³, a nastêpny klocek jest równy 0
				while (k < 2 && board.board_array[i][k + 1].value == 0) 
				{
					// zamiana klocków miejscami
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
					k++;
				}
				// je¿eli napotkany element ma tak¹ sam¹ wartoœæ
				if (board.board_array[i][k + 1].value == board.board_array[i][k].value) 
				{
					// po³¹cz klocki
					board.board_array[i][k + 1].value *= 2;
					board.board_array[i][k].value = 0;

					// dodaj po³¹czenie do wyniku
					points.counter += board.board_array[i][k + 1].value;

					// ustaw znacznik po³¹czenia na bie¿¹cy element, aby nie móg³ byæ ponownie po³¹czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po³¹czenia
		stacked = -1;
	}
}