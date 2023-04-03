#include "board_movement.h"
#include "game_structures.h"
#include "board_operations.h"

extern struct game_board board;
extern struct game_points points;

// funkcja przesuwaj�ce klocki w d�
void move_down() {
	int i, j, k;
	// operacja wykonywana dla ka�dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj nast�pny klocek a� do ko�ca kolumny
			for (k = 0; k < board.y_size - 1; k++) 
			{
				// je�eli nast�pny klocek w kolumnie jest r�wny 0 i aktualny nie jest r�wny 0
				if (board.board_array[k + 1][j].value == 0 && board.board_array[k][j].value != 0) 
				{
					// zamie� ich warto�ci = zamie� ich miejscami
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
				}
			}
		}
	}
}

// funkcja przesuwaj�ce klocki do g�ry
void move_up() {
	int i, j, k;
	// operacja wykonywana dla ka�dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj poprzedni klocek a� do ko�ca kolumny
			for (k = 1; k < board.y_size; k++) 
			{
				// je�eli poprzedni klocek w kolumnie jest r�wny 0 i aktualny nie jest r�wny 0
				if (board.board_array[k - 1][j].value == 0 && board.board_array[k][j].value != 0) 
				{
					// zamie� ich warto�ci = zamie� ich miejscami
					board.board_array[k - 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
				}
			}
		}
	}
}

// funkcja przesuwaj�ce klocki w prawo
void move_right() {
	int i, j, k;
	// operacja wykonywana dla ka�dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj nast�pny klocek a� do ko�ca wiersza
			for (k = 0; k < board.y_size - 1; k++) 
			{
				// je�eli nast�pny klocek w wierszu jest r�wny 0 i aktualny nie jest r�wny 0
				if (board.board_array[i][k + 1].value == 0 && board.board_array[i][k].value != 0)
				{
					// zamie� ich warto�ci = zamie� ich miejscami
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
				}
			}
		}
	}
}

// funkcja przesuwaj�ce klocki w lewo
void move_left() {
	int i, j, k;
	// operacja wykonywana dla ka�dego klocka w macierzy
	for (i = 0; i < board.y_size; i++) 
	{
		for (j = 0; j < board.x_size; j++) 
		{
			// przeszukuj poprzedni klocek a� do ko�ca wiersza
			for (k = 1; k < board.y_size; k++) 
			{
				// je�eli poprzedni klocek w wierszu jest r�wny 0 i aktualny nie jest r�wny 0
				if (board.board_array[i][k - 1].value == 0 && board.board_array[i][k].value != 0) 
				{
					// zamie� ich warto�ci = zamie� ich miejscami
					board.board_array[i][k - 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
				}
			}
		}
	}
}

// funkcja ��cz�ca klocki w d�
void merge_down() 
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (j = 0; j < board.x_size; j++) 
	{
		// ��czenie klock�w od do�u kolumny
		for (i = board.y_size - 2; i >= 0; i--) 
		{
			// je�eli klocek nie jest r�wny zero i nie zosta� ju� wcze�niej po��czony
			if (board.board_array[i][j].value != 0 && i != stacked) 
			{
				int k = i;	// przeszukiwanie w do� kolumny od aktualnego elementu
				// dop�ki kolumna si� nie sko�czy�a, a nast�pny klocek jest r�wny 0
				while (k < 2 && board.board_array[k + 1][j].value == 0) 
				{
					// zamiana klock�w miejscami
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
					k++;
				}
				// je�eli napotkany element ma tak� sam� warto��
				if (board.board_array[k + 1][j].value == board.board_array[k][j].value) 
				{
					// po��cz klocki
					board.board_array[k + 1][j].value *= 2;
					board.board_array[k][j].value = 0;

					// dodaj po��czenie do wyniku
					points.counter += board.board_array[k + 1][j].value;

					// ustaw znacznik po��czenia na bie��cy element, aby nie m�g� by� ponownie po��czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po��czenia
		stacked = -1;
	}
}

void merge_up()
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (j = 0; j < board.x_size; j++) 
	{
		// ��czenie klock�w od g�ry kolumny
		for (i = 0; i < board.y_size - 1; i++)
		{
			// je�eli klocek nie jest r�wny zero i nie zosta� ju� wcze�niej po��czony
			if (board.board_array[i][j].value != 0 && i != stacked) 
			{
				int k = i;	// przeszukiwanie w g�r� kolumny od aktualnego elementu
				// dop�ki kolumna si� nie sko�czy�a, a nast�pny klocek jest r�wny 0
				while (k < 2 && board.board_array[k + 1][j].value == 0) 
				{
					// zamiana klock�w miejscami
					board.board_array[k + 1][j].value = board.board_array[k][j].value;
					board.board_array[k][j].value = 0;
					k++;
				}
				// je�eli napotkany element ma tak� sam� warto��
				if (board.board_array[k + 1][j].value == board.board_array[k][j].value) 
				{
					// po��cz klocki
					board.board_array[k + 1][j].value *= 2;
					board.board_array[k][j].value = 0;

					// dodaj po��czenie do wyniku
					points.counter += board.board_array[k + 1][j].value;

					// ustaw znacznik po��czenia na bie��cy element, aby nie m�g� by� ponownie po��czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po��czenia
		stacked = -1;
	}
}

void merge_left() 
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (i = 0; i < board.y_size; i++) 
	{
		// ��czenie klock�w od pocz�tku wiersza
		for (j = 0; j < board.x_size - 1; j++) 
		{
			// je�eli klocek nie jest r�wny zero i nie zosta� ju� wcze�niej po��czony
			if (board.board_array[i][j].value != 0 && j != stacked) 
			{
				int k = j;	// przeszukiwanie wiersza do przodu od aktualnego elementu
				// dop�ki wiersz si� nie sko�czy�, a nast�pny klocek jest r�wny 0
				while (k < 2 && board.board_array[i][k + 1].value == 0) 
				{
					// zamiana klock�w miejscami
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
					k++;
				}
				// je�eli napotkany element ma tak� sam� warto��
				if (board.board_array[i][k + 1].value == board.board_array[i][k].value) 
				{
					// po��cz klocki
					board.board_array[i][k + 1].value *= 2;
					board.board_array[i][k].value = 0;

					// dodaj po��czenie do wyniku
					points.counter += board.board_array[i][k + 1].value;

					// ustaw znacznik po��czenia na bie��cy element, aby nie m�g� by� ponownie po��czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po��czenia
		stacked = -1;
	}
}

void merge_right() 
{
	int i, j, stacked = -1;
	save_board();	// zapisanie stanu planszy
	for (i = 0; i < board.y_size; i++) 
	{
		// ��czenie klock�w od ko�ca wiersza
		for (j = board.x_size - 2; j >= 0; j--) 
		{
			// je�eli klocek nie jest r�wny zero i nie zosta� ju� wcze�niej po��czony
			if (board.board_array[i][j].value != 0 && j != stacked) 
			{
				int k = j;	// przeszukiwanie wiersza od ty�u od aktualnego elementu
				// dop�ki wiersz si� nie sko�czy�, a nast�pny klocek jest r�wny 0
				while (k < 2 && board.board_array[i][k + 1].value == 0) 
				{
					// zamiana klock�w miejscami
					board.board_array[i][k + 1].value = board.board_array[i][k].value;
					board.board_array[i][k].value = 0;
					k++;
				}
				// je�eli napotkany element ma tak� sam� warto��
				if (board.board_array[i][k + 1].value == board.board_array[i][k].value) 
				{
					// po��cz klocki
					board.board_array[i][k + 1].value *= 2;
					board.board_array[i][k].value = 0;

					// dodaj po��czenie do wyniku
					points.counter += board.board_array[i][k + 1].value;

					// ustaw znacznik po��czenia na bie��cy element, aby nie m�g� by� ponownie po��czony w tej turze
					stacked = k + 1;
				}
			}
		}
		// reset znacznika po��czenia
		stacked = -1;
	}
}