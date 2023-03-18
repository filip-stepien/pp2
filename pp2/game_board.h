// Plik zawieraj�cy definicj� funkcji do generowania i manipulacji plansz�

#pragma once // zapewnienie �e dany plik nag��wkowy b�dzie za��czony tylko raz

void generate_board();						// funkcja generuj�ca plansz�
void draw_board();							// funkcja rysuj�ca plansz�
void insert_node(int x, int y, int value);	// funkcja wstawiaj�ca element do planszy