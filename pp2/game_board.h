// Plik zawieraj¹cy definicjê funkcji do generowania i manipulacji plansz¹

#pragma once // zapewnienie ¿e dany plik nag³ówkowy bêdzie za³¹czony tylko raz

void generate_board();						// funkcja generuj¹ca planszê
void draw_board();							// funkcja rysuj¹ca planszê
void insert_node(int x, int y, int value);	// funkcja wstawiaj¹ca element do planszy