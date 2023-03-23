// Plik zawieraj¹cy definicjê funkcji do generowania i manipulacji plansz¹

#pragma once // zapewnienie ¿e dany plik nag³ówkowy bêdzie za³¹czony tylko raz

void initialize_board();			// funkcja inicjuj¹ca planszê gry
void initialize_nodes(int, int);	// funkcja inicjuj¹ca klocki
void board_cleanup();				// funkcja zwalniaj¹ca pamiêæ zaalokowan¹ dla planszy gry
void draw_board();					// funkcja rysuj¹ca planszê
void insert_node(int, int, int);	// funkcja wstawiaj¹ca element do planszy