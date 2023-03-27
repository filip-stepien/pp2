// Plik zawieraj¹cy definicjê funkcji do generowania i manipulacji plansz¹
#include <stdbool.h>

#pragma once // zapewnienie ¿e dany plik nag³ówkowy bêdzie za³¹czony tylko raz

void initialize_board();			// funkcja inicjuj¹ca planszê gry
void initialize_nodes(int, int);	// funkcja inicjuj¹ca klocki
void board_cleanup();				// funkcja zwalniaj¹ca pamiêæ zaalokowan¹ dla planszy gry
void draw_board();					// funkcja rysuj¹ca planszê
void insert_node(int, int, int);	// funkcja wstawiaj¹ca element do planszy
// TODO: OPISAÆ FUNKCJE PONI¯EJ
void debug_print_board();
void reset_board();
bool did_game_end();
void move_down();
void move_up();
void move_right();
void move_left();
void stack_down();
void stack_up();
void stack_right();
void stack_left();
void generate_random_node();
void color_nodes();