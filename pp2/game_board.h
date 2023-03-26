// Plik zawieraj�cy definicj� funkcji do generowania i manipulacji plansz�

#pragma once // zapewnienie �e dany plik nag��wkowy b�dzie za��czony tylko raz

void initialize_board();			// funkcja inicjuj�ca plansz� gry
void initialize_nodes(int, int);	// funkcja inicjuj�ca klocki
void board_cleanup();				// funkcja zwalniaj�ca pami�� zaalokowan� dla planszy gry
void draw_board();					// funkcja rysuj�ca plansz�
void insert_node(int, int, int);	// funkcja wstawiaj�ca element do planszy
void debug_print_board();
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