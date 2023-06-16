#pragma once

/**
 * @file board_animations.h
 * @brief Animacje gry - deklaracje
 */

//! Prefix ruchu do góry
#define MOVE_NONE 0
//! Prefix ruchu w lewo
#define MOVE_LEFT 1
//! Prefix ruchu w prawo
#define MOVE_RIGHT 2
//! Prefix ruchu w górę
#define MOVE_UP 3
//! Prefix ruchu w dół
#define MOVE_DOWN 4

/**
 * @brief Dodanie klocka do tablicy klocków wymagających wykonania animacji rozszerzenia
 * @param curent_node klocek
 */
void push_to_grow_animation_array(struct node current_node);

/**
 * @brief Wyczyszczenie tablicy klocków wymagających wykonania animacji rozszerzenia
 */
void clear_grow_animation_array();

/**
 * @brief Wykonanie animacji rozszerzenia na klocku
 * @param curent_node klocek
 * @param current_frame klatka gry
 */
void grow_animation(struct node current_node, int current_frame);

/**
 * @brief Wykonanie animacji rozszerzenia na wszystkich wymagających tego klockach
 * @param frame klatka gry
 */
void grow_animate_nodes(int frame);

/**
 * @brief Wyczyszczenie tablicy klocków wymagających wykonania animacji przesunięcia
 */
void clear_slide_animation_array();

/**
 * @brief Wykonanie animacji przesunięcia na klocku (od lewej do prawej)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_left_to_right(struct node from, struct node to, int current_frame);

/**
 * @brief Wykonanie animacji przesunięcia na klocku (od prawej do lewej)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_right_to_left(struct node from, struct node to, int current_frame);

/**
 * @brief Wykonanie animacji przesunięcia na klocku (z dołu na górę)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 */
void slide_animation_down_to_up(struct node from, struct node to, int current_frame);

/**
 * @brief Wykonanie animacji przesunięcia na klocku (z góry na dół)
 * @param from klocek, od którego ma wykonać się przesunięcie
 * @param to klocek docelowy
 * @param current_frame klatka gry
 * 
 */
void slide_animation_up_to_down(struct node from, struct node to, int current_frame);

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu od lewej do prawej)
 */
void get_nodes_to_slide_animate_left_to_right();

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu od prawej do lewej)
 */
void get_nodes_to_slide_animate_right_to_left();

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu z góry na dół)
 */
void get_nodes_to_slide_animate_up_to_down();

/**
 * @brief Uzupełnienie tablicy animacji przesunięcia (dla ruchu z dołu na górę)
 */
void get_nodes_to_slide_animate_down_to_up();

/**
 * @brief Uzupełnienie tablicy animacji rozszerzenia
 * @param frame klatka gry
 */
void slide_animate_nodes(int frame);