#pragma once

/**
 * @file board_operations.h
 * @brief Operacje na planszy gry - deklaracje
 */

/**
 * @brief Generowanie losowego klocka
 */
void generate_random_node();

/**
 * @brief Wstawianie klocka w określone miejsce
 * @param x koordynata x
 * @param y koordynata y
 * @param value wartość klocka
 */
void insert_node(int x, int y, int value);

/**
 * @brief Kolorowanie klocków
 */
void color_nodes();

/**
 * @brief Zapisanie stanu planszy
 */
void save_board();

/**
 * @brief Zresetowanie planszy
 */
void reset_board();