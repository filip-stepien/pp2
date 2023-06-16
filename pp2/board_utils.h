/**
 * @file board_utils.h
 * @brief Funkcje pomocnicze - deklaracje
 */

#pragma once
#include <stdbool.h>

/**
 * @brief Sprawdzenie czy na planszy nastąpił ruch
 * @return czy nastąpił ruch
 */
bool did_board_change();

/**
 * @brief Sprawdzenie czy gra się zakończyła
 * @return czy gra się zakończyła
 */
bool did_game_end();

/**
 * @brief Aktualizacja najlepszego wyniku
 */
void compare_and_set_best_score();

/**
 * @brief Zapisanie najlepszego wyniku do pliku
 */
void save_best_score();

/**
 * @brief Obsługa kliknięć
 */
void handle_mouse_clicks();