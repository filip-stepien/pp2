#pragma once

/**
 * @file game_renders.h
 * @brief Rysowanie elementów gry - deklaracje
 */

/**
 * @brief Rysowanie planszy
 */
void draw_board();

/**
 * @brief Rysowanie wyniku
 */
void draw_points();

/**
 * @brief Rysowanie najlepszego wyniku
 */
void draw_best_points();

/**
 * @brief Rysowanie przycisku menu
 */
void draw_menu_button();

/**
 * @brief Rysowanie przycisku restart
 */
void draw_restart_button();

/**
 * @brief Rysowanie okna menu
 */
void draw_menu_popup();

/**
 * @brief Rysowanie okna końca gry
 */
void draw_end_popup();

/**
 * @brief Rysowanie przycisku od wyciszenia dźwięków
 */
void draw_mute_button();

/**
 * @brief Wyczyszczenie ekranu gry
 */
void clear();