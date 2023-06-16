#pragma once

/**
 * @file game_init.h
 * @brief Inicjalizacja elementów gry - deklaracje
 */

/**
 * @brief Inicjalizacja dźwięków
 */
void initialize_sounds();

/**
 * @brief Inicjalizacja planszy gry
 */
void initialize_board();

/**
 * @brief Inicjalizacja klocków
 * @param render_x koordynata x, od której będzie rysowana plansza
 * @param render_y koordynata y, od której będzie rysowana plansza
 */
void initialize_nodes(int render_x, int render_y);

/**
 * @brief Czyszczenie po planszy gry
 */
void board_cleanup();

/**
 * @brief Inicjalizacja licznika wyniku
 * @param render_x koordynata x, od której będzie rysowany licznik wyniku
 * @param render_y koordynata y, od której będzie rysowany licznik wyniku
 * @param new_width szerokość licznika
 */
void initialize_points(int render_x, int render_y, int new_width);

/**
 * @brief Inicjalizacja licznika najlepszego wyniku
 * @param render_x koordynata x, od której będzie rysowany licznik najlepszego wyniku
 * @param render_y koordynata y, od której będzie rysowany licznik najlepszego wyniku
 * @param new_width szerokość licznika
 */
void initialize_best_points(int render_x, int render_y, int new_width);

/**
 * @brief Inicjalizacja przycisku restart
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 * @param img_name nazwa pliku z ikoną
 */
void initialize_restart_button(int render_x, int render_y, char* img_name);

/**
 * @brief Inicjalizacja przycisku menu
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 * @param img_name nazwa pliku z ikoną
 */
void initialize_menu_button(int render_x, int render_y, char* img_name);

/**
 * @brief Inicjalizacja przycisków w menu
 * @param render_x koordynata x, od której będą rysowane przyciski
 * @param render_y koordynata y, od której będą rysowane przyciski
 */
void initialize_menu_option_buttons(int render_x, int render_y);

/**
 * @brief Inicjalizacja okna menu
 */
void initialize_menu_popup();

/**
 * @brief Inicjalizacja przycisku restartu w oknie końca gry
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 */
void initialize_end_button(int render_x, int render_y);

/**
 * @brief Inicjalizacja okna końca gry
 */
void initialize_end_popup();

/**
 * @brief Rozpoczęcie nowej gry
 */
void start_new_game();

/**
 * @brief Inicjalizacja przycisku od dźwięku
 * @param render_x koordynata x, od której będzie rysowany przycisk
 * @param render_y koordynata y, od której będzie rysowany przycisk
 */
void initialize_mute_button(int render_x, int render_y);