#pragma once
#include <stdbool.h>

bool did_board_change();
bool did_game_end();
void compare_and_set_best_score();
void save_best_score();
void handle_mouse_clicks();