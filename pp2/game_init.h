#pragma once

void initialize_board();
void initialize_nodes(int render_x, int render_y);
void board_cleanup();
void initialize_points(int render_x, int render_y, int new_width);
void initialize_best_points(int render_x, int render_y, int new_width);
void initialize_restart_button(int render_x, int render_y, char* img_name);
void initialize_menu_button(int render_x, int render_y, char* img_name);
void initialize_menu_option_buttons(int render_x, int render_y);
void initialize_menu_popup();
void start_new_game();
void initialize_mute_button(int render_x, int render_y);