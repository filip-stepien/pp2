#pragma once

#define MOVE_NONE 0
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_UP 3
#define MOVE_DOWN 4

void push_to_grow_animation_array(struct node current_node);
void clear_grow_animation_array();
void grow_animation(struct node current_node, int current_frame);
void grow_animate_nodes(int frame);
void clear_slide_animation_array();
void slide_animation_left_to_right(struct node from, struct node to, int current_frame);
void slide_animation_right_to_left(struct node from, struct node to, int current_frame);
void slide_animation_down_to_up(struct node from, struct node to, int current_frame);
void slide_animation_up_to_down(struct node from, struct node to, int current_frame);
void get_nodes_to_slide_animate_left_to_right();
void get_nodes_to_slide_animate_right_to_left();
void get_nodes_to_slide_animate_up_to_down();
void get_nodes_to_slide_animate_down_to_up();
void slide_animate_nodes(int frame);