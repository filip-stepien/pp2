#pragma once

void push_to_animation_array(struct node current_node);
void clear_animation_array();
void grow_animation(struct node current_node, int current_frame);
void get_nodes_to_grow_animate();
void grow_animate_nodes(int frame);
void slide_animation_left_to_right(struct node from, struct node to, int current_frame);
void slide_animation_right_to_left(struct node from, struct node to, int current_frame);
void slide_animation_down_to_up(struct node from, struct node to, int current_frame);
void slide_animation_up_to_down(struct node from, struct node to, int current_frame);
void get_nodes_to_slide_animate_left_to_right(struct node* arr);
void get_nodes_to_slide_animate_right_to_left(struct node* arr);
void get_nodes_to_slide_animate_up_to_down(struct node* arr);
void get_nodes_to_slide_animate_down_to_up(struct node* arr);