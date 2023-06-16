/**
 * @file main.c
 * @brief Główny plik gry
 */

#include "game_structures.h"
#include "game_init.h"
#include "game_renders.h"
#include "board_operations.h"
#include "board_movement.h"
#include "board_utils.h"
#include "game_includes.h"
#include "board_animations.h"
#include "game_music.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/**
 * @brief Inicjalizacja gry i zmiennych Allegro, 
 * @param game struktura ze zmiennymi gry
 * @param cfg struktura z konfiguracją gry
 * @return kod błędu gry
 */
int game_init(struct game_window* game, struct config cfg)
{
    game->game_initialized = al_init();
    game->keyboard_initialized = al_install_keyboard();
    game->primitive_shapes_addon_initialized = al_init_primitives_addon();
    game->font_addon_initialized = al_init_font_addon();
    game->ttf_addon_initialized = al_init_ttf_addon();
    game->image_addon_initialized = al_init_image_addon();
    game->mouse_initialized = al_install_mouse();
    game->audio_addon_initialized = al_install_audio();
    game->acodec_addon_initialized = al_init_acodec_addon();
    game->display = al_create_display(cfg.width, cfg.height);
    game->queue = al_create_event_queue();
    game->font = al_load_font(cfg.font_name, cfg.font_size, 0);
    game->points_font = al_load_font(cfg.font_name, cfg.points_font_size, 0);
    game->title_font = al_load_font(cfg.font_name, cfg.title_font_size, 0);
    game->option_font = al_load_font(cfg.font_name, cfg.option_font_size, 0);
    game->timer = al_create_timer(1.0 / (double)cfg.fps); // klatka co 1/30 sekundy = 30 klatek na sekundę
    game->current_popup = NULL;
    game->started = false;
    game->muted = false;

    if (!game->game_initialized) return 100;
    if (!game->keyboard_initialized) return 101;
    if (!game->primitive_shapes_addon_initialized) return 102;
    if (!game->font_addon_initialized) return 103;
    if (!game->display) return 104;
    if (!game->queue) return 105;
    if (!game->font || !game->points_font || !game->title_font || !game->option_font) return 106;
    if (!game->timer) return 107;

    al_register_event_source(game->queue, al_get_keyboard_event_source());              // eventy klawiatury
    al_register_event_source(game->queue, al_get_display_event_source(game->display));  // eventy okna
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));      // eventy licznika

    return 0;
}

/**
 * @brief Sprzątanie zainicjalizowanych elementów gry
 * @param game struktura ze zmiennymi gry
 */
void game_cleanup(struct game_window* game)
{
    save_best_score();

    free(menu.buttons);
    menu.buttons = NULL;
    menu.buttons_length = 0;

    free(end.buttons);
    end.buttons = NULL;
    end.buttons_length = 0;

    free(sounds.click_sounds);
    sounds.click_sounds = NULL;

    free(sounds.grow_sounds);
    sounds.grow_sounds = NULL;

    al_destroy_font(game->font);
    al_destroy_display(game->display);
    al_destroy_timer(game->timer);
    al_destroy_event_queue(game->queue);
    game = NULL;
}

/**
 * @brief Obsługa błędów przy uruchomieniu gry
 * @param code kod uruchomienia gry
 * @return czy wystąpił błąd
 */
bool check_err_state(int code)
{
    switch (code)
    {
        case 0:
            return false;

        case 100:
            puts("Niepoprawna inicjalizacja gry. \nKod bledu 100");
            return true;

        case 101:
            puts("Klawiatura nie zostala zinicjalizowana poprawnie. \nKod bledu 101");
            return true;

        case 102:
            puts("Dodatek prymitywnych ksztaltow nie zostal zainicjalizowany poprawnie. \nKod bledu 102");
            return true;

        case 103:
            puts("Dodatek do czcionki nie zostal zainicjalizowany poprawnie. \nKod bledu 103");
            return true;

        case 104:
            puts("Obraz nie zostal zainicjalizowany poprawnie. \nKod bledu 104");
            return true;

        case 105:
            puts("Kolejka nie zostala zainicjalizowana poprawnie. \nKod bledu 105");
            return true;

        case 106:
            puts("Czcionka nie zostala zainicjalizowana poprawnie. \nKod bledu 106");
            return true;

        case 107:
            puts("Licznik nie zostal zainicjalizowany poprawnie. \nKod bledu 107");
            return true;

        default:
            puts("Wystapil niezidentyfikowany blad.");
            return true;
    }
}

/**
 * @brief Główna funkcja programu
 */
int main()
{
    int code = game_init(&game, cfg);

    bool err = check_err_state(code);
    if (err) return -1;

    al_start_timer(game.timer);

    int option_center_x = (cfg.width - cfg.option_width) / 2;
    int option_start_y = 300;
    int mute_button_right_x = cfg.width - cfg.mute_button_width;
    int mute_button_end_y = cfg.height - cfg.mute_button_height;
    int end_option_start_y = 430;

    initialize_sounds();
    play_music();

    initialize_menu_option_buttons(option_center_x, option_start_y);
    initialize_menu_popup();

    initialize_end_button(option_center_x, end_option_start_y);
    initialize_end_popup();

    initialize_mute_button(mute_button_right_x, mute_button_end_y);
    
    bool running = true;
    ALLEGRO_EVENT event;

    while (running)
    {
        al_wait_for_event(game.queue, &event);
        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                clear();

                if (game.started)
                {
                    draw_board();
                    draw_points();
                    draw_best_points();
                    draw_restart_button();
                    draw_menu_button();
                    slide_animate_nodes(animations.frame);
                    grow_animate_nodes(animations.frame);
                }

                if (menu.visible) draw_menu_popup();

                if (end.visible) draw_end_popup();

                draw_mute_button();

                handle_mouse_clicks(animations.click_frame);

                al_flip_display();

                if (animations.frame == cfg.grow_animation_duration) clear_grow_animation_array();

                if (animations.frame == cfg.move_cooldown) animations.on_cooldown = false;

                if (animations.click_frame == cfg.click_cooldown) animations.click_cooldown = false;

                animations.frame++;
                animations.click_frame++;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                if (animations.on_cooldown || !game.started || game.current_popup != NULL) break;

                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        animations.last_move = UP;

                        merge_up();
                        move_up();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_down_to_up();
                        break;

                    case ALLEGRO_KEY_DOWN:
                        animations.last_move = DOWN;

                        merge_down();
                        move_down();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_up_to_down();
                        break;

                    case ALLEGRO_KEY_LEFT:
                        animations.last_move = LEFT;

                        merge_left();
                        move_left();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_right_to_left();
                        break;

                    case ALLEGRO_KEY_RIGHT:
                        animations.last_move = RIGHT;

                        merge_right();
                        move_right();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_left_to_right();
                        break;

                    case ALLEGRO_KEY_ESCAPE:
                        running = false;
                        break;
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT || 
                    event.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                    event.keyboard.keycode == ALLEGRO_KEY_UP ||
                    event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    generate_random_node();
                    animations.frame = 0;
                    animations.done_sliding = false;
                    animations.on_cooldown = true;

                    if (did_game_end())
                    {
                        game.current_popup = &end;
                        end.visible = true;
                    }
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
        }
    }

    board_cleanup();
    game_cleanup(&game);

    return 0;
}