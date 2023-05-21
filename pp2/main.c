/* Pliki nagłówkowe z logiką gry */
#include "game_structures.h"
#include "game_init.h"
#include "game_renders.h"
#include "board_operations.h"
#include "board_movement.h"
#include "board_utils.h"
#include "game_includes.h"
#include "board_animations.h"
#include "game_music.h"
/**/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// funkcja inicjująca zmienne okna gry i źródła eventów
int game_init(struct game_window* game, struct config cfg)
{
    // inicjacja zmiennych struktury okna gry
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

    // generacja kodów błędów, jeżeli któraś zmienna nie została zainicjowana poprawnie
    if (!game->game_initialized) return 100;
    if (!game->keyboard_initialized) return 101;
    if (!game->primitive_shapes_addon_initialized) return 102;
    if (!game->font_addon_initialized) return 103;
    if (!game->display) return 104;
    if (!game->queue) return 105;
    if (!game->font || !game->points_font || !game->title_font || !game->option_font) return 106;
    if (!game->timer) return 107;

    // rejestrowanie źródeł eventów
    al_register_event_source(game->queue, al_get_keyboard_event_source());              // eventy klawiatury
    al_register_event_source(game->queue, al_get_display_event_source(game->display));  // eventy okna
    al_register_event_source(game->queue, al_get_timer_event_source(game->timer));      // eventy licznika

    return 0;   // gra poprawnie zainicjowana
}

// funkcja sprzątająca zainicjalizowane elementy gry
void game_cleanup(struct game_window* game)
{
    if (best_points.counter == points.counter && points.counter > 0)
    {
        FILE* save_file = NULL;
        fopen_s(&save_file, "score.txt", "w");
        if (save_file != NULL)
        {
            fprintf_s(save_file, "%d", best_points.counter);
            fclose(save_file);
        }
    }

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

    al_destroy_font(game->font);            // usuwanie czcionki
    al_destroy_display(game->display);      // usuwanie okna
    al_destroy_timer(game->timer);          // usuwanie licznika
    al_destroy_event_queue(game->queue);    // usuwanie kolejki
    game = NULL;                            // wyzerowanie struktury ze zmiennymi gry
}

// funkcja wypisująca błąd przy uruchomieniu gry
// przyjmuje kod uruchomienia jako argument
bool check_err_state(code)
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

int main()
{
    int code = game_init(&game, cfg); // generacja kodu uruchomienia gry

    // jeżeli wystąpi błąd, zamknij grę i wygeneruj wiadomość z błędem
    bool err = check_err_state(code);
    if (err) return -1;

    al_start_timer(game.timer); // start licznika gry

    int option_center_x = (cfg.width - cfg.option_width) / 2;
    int option_start_y = 300;
    int mute_button_left_x = cfg.width - cfg.mute_button_width;
    int end_option_start_y = 430;

    initialize_sounds();
    play_music();

    initialize_menu_option_buttons(option_center_x, option_start_y);
    initialize_menu_popup();

    initialize_end_button(option_center_x, end_option_start_y);
    initialize_end_popup();

    initialize_mute_button(mute_button_left_x, 0);
    
    // główna pętla gry
    bool running = true;    // zmienna sterująca działaniem głównej pętli gry
    ALLEGRO_EVENT event;    // zmienna w której znajdzie się przechwycony event 

    while (running)
    {
        al_wait_for_event(game.queue, &event);  // nasłuchuj eventów
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

            case ALLEGRO_EVENT_KEY_DOWN:        // event "przycisk wciśnięty"
                if (animations.on_cooldown || !game.started || game.current_popup != NULL) break;

                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:        // przycisk - strzałka w górę
                        animations.last_move = UP;

                        merge_up();
                        move_up();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_down_to_up();
                        break;

                    case ALLEGRO_KEY_DOWN:      // przycisk - strzałka w dół
                        animations.last_move = DOWN;

                        merge_down();
                        move_down();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_up_to_down();
                        break;

                    case ALLEGRO_KEY_LEFT:      // przycisk - strzałka w lewo
                        animations.last_move = LEFT;

                        merge_left();
                        move_left();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_right_to_left();
                        break;

                    case ALLEGRO_KEY_RIGHT:     // przycisk - strzałka w prawo
                        animations.last_move = RIGHT;

                        merge_right();
                        move_right();
                        color_nodes();
                        clear_slide_animation_array();
                        clear_grow_animation_array();
                        get_nodes_to_slide_animate_left_to_right();
                        break;

                    case ALLEGRO_KEY_ESCAPE:    // przycisk - esc
                        running = false;        // przerwanie pętli
                        break;
                }

                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT || 
                    event.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                    event.keyboard.keycode == ALLEGRO_KEY_UP ||
                    event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                    generate_random_node(); // generowanie losowego klocka
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

            case ALLEGRO_EVENT_DISPLAY_CLOSE:   // event "zamknięcie okna"
                running = false;                // przerwanie pętli
                break;
        }
    }

    board_cleanup();        // zwolnienie pamięci zaalokowanej dla planszy gry
    game_cleanup(&game);    // czyszczenie po zakończeniu gry

    return 0;
}