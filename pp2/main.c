/* Pliki nagłówkowe z logiką gry */
#include "game_structures.h"
#include "game_init.h"
#include "game_renders.h"
#include "board_operations.h"
#include "board_movement.h"
#include "board_utils.h"
/**/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

extern struct game_window game; // definicja zewnętrznej struktury zawierającej główne zmienne okna gry
extern struct config cfg;       // definicja zewnętrznej struktury z podstawową konfiguracją gry

// funkcja inicjująca zmienne okna gry i źródła eventów
int game_init(struct game_window* game, struct config cfg)
{
    // inicjacja zmiennych struktury okna gry
    game->game_initialized = al_init();
    game->keyboard_initialized = al_install_keyboard();
    game->primitive_shapes_addon_initialized = al_init_primitives_addon();
    game->font_addon_initialized = al_init_font_addon();
    game->ttf_addon_initialized = al_init_ttf_addon();
    game->display = al_create_display(cfg.width, cfg.height);
    game->queue = al_create_event_queue();
    game->font = al_load_font("Arial.ttf", cfg.font_size, NULL);
    game->timer = al_create_timer(1.0 / (double)cfg.fps); // klatka co 1/30 sekundy = 30 klatek na sekundę

    // generacja kodów błędów, jeżeli któraś zmienna nie została zainicjowana poprawnie
    if (!game->game_initialized) return 100;
    if (!game->keyboard_initialized) return 101;
    if (!game->primitive_shapes_addon_initialized) return 102;
    if (!game->font_addon_initialized) return 103;
    if (!game->display) return 104;
    if (!game->queue) return 105;
    if (!game->font) return 106;
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
    }
}

int main()
{
    int code = game_init(&game, cfg); // generacja kodu uruchomienia gry

    // jeżeli wystąpi błąd, zamknij grę i wygeneruj wiadomość z błędem
    bool err = check_err_state(code);
    if (err) return -1;

    al_start_timer(game.timer); // start licznika gry

    initialize_board();                                 // inicjalizacja plansy gry
    initialize_nodes(10, 160);                          // inicjalizacja klocków
    initialize_points(10, 10, 430, 140, cfg.font_size); // inicjalizacja licznika punktów

    generate_random_node();     // generowanie losowego klocka
    color_nodes();              // kolorowanie klocków
    draw_board();               // rysowanie planszy z wstawionymi klockami
    draw_points();              // rysowanie licznika
    al_flip_display();          // wyświetlanie narysowanej klatki

    // główna pętla gry
    bool running = true;    // zmienna sterująca działaniem głównej pętli gry
    ALLEGRO_EVENT event;    // zmienna w której znajdzie się przechwycony event    
    while (running)
    {
        al_wait_for_event(game.queue, &event);  // nasłuchuj eventów
        switch (event.type)
        {
            case ALLEGRO_EVENT_KEY_DOWN:        // event "przycisk wciśnięty"
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:        // przycisk - strzałka w górę
                        merge_up();
                        move_up();
                        break;

                    case ALLEGRO_KEY_DOWN:      // przycisk - strzałka w dół
                        merge_down();
                        move_down();
                        break;

                    case ALLEGRO_KEY_LEFT:      // przycisk - strzałka w lewo
                        merge_left();
                        move_left();
                        break;

                    case ALLEGRO_KEY_RIGHT:     // przycisk - strzałka w prawo
                        merge_right();
                        move_right();
                        break;
                    case ALLEGRO_KEY_R:         // przycisk - r
                        reset_board();          // zresetuj planszę
                        break;
                    case ALLEGRO_KEY_ESCAPE:    // przycisk - esc
                        running = false;        // przerwanie pętli
                        break;
                }

                if (event.keyboard.keycode != ALLEGRO_KEY_ESCAPE) {
                    clear();                // czyszczenie poprzedniej klatki
                    generate_random_node(); // generowanie losowego klocka
                    color_nodes();          // kolorowanie klocków
                    draw_board();           // rysowanie planszy
                    draw_points();          // rysowanie licznika punktów
                    al_flip_display();      // wyświetlanie narysowanej klatki
                    if (did_game_end())     // jeżeli gra się zakończyła
                        puts("Koniec! Wciśnij klawisz R aby zrestartowac gre.");   // komunikat o końcu gry
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