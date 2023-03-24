#include <stdio.h>
#include <stdbool.h>
#include "game_data.h" // plik nagłówkowy z podstawowymi strukturami gry

/* Pliki nagłówkowe z logiką gry */
#include "example.h"
#include "game_board.h"
/**/

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
            puts("Niepoprawna inicjalizacja gry. \n Kod bledu 100");
            return true;

        case 101:
            puts("Klawiatura nie zostala zinicjalizowana poprawnie. \n kod bledu 101");
            return true;

        case 102:
            puts("Okno nie zostalo zainicjalizowane poprawnie. \n kod bledu 102");
            return true;

        case 103:
            puts("Kolejka nie zostala zainicjalizowana poprawnie. \n kod bledu 103");
            return true;

        case 104:
            puts("Czcionka nie zostala zainicjalizowana poprawnie. \n kod bledu 104");
            return true;

        case 105:
            puts("Licznik nie zostal zainicjalizowany poprawnie. \n kod bledu 105");
            return true;
    }
}

int main()
{
    int code = game_init(&game, cfg); // generacja kodu uruchomienia gry

    // jeżeli wystąpi błąd, zamknij grę i wygeneruj wiadomość z błędem
    bool err = check_err_state(code);
    if (err) return -1;

    game_init(&game, cfg);      // inicjalizacja gry
    al_start_timer(game.timer); // start licznika gry

    bool running = true;        // zmienna sterująca działaniem głównej pętli gry
    ALLEGRO_EVENT event;        // zmienna w której znajdzie się przechwycony event

    /* PRZYKŁADOWE WYGENEROWANIE PLANSZY */
    initialize_board();           // zainicjalizuj planszę gry
    initialize_nodes(100, 100);   // zainicjuj plansze, która będzie generowana w koordynatach (100,100)

    // wstawianie przykladowych klocków (x, y, wartość_klocka)
    insert_node(2, 2, 2);
    insert_node(2, 3, 4);
    insert_node(3, 3, 2);
    insert_node(0, 3, 4);
    insert_node(2, 1, 2);
    insert_node(0, 0, 8);

    draw_board();                 // rysowanie planszy z wstawionymi klockami
    al_flip_display();            // wyświetlanie narysowanej klatki

    // główna pętla gry
    while (running)
    {
        al_wait_for_event(game.queue, &event);  // nasłuchuj eventów
        switch (event.type)
        {
            case ALLEGRO_EVENT_KEY_DOWN:        // event "przycisk wciśnięty"
                switch (event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:        // przycisk - strzałka w górę
                        stack_up();
                        move_up();
                        break;

                    case ALLEGRO_KEY_DOWN:      // przycisk - strzałka w dół
                        stack_down();
                        move_down();
                        break;

                    case ALLEGRO_KEY_LEFT:      // przycisk - strzałka w lewo
                        stack_left();
                        move_left();
                        break;

                    case ALLEGRO_KEY_RIGHT:     // przycisk - strzałka w prawo
                        stack_right();
                        move_right();
                        break;
                    case ALLEGRO_KEY_ESCAPE:    // przycisk - esc
                        running = false;        // przerwanie pętli
                        break;
                }

                // debug_print_board(); <-- funkcja do debugowania
                draw_board();      // rysowanie planszy
                al_flip_display(); // wyświetlanie narysowanej klatki
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