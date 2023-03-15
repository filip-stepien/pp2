#include <stdbool.h>
#include "game_data.h" // plik nagłówkowy z podstawowymi strukturami gry

/* Pliki nagłówkowe z logiką gry */
#include "example.h";
/**/

extern struct game_window game; // definicja zewnętrznej struktury zawierającej główne zmienne okna gry
extern struct config cfg;       // definicja zewnętrznej struktury z podstawową konfiguracją gry

// funkcja inicjująca zmienne okna gry i źródła eventów
int game_init(struct game_window* game, struct config cfg)
{
    // inicjacja zmiennych struktury okna gry
    game->gameInitialized = al_init();
    game->keyboardInitialized = al_install_keyboard();
    game->display = al_create_display(cfg.width, cfg.height);
    game->queue = al_create_event_queue();
    game->font = al_create_builtin_font();
    game->timer = al_create_timer(1.0 / (double)cfg.fps); // klatka co 1/30 sekundy = 30 klatek na sekundę

    // generacja kodów błędów, jeżeli któraś zmienna nie została zainicjowana poprawnie
    if (!game->gameInitialized) return 100;
    if (!game->keyboardInitialized) return 101;
    if (!game->display) return 102;
    if (!game->queue) return 103;
    if (!game->font) return 104;
    if (!game->timer) return 105;

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

int main()
{
    game_init(&game, cfg);      // inicjalizacja gry

    al_start_timer(game.timer); // start licznika gry
    bool running = true;        // zmienna sterująca działaniem głównej pętli gry
    ALLEGRO_EVENT event;        // zmienna w której znajdzie się przechwycony event

    // główna pętla gry
    while (running)
    {
        al_wait_for_event(game.queue, &event);  // nasłuchuj eventów
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:   // event pojedynczego tyknięcia licznika
            
            /* LOGIKA GRY */
            example_render();   // przykładowy element logiki

            al_flip_display();  // rysowanie
            break;

        case ALLEGRO_EVENT_KEY_UP:          // event "klawisz spuszczony"
        case ALLEGRO_EVENT_DISPLAY_CLOSE:   // event "zamknięcie okna"
            running = false;                // przerwanie pętli
            break;
        }
    }

    game_cleanup(&game);    // czyszczenie po zakończeniu gry

    return 0;
}