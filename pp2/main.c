#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "game_data.h" // plik nagłówkowy z podstawowymi strukturami gry

/* Pliki nagłówkowe z logiką gry */
#include "example.h"
#include "game_board.h"
/**/

extern struct game_window game; // definicja zewnętrznej struktury zawierającej główne zmienne okna gry
extern struct config cfg;       // definicja zewnętrznej struktury z podstawową konfiguracją gry

int random = 0;

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
    srand(time(NULL));


    int code = game_init(&game, cfg);

    bool err = check_err_state(code);
    if (err) return -1;
    
    

    game_init(&game, cfg);      // inicjalizacja gry
    al_start_timer(game.timer); // start licznika gry

    bool running = true;        // zmienna sterująca działaniem głównej pętli gry
    ALLEGRO_EVENT event;        // zmienna w której znajdzie się przechwycony event

    /* PRZYKŁADOWE WYGENEROWANIE PLANSZY */
    generate_board(100, 100);   // wygeneruj plansze w koordynatach (100,100)
    draw_board();               // rysuj plansze
    random = rand() % 4;        
    printf("%d", random);      //pokazuje w konsoli jaka została wylosowana liczba i jaka powina się znajdować w grze
   

    // główna pętla gry
    while (running)
    {

        al_wait_for_event(game.queue, &event);  // nasłuchuj eventów
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:   // event pojedynczego tyknięcia licznika
            
            /* LOGIKA GRY */
            //example_render();   // przykładowy element logiki
            insert_node(random,random, 2);       // wstaw klocek który w tablicy 2D ma koordynaty random,2 z wartością 2
            draw_board();               // narysuj planszę z wstawionym klockiem
            al_flip_display(); // rysowanie
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