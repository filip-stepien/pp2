/**
 * @file game_music.c
 * @brief Muzyka gry
 */

#include "game_music.h"
#include "game_includes.h"
#include "game_structures.h"

/**
 * @brief Odtworzenie dźwięku kliknięcia
 */
void play_click_sound()
{
	int random = 0;
	while (random == sounds.last_click_sound) random = rand() % cfg.click_sounds_length;
	al_play_sample_instance(sounds.click_sounds[random]);
	sounds.last_click_sound = random;
}

/**
 * @brief Odtworzenie dźwięku pojawienia się nowego klocka
 */
void play_grow_sound()
{
	int random = 0;
	while (random == sounds.last_grow_sound) random = rand() % cfg.grow_sounds_length;
	al_play_sample_instance(sounds.grow_sounds[random]);
	sounds.last_grow_sound = random;
}

/**
 * @brief Odtworzenie muzyki gry
 */
void play_music()
{
	al_play_sample_instance(sounds.music);
}

/**
 * @brief Wyciszenie dźwięków
 */
void mute_game()
{
	al_set_sample_instance_gain(sounds.music, 0.0);
	for (int i = 0; i < cfg.click_sounds_length; i++) al_set_sample_instance_gain(sounds.click_sounds[i], 0.0);
	for (int i = 0; i < cfg.grow_sounds_length; i++) al_set_sample_instance_gain(sounds.grow_sounds[i], 0.0);
}

/**
 * @brief Wyłączenie wyciszenia dźwięków
 */
void unmute_game()
{
	al_set_sample_instance_gain(sounds.music, cfg.music_volume);
	for (int i = 0; i < cfg.click_sounds_length; i++) al_set_sample_instance_gain(sounds.click_sounds[i], cfg.sfx_volume);
	for (int i = 0; i < cfg.grow_sounds_length; i++) al_set_sample_instance_gain(sounds.grow_sounds[i], cfg.sfx_volume);
}