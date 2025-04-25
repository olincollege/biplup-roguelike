/**
 * input.h
 *
 * Describe functions that poll for and react to player key input.
 *
 * Since the functions behave similarly in polling but react differently to
 * input, they are split up by the three game states: PREGAME, GAME, and
 * POSTGAME.
 */

#pragma once

#include "tonc.h"
#include "types.h"

/**
 * Collect key input during the PREGAME state.
 *
 * Collect key input during the PREGAME state. When the up button is
 * pressed,reset the game to a score of 0, a frame count of 1, and the state
 * GAME.
 */
void pregame_key_input();

/**
 * Collect key input during the GAME state.
 *
 * Collect key input during the GAME state. When the up button is pressed, set
 * the player to a jumping state.
 */
void game_key_input(Object *player);

/**
 * Collect key input during the POSTGAME state.
 *
 * Collect key input during the POSTGAME state. When the up button is pressed,
 * reset the game to a score of 0, a frame count of 1, and the state GAME.
 * Also, reset all game obstacles to be hidden and offscreen.
 */
void postgame_key_input(Object **obstacles);
