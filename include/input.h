/**
 * input.h
 *
 * Describe functions that poll for and react to player key input.
 *
 * Since the functions behave similarly in polling but react differently to
 * input, they are split up by the three game states: PREGAME, GAME, and
 * POSTGAME. There is also an additional function for toggling on the secret
 * pokemon sprite mode.
 */

#pragma once

#include "tonc.h"
#include "types.h"

/**
 * Collect key input.
 *
 * Polls the device for a key input. If it detects a key input, the input will
 * be returned. If it doesn't detect any input, such as in the situation of
 * running test cases, it will return a preset test input.
 *
 * @param key an unsigned 32-bit integer representing what keys are pressed.
 * @return a key input either preset for tests or collected from user input on
 * the GBA.
 */
u32 get_input(u32 key);

/**
 * Wait for key input during the PREGAME state.
 *
 * Wait for correct key input during the PREGAME state. When the up button is
 * pressed, reset the game to a score of 0, a frame count of 1, and the state
 * GAME.
 */
void pregame_key_input();

/**
 * Wait for key input during the GAME state.
 *
 * Wait for correct key input during the GAME state. When the up button is
 * pressed, set the player to a jumping state.
 *
 * @param player A Player struct, which is passed to the update_jump_state
 * function.
 */
void game_key_input(Player *player);

/**
 * Wait for key input during the POSTGAME state.
 *
 * Wait for correct key input during the POSTGAME state. When the up button is
 * pressed, reset the game to a score of 0, a frame count of 1, and the state
 * GAME. Also, reset all game obstacles to be hidden and offscreen.
 *
 * @param obstacles A pointer to a list of references to Obstacle structs, which
 * will be reset.
 */
void postgame_key_input(Obstacle **obstacles);

/**
 * Wait for cheat key input during the GAME state.
 *
 * Wait for correct key input during the GAME state. When the right button is
 * pressed, display the pokemon sprites in place of the original dinosaur themed
 * sprites.
 *
 * @param player A Player struct, which is passed to the cheat_toggle_pokemon
 * function.
 * @param obstacles A pointer to a list of references to Obstacle structs, which
 * is passed to the cheat_toggle_pokemon function.
 */
void cheat_key_input(Player *player, Obstacle **obstacles);
