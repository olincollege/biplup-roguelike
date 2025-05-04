#pragma once

#include <stdbool.h>
#include "tonc.h"

/**
 * Sets test_input to the inputed key.
 *
 * @param input unsigned 32-bit integer representing simulated key press
 */
void set_test_input(u32 input);

/**
 * Function: pregame_key_input
 *
 * Test to see that if the up button is pressed in the PREGAME state, the game
 * is reset to a score of 0.
 *
 * @return A 1 if the score is reset to 0, otherwise a 0.
 */
int test_pregame_reset_score();

/**
 * Function: pregame_key_input
 *
 * Test to see that if the up button is pressed in the PREGAME state, the game
 * is reset to a frame count of 1.
 *
 * @return A 1 if the frame count is reset to 1, otherwise a 0.
 */
int test_pregame_reset_frame();

/**
 * Function: pregame_key_input
 *
 * Test to see that if the up button is pressed in the PREGAME state, the game
 * state is set to GAME.
 *
 * @return A 1 if the game state is equal to GAME, otherwise a 0.
 */
int test_pregame_to_game();

/**
 * Function: game_key_input
 *
 * Test to see that if the up button is pressed in the GAME state, the player is
 * set to a jumping state.
 *
 * @return A 1 if the players jumping state is true, otherwise a 0.
 */
int test_jump_state();

/**
 * Function: postgame_key_input
 *
 * Test to see that if the up button is pressed in the POSTGAME state, the game
 * is reset to a score of 0.
 *
 * @return A 1 if the score is reset to 0, otherwise a 0.
 */
int test_postgame_reset_score();

/**
 * Function: postgame_key_input
 *
 * Test to see that if the up button is pressed in the POSTGAME state, the game
 * is reset to a frame count of 1.
 *
 * @return A 1 if the frame count is reset to 1, otherwise a 0.
 */
int test_postgame_reset_frame();

/**
 * Function: postgame_key_input
 *
 * Test to see that if the up button is pressed in the POSTGAME state, the game
 * state is set to GAME.
 *
 * @return A 1 if the game state is equal to GAME, otherwise a 0.
 */
int test_postgame_to_game();

/**
 * Function: postgame_key_input
 *
 * Test to see that if the up button is pressed in the POSTGAME state, all
 * obstacles are hidden and offscreen.
 *
 * @return A 1 if the obstacle is hidden and offscreen, otherwise a 0.
 */
int test_postgame_obst_reset();

/**
 * Function: cheat_key_input
 *
 * Test to see that if the right button is pressed in the GAME state, the cheat
 * sprite state will be toggled on and equal 1.
 *
 * @return A 1 if the cheat sprite state equals 1, otherwise a 0.
 */
int test_cheat_mode_toggle();
