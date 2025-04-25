/**
 * system_utils.h
 *
 * Describe functions and constants that manage the state of the game and
 * overall system.
 */

#pragma once
#include "tonc.h"

#define MAX_SPRITES 128 // maximum number of sprites in the game
#define FLOOR_LEVEL 112 // height of the floor on the screen
#define COUNT_SCORE_ON_FRAME                                                   \
  5 // number of frames to pass before iterating score

/**
 * Reset key game variables so the game can restart.
 *
 * Reset key game variables so the game can restart, specifically:
 * score: 0
 * frame_counter: 1
 * game_state: 1
 */
void init_main(void);

/**
 * Reset key game variables so the game can restart.
 *
 * Reset key game variables so the game can restart, specifically:
 * score: 0
 * frame_counter: 1
 * game_state: 1
 */
void reset_game_state(void);

/**
 * Set the game state to POSTGAME.
 *
 * Set the global game state variable to the POSTGAME state.
 */
void end_game(void);
