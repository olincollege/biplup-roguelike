/**
 * system_utils.h
 *
 * Describe functions and constants that manage the state of the game and
 * overall system.
 */

#pragma once
#include "tonc.h"

#define MAX_SPRITES 128        // maximum number of sprites in the game
#define FLOOR_LEVEL 112        // height of the floor on the screen
#define COUNT_SCORE_ON_FRAME 5 // number of frames to pass before updating score
#define SCORE_MILESTONE 500    // number of frames to pass before bumping speed

/**
 * Initialize memory for sprites and set up several global game variables.
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

/**
 * Retrieve the high score from SRAM and save it to the global high score
 * variable.
 *
 * At the start of the game, retrieve the high score from SRAM, so that
 * the high score can last across device resets.
 *
 * @return The high score, built from unsigned 8 bit integers, as a unsigned 32
 * bit integer.
 */
u32 retrieve_high_score(void);

/**
 * After each game has ended, save the current high score into SRAM.
 *
 * When the player has collided with another sprite, retrieve the high score and
 * save it into SRAM, so that the high score can last across device resets.
 */
void save_high_score(void);