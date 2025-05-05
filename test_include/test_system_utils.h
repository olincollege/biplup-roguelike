#pragma once

/**
 * function: init_main
 *
 * Tests to see if init_main properly initializes all of the global variables it
 * edits.
 *
 * @return A 1 if all of the global variables init_main interacts with are set
 * to what they are supposed to be, otherwise a 0.
 */
int test_init_main(void);

/**
 * function: reset_game_state
 *
 * Tests to see if reset_game_state properly resets all of the global variables
 * it edits.
 *
 * @return A 1 if reset_game_state resets all of the global variables it
 * interacts with, otherwise a 0.
 */
int test_reset_game_state(void);

/**
 * function retrieve_high_score
 *
 * Tests to see if retrieve_high_score returns 0.
 *
 * @return A 1 if retrieve_high_score returns 0, otherwise a 0.
 */
int test_retrieve_high_score(void);
