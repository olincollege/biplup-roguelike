#pragma once

#include <stdbool.h>

/**
 * Test whether reset_obstacle_position sets the obstacle's x position
 * correctly.
 *
 * @return 1 if the test passes, 0 otherwise.
 */
int test_reset_obstacle_position();

/**
 * Test whether set_obstacle_x_velocity correctly sets the x velocity.
 *
 * @return 1 if the test passes, 0 otherwise.
 */
int test_set_obstacle_x_velocity();

/**
 * Test whether set_player_y_velocity correctly sets the y velocity.
 *
 * @return 1 if the test passes, 0 otherwise.
 */
int test_set_player_y_velocity();

/**
 * Test whether set_jump_state correctly sets the player's jumping state.
 *
 * @return 1 if the test passes, 0 otherwise.
 */
int test_set_jump_state();

/**
 * Test whether update_jump_state starts a jump when the player is not already
 * jumping.
 *
 * @return 1 if the test passes, 0 otherwise.
 */
int test_update_jump_state_starts_jump();

/**
 * Test that update_jump_state does not change state when the player is already
 * jumping.
 *
 * @return 1 if the test passes, 0 otherwise.
 */
int test_update_jump_state_while_jumping();

/**
 * Test full player physics update, including falling and landing on the floor.
 *
 * @return 1 if the test passes (player lands and stops jumping), 0 otherwise.
 */
int test_update_player_physics();
