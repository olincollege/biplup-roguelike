#pragma once

#include <stdbool.h>

/**
 * function: object_constructor
 *
 * Tests to see if player_constructor properly constructs a Player instance,
 * which should have the following values set by arguments:
 *
 * object_counter (int)
 * attr (pointer to an OBJ_ATTR)
 * x (float)
 * y (float)
 * default_sprite (Sprite_ID)
 *
 * TODO: test bitmap stuff?
 * @return 1 if the Object was constructed properly; 0 otherwise.
 */
int test_object_constructor();

/**
 * function: obstacle_constructor
 *
 * Tests to see if obstacle_constructor properly constructs an Obstacle
 * instance, which should have the following predetermined values:
 * x = SCREEN_WIDTH + OFFSCREEN_OFFSET;
 * is_active = false;
 *
 * The following values should be set by arguments given within the test:
 * x_velocity (float)
 * frame_spawn_threshold (int)
 *
 * @return 1 if the Obstacle was constructed properly; 0 otherwise.
 */
int test_obstacle_constructor();

/**
 * function: player_constructor
 *
 * Tests to see if player_constructor properly constructs a Player instance,
 * which should have the following predetermined values:
 * y_velocity = 0;
 * y_acceleration = PLAYER_Y_ACCEL;
 *
 *
 * @return 1 if the Player was constructed properly; 0 otherwise.
 */
int test_player_constructor();

/**
 * function: despawn
 *
 * Tests that despawn hides the given Obstacle on the bitmap level.
 *
 * @return 1 if the Obstacle's ATTR0_HIDE is set to true; 0 otherwise.
 */
int test_despawn_hide();

/**
 * function: despawn
 *
 * Tests that despawn deactivates the Obstacle.
 *
 * @return 1 if the Obstacle's is_active field is set to false; 0 otherwise.
 */
int test_despawn_inactive();

/**
 * function: spawn
 *
 * Tests that spawn unhides the given Obstacle on the bitmap level.
 *
 * @return 1 if the Obstacle's ATTR0_HIDE is set to false; 0 otherwise.
 */
int test_spawn_show();

/**
 * function: spawn
 *
 * Tests that spawn activates the Obstacle.
 *
 * @return 1 if the Obstacle's is_active field is set to true; 0 otherwise.
 */
int test_spawn_active();

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for
 * the right field if an Object is offscreen to the right.
 *
 * @return A 1 if the Object is completely offscreen to the right, otherwise a
 * 0.
 */
int test_right_offscreen();
