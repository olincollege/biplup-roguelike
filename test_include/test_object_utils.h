#pragma once

#include <stdbool.h>

#define NUM_OBJECT_UTILS_TESTS 27

// Constant used for determining the difference between floats.
#define EPSILON 0.001

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for
 * the right field if an Object is offscreen to the right.
 *
 * @return A 1 if the Object is completely offscreen to the right, otherwise a
 * 0.
 */
int test_right_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 0 if the Object is partially
 * offscreen.
 *
 * @return A 1 if the Object is partially offscreen, otherwise a 0.
 */
int test_partly_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the left field if an
 * Object is offscreen to the left.
 *
 * @return A 1 if the Object is completely offscreen to the left, otherwise a 0.
 */
int test_left_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the top field if an
 * Object is offscreen at the top.
 *
 * @return A 1 if the Object is completely offscreen at the top, otherwise a 0.
 */
int test_top_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the bottom field if an
 * Object is offscreen at the bottom.
 *
 * @return A 1 if the Object is completely offscreen at the bottom. otherwise a
 * 0.
 */
int test_bottom_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the top field and the
 * left field if an Object is offscreen in the top-left corner.
 *
 * @return A 1 if the Object is completely offscreen at the top-left corner,
 * otherwise a 0.
 */
int test_corner_top_left_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the top field and the
 * right field if an Object is offscreen in the top-right corner.
 *
 * @return A 1 if the Object is completely offscreen at the top-right corner,
 * otherwise a 0.
 */
int test_corner_top_right_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the bottom field and the
 * left field if an Object is offscreen in the bottom-left corner.
 *
 * @return A 1 if the Object is completely offscreen at the bottom-left corner,
 * otherwise a 0.
 */
int test_corner_bottom_left_offscreen(void);

/**
 * function: check_obj_offscreen
 *
 * Tests to see if check_obj_offscreen returns a 1 for the bottom field and the
 * right field if an Object is offscreen in the bottom-right corner.
 *
 * @return A 1 if the Object is completely offscreen at the bottom-right corner,
 * otherwise a 0.
 */
int test_corner_bottom_right_offscreen(void);

/**
 * function: update_obstacles
 *
 * Tests to see if Obstacles in an array are updated based on their current
 * velocity.
 *
 * @return A 1 if all of the Obstacles in an array are updated by their velocity
 * amount, otherwise a 0.
 */
int test_update_moving_obstacles(void);

/**
 * function: update_obstacles
 *
 * Tests to see if Obstacles in an array are all spawned when their frame spawn
 * threshold is hit, and they are currently not spawned.
 *
 * @return A 1 if all of the Obstacles are spawned and their position is at the
 * edge of the screen, otherwise a 0.
 */
int test_update_still_obstacles(void);

/**
 * function: update_obstacle_velocities
 *
 * Tests to see if the velocities are updated by the correct multiplier based on
 * the score 500.
 *
 * @return A 1 if all of the Obstacle's velocities are updated based on the
 * score 500, otherwise a 0.
 */
int test_velocity_milestone_1(void);

/**
 * function: update_obstacle_velocities
 *
 * Tests to see if the velocities are updated by the correct multiplier based on
 * the score 1000.
 *
 * @return A 1 if all of the Obstacle's velocities are updated based on the
 * score 1000, otherwise a 0.
 */
int test_velocity_milestone_2(void);

/**
 * function: update_obstacle_velocities
 *
 * Tests to see if the velocities are updated by the correct multiplier based on
 * the score 1500.
 *
 * @return A 1 if all of the Obstacle's velocities are updated based on the
 * score 1500, otherwise a 0.
 */
int test_velocity_milestone_3(void);

/**
 * function: update_obstacle_velocities
 *
 * Tests to see if the velocities are updated by the correct multiplier based on
 * the score 2000.
 *
 * @return A 1 if all of the Obstacle's velocities are updated based on the
 * score 2000, otherwise a 0.
 */
int test_velocity_milestone_4(void);

/**
 * function: restart_obstacles
 *
 * Tests to see if all of the Obstacles are despawned and set to the edge of the
 * screen.
 *
 * @return A 1 if all of the Obstacles are despawned and set to the edge of the
 * screen, otherwise a 0.
 */
int test_restart_obstacles(void);

/**
 * function: check_player_collision
 *
 * Tests to see if the first Obstacle in an array of Obstacles has collided with
 * the player.
 *
 * @return A 1 if an Obstacle has collided with the player, otherwise a 0.
 */
int test_collisions(void);

/**
 * function: check_player_collision
 *
 * Tests to see if no Obstacles have collided with
 *
 * @return A 1 if no Obstacle has collided with the player, otherwise a 0.
 */
int test_no_collisions(void);

/**
 * function: cheat_toggle_pokemon
 *
 * Tests to see if global variables have properly been set after toggling all of
 * the Obstacles in an array in or out of pokemon mode.
 *
 * @return A 1 if all of the global variables have properly been set, otherwise
 * a 0.
 */
int test_cheat_toggle_pokemon(void);

/**
 * Tests to see if toggling cheat mode off sets all sprites to the default
 * sprite.
 *
 * In this test, both the player and obstacle have their default sprite set to
 * DINO. Therefore, their sprite id's should remain as DINO.
 *
 * @return 1 if both the player and obstacle sprite IDs are the default, 0
 * otherwise.
 */
int test_toggle_cheat_state_off();

/**
 * Tests to see if toggling cheat mode on sets all sprites to the cheat mode
 * sprite.
 *
 * In this test, both the player and obstacle have their default sprite set to
 * DINO. Therefore, their sprite id's should become BIPLUP.
 *
 * @return 1 if both the player and obstacle sprite IDs are the the cheat mode
 * sprite, 0 otherwise.
 */
int test_toggle_cheat_state_on();

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

#define OBJECT_UTILS_TESTS                                                     \
  test_right_offscreen(), test_partly_offscreen(), test_left_offscreen(),      \
      test_top_offscreen(), test_bottom_offscreen(),                           \
      test_corner_bottom_left_offscreen(), test_corner_top_left_offscreen(),   \
      test_corner_top_right_offscreen(), test_corner_bottom_right_offscreen(), \
      test_update_moving_obstacles(), test_update_still_obstacles(),           \
      test_velocity_milestone_1(), test_velocity_milestone_2(),                \
      test_velocity_milestone_3(), test_velocity_milestone_4(),                \
      test_restart_obstacles(), test_collisions(), test_no_collisions(),       \
      test_cheat_toggle_pokemon(), test_object_constructor(),                  \
      test_obstacle_constructor(), test_player_constructor(),                  \
      test_despawn_inactive(), test_spawn_show(), test_spawn_active(),         \
      test_toggle_cheat_state_on(), test_toggle_cheat_state_off()
