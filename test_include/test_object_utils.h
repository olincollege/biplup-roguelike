#pragma once

#include <stdbool.h>

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
