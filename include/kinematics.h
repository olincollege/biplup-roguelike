/**
 * kinematics.h
 *
 * Describe functions and constants that maintain the kinematics of game
 * objects, including obstacles and the player.
 *
 * Kinematics refers to position, velocity, and acceleration in the x and y
 * direction. In practice, the player only uses x and y position, y velocity,
 * and y acceleration; while obstacles only use x and y position and x velocity.
 *
 * The constants in the file refer to base values for the kinematic variables of
 * the player and the obstacles.
 */

#pragma once

#include "tonc.h"
#include "types.h"
#include <stdbool.h>

#define OFFSCREEN_OFFSET 10   // offset obstacles from the right of the screen
#define PLAYER_X_POS 40       // x position of the player
#define PLAYER_Y_JUMP_VEL -13 // y velocity of the player while jumping
#define PLAYER_Y_ACCEL 0.5    // y acceleration of the player while jumping
#define PLAYER_Y_ACCEL_MOD 11 // y acceleration modifier for arc motion
#define OBSTACLE_X_VELOCITY 3 // x velocity of obstacles

/**
 * Align the x position of the object struct and its OBJ_ATTR field.
 *
 * Retrieve the true x position of the object and save it in the object's x
 * field, such that the program can interact with the field rather than with the
 * bitmap.
 *
 * @param obj A pointer to an Object struct to align.
 */
void update_obj_x(Object *obj);

/**
 * Align the y position of the object struct and its OBJ_ATTR field.
 *
 * Retrieve the true y position of the object and save it in the object's y
 * field, such that the program can interact with the field rather than with the
 * bitmap.
 *
 * @param obj A pointer to an Object struct to align.
 */
void update_obj_y(Object *obj);

/**
 * Reset an obstacle to its default position off the screen.
 *
 * Given a pointer to an Object struct representing an obstacle, set the
 * obstacle's true x position to SCREEN_WIDTH + OFFSCREEN_OFFSET. Then, align
 * the Object's position fields to its bitmap location.
 *
 * @param obs A pointer to an Object struct that is an obstacle.
 */
void reset_obstacle_position(Obstacle *obs);

/**
 * Set the x velocity of an obstacle.
 *
 * Given a value for x velocity, set the obstacle's x velocity to this value.
 *
 * @param obs A pointer to an Object struct representing an obstacle.
 * @param x_velocity A float representing the x velocity to apply to the
 * obstacle.
 */
void set_obstacle_x_velocity(Obstacle *obs, float x_velocity);

/**
 * Set the y velocity of the player.
 *
 * Given a value for y velocity, set the player's y velocity to this value.
 *
 * @param player A pointer to an Object struct representing the player.
 * @param y_velocity A float representing the y velocity to apply to the player.
 */
void set_player_y_velocity(Player *player, float y_velocity);

/**
 * Set the y acceleration of the player.
 *
 * Given a value for y acceleration, set the player's y acceleration to this
 * value.
 *
 * @param player A pointer to an Object struct representing the player.
 * @param y_acceleration A float representing the y acceleration to apply to the
 * player.
 */
void set_obj_y_acceleration(Player *player, float y_acceleration);

/**
 * Set the jump state of the player.
 *
 * Given a boolean value, set the player's jumping property to this value.
 *
 * @param player A pointer to an Object struct representing the player.
 * @param y_acceleration A boolean representing whether or not the player is now
 * jumping.
 */
void set_jump_state(Player *player, bool jumping);

/**
 * Cause the player to perform an in-game jump.
 *
 * Confirm that the player is not already jumping, then set its kinematic values
 * and jumping state to perform a jump.
 *
 * @param player A pointer to an Object struct representing the player.
 */
void update_jump_state(Player *player);

/**
 * Calculate the correct position of the player based on kinematics.
 *
 * Calculate the correct y position of the player based on its y velocity and y
 * acceleration. If the player is on the floor, prevent it from falling further
 * and disable the jump state.
 *
 * @param player A pointer to an Object struct representing the player.
 */
void update_player_physics(Player *player);
