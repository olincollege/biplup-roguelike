/**
 * object_utils.h
 *
 * Describe functions and constants that construct, arrange, and compare objects
 * in the game, such as obstacles and the player.
 *
 * The constants in this file are obstacle-specific values that Objects use
 * depending on their type. Functions include object-specific constructors,
 * depawn and respawn functionality, position resetting, and checking overlap
 * wwith the screen and other objects.
 */

#pragma once

#include "tonc.h"
#include "types.h"
#include <stdbool.h>
#include <stdint.h>

#define DACTYL_HEIGHT_DIFF -35 // offset dactyls from the floor height
#define CLOUD_HEIGHT_DIFF -100 // offset clouds from the floor height
#define DACTYL_HEIGHT_DIFF -35 // offset dactyls from the floor height
#define CLOUD_HEIGHT_DIFF -100 // offset clouds from the floor height

#define CACTUS_AMOUNT 2 // number of cacti in the game
#define DACTYL_AMOUNT 1 // number of dactyls in the game
#define CLOUD_AMOUNT 1  // number of clouds in the game
#define OBSTACLE_AMOUNT                                                        \
  CACTUS_AMOUNT + DACTYL_AMOUNT +                                              \
      CLOUD_AMOUNT      // total obstacles present in the game
#define HITBOX_BUFFER 8 // buffer for hitbox

#define CACTUS_FRAME_SPAWN_THRESHOLD 100 // frame count before cacti respawn
#define DACTYL_FRAME_SPAWN_THRESHOLD 300 // frame count before dactyls respawn
#define CLOUD_FRAME_SPAWN_THRESHOLD 80   // frame count before clouds respawn

/**
 * Construct a generic game object.
 *
 * Given a pointer to an empty Object struct and several attributes, construct a
 * new game object at this pointer. This function should not be called directly
 * to construct a game object; instead, use obstacle_constructor or
 * player_constructor.
 *
 * @param obj A pointer to the empty Object struct.
 * @param obj_counter An int representing the index of this object in the game.
 * @param x An int that is the x position of the object.
 * @param y An int that is the y position of the object.
 * @param tile_number An int indicating the sprite of this object.
 */
void object_constructor(Object *obj, int obj_counter, float x, float y,
                        int tile_number);

/**
 * Construct an obstacle.
 *
 * Given a pointer to an empty Obstacle struct and several attributes, construct
 * a new obstacle at this pointer that possesses the attributes. The following
 * fields are also predefined with this function:
 * -> x: SCREEN_WIDTH + OFFSCREEN_OFFSET
 * -> is_active: false
 *
 * @param obs A pointer to the empty Obstacle struct.
 * @param obj_counter An int representing the index of this obstacle in the
 * game.
 * @param y An float that is the y position of the obstacle.
 * @param x_velocity A float representing the obstacle's base velocity.
 * @param frame_spawn_threshold An int that defines the number of frames that
 * must pass before the obstacle respawns.
 * @param tile_number An int indicating the sprite of this obstacle.
 */

void obstacle_constructor(Obstacle *obs, int obj_counter, float y,
                          float x_velocity, int frame_spawn_threshold,
                          int tile_number);

/**
 * Construct a player.
 *
 * Given a pointer to an empty Player struct, construct a new player using
 * predefined values for all of its fields:
 * -> obj_counter: 0
 * -> x: PLAYER_X_POS
 * -> y: FLOOR_LEVEL
 * -> is_active: true
 * -> tile_number: DINO
 *
 * @param player A pointer to the empty Object struct.
 */
void player_constructor(Player *player);

/**
 * Disable an object in the game..
 *
 * Given a pointer to an Obstacle struct, hide the obstacle and set it to an
 * inactive state. This forces the obstacle to wait for the frame counter until
 * it is allowed to respawn.
 *
 * @param obs A pointer to an Obstacle struct.
 */
void despawn(Obstacle *obs);

/**
 * Enable an object in the game.
 *
 * Given a pointer to an Obstacle struct, show the obstacle and set it to an
 * active state. This allows the obstacle to begin traversing the screen, if it
 * is an obstacle.
 *
 * @param obs A pointer to an Obstacle struct.
 */
void spawn(Obstacle *obs);

/**
 * Update all of the obstacle velocities when the score hits a milestone.
 *
 * Given an array of obstacles, update all of those obstacles' velocities by a
 * multiplier based on the score.
 *
 * @param obstacles The array of obstacles to be edited.
 */
void update_obstacle_velocities(Obstacle **obstacles);

/**
 * Determine how the game's obstacles should be moving in their current states
 * and enact it.
 *
 * Given a pointer to a array of Obstacles, check if each is active or not. If
 * so, progress the obstacle across the screen. If not, wait for the frame
 * counter to advance until the obstacle can spawn.
 *
 * @param obs A pointer to an array of Obstacle structs.
 */
void update_obstacles(Obstacle **obstacles);

/**
 * Reset all obstacles in the game to their starting position.
 *
 * Given a pointer to a list of Obstacles, reset their x positions to the
 * default location SCREEN_WIDTH + OFFSCREEN_OFFSET.
 *
 * @param obstacles A pointer to a list of Objects that are obstacles.
 */
void restart_obstacles(Obstacle **obstacles);

/**
 * Determine if there is overlap between two objects on the screen.
 *
 * Given two object's attributes, determine whether or not the sprites are
 * colliding based on their (x,y) coordinates and sprite dimensions. Writing a
 * 1 to the result pointer indicates a collision, whereas a 0 indicates that
 * the objects are not colliding.
 *
 * @param obj1 A pointer to the first object.
 * @param obj2 A pointer to the second object.
 * @return An bool to indicate if the objects are colliding.
 */
bool check_obj_overlap(const Object *obj1, const Object *obj2);

/**
 * Determine if any part of an object is offscreen.
 *
 * Given a pointer to an object, use the position and size of the object to
 * determine if it is off of the screen in any way. Return a dir struct
 * describing which parts of the screen it is off from.
 *
 * @param obj1 A pointer to the  object.
 * @param dir A pointer to a dir struct with values of 1 wherever the object
 *            is offscreen.
 */
void check_obj_offscreen(const Object *obj, RECT *dir);

/**
 * Determine if the player is colliding with any obstacles.
 *
 * Given a pointer to a list of Objects representing the game obstacles and a
 * pointer to an Object representing the player, evaluate if the player is
 * colliding with any of them. If so, return true, and return false if not.
 *
 * @param player A pointer to the player.
 * @param obstacles An pointer to a list of Objects representing obstacles.
 * @return A boolean indicating if the player is colliding with any obstacles.
 */
bool check_player_collision(Player *player, Obstacle **obstacles);

void cheat_toggle_pokemon(Player *player, Obstacle **obstacles);

void animation(Object *obj, int frame);

void change_sprite(Object *obj, int id);

Sprite_ID get_sprite_id(Object *obj);
