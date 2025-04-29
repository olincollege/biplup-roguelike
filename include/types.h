/**
 * types.h
 *
 * Define key structs and enums used by files throughout the game.
 *
 * Since nearly every file references the Object struct, it is contained here
 * instead of in a broader utility function, such that imports are more precise.
 */

#pragma once

#include "tonc.h"

// Enumeration of the three game states
typedef enum { PRE_GAME = 0, GAME = 1, POST_GAME = 2 } Game_State;

// Enumeration of each possible sprite in the game
enum {
  DINO = 0,
  CACTUS = 32,
  DACTYL = 48,
  CLOUD = 64,
  BIPLUP = 80,
  SUDOWOODO = 112,
  AERODACTYL = 128,
  SWABLU = 8,
  BLOB = 9,
};

/**
 * The Object struct, which contains a libtonc OBJ_ATTR field and several
 * kinematic properties that abstract interfacing directly with memory. Note
 * that Objects should never be instantiated; instead, use either the Player or
 * the Obstacle struct.
 */
typedef struct object_t {
  OBJ_ATTR *attr;     // libtonc macro storing data in bitmap form
  int object_counter; // the global index of this object
  float x;            // x position
  float y;            // y position
} Object;

/**
 * The Player struct, which contains an Object struct and player-specific
 * fields.
 */
typedef struct player_t {
  struct object_t *obj_args; // general Object struct
  float y_velocity;          // y velocity for jumping
  float y_acceleration;      // y acceleration for falling
  bool jumping; // state indicator for if the player is currently jumping
} Player;

/**
 * The Obstacle struct, which contains an Object struct and obstacle-specific
 * fields.
 */
typedef struct obstacle_t {
  struct object_t *obj_args; // general Object struct
  bool is_active;   // state indicator for if the object is waiting to spawn
  float x_velocity; // x velocity to simulate dino running
  int frame_spawn_threshold; // respawn at this frame count multiple
} Obstacle;
