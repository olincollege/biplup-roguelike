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
  DINO_WALK_1 = 0,
  DINO_WALK_2 = 4,
  CACTUS = 8,
  DACTYL = 12,
  CLOUD = 4,
  PIPLUP = 5,
  SUDOWOODO = 6,
  AERODACTYL = 7,
  SWABLU = 8,
  BLOB = 9,
};

// The Object struct, which contains a libtonc OBJ_ATTR field and several
// kinematic properties that abstract interfacing directly with memory
typedef struct object_t {
  OBJ_ATTR *attr;
  int object_counter;
  bool is_active;
  float x;
  float y;
  float x_velocity;
  float y_velocity;
  float x_acceleration;
  float y_acceleration;
  bool jumping;
  int frame_spawn_threshold;
} Object;
