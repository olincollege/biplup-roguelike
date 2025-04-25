#pragma once
#include "tonc.h"

typedef enum { PRE_GAME = 0, GAME = 1, POST_GAME = 2 } Game_State;

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
