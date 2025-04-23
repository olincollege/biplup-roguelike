#pragma once
#include "tonc.h"

typedef enum { PRE_GAME = 0, GAME = 1, POST_GAME = 2 } Game_State;

enum {
  BLOB = 0,
  DINO = 1,
  CACTUS = 2,
  DACTYL = 3,
  CLOUD = 4,
  PIPLUP = 5,
  SUDOWOODO = 6,
  AERODACTYL = 7,
  SWABLU = 8,
};

typedef struct object_t {
  OBJ_ATTR *attr;
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
