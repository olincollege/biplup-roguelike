#include "test_object_utils.h"

#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

#include "assets/blob.h"

extern int frame_counter;
extern int score;
extern int cheat_sprite_state;
extern int last_cheat_frame;

#define EPSILON 0.001

int test_right_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = 240 + 32 + 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, 10.0, CACTUS);
  object->x = 240 + 32 + 1;

  check_obj_offscreen(object, &direction);

  return direction.right == 1;
}

int test_partly_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = 240 + 16;
  RECT direction;
  object_constructor(object, 1, offscreen_x, 10.0, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->x = 240 + 16;

  check_obj_offscreen(object, &direction);

  return direction.right == 0;
}

int test_left_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = -32 - 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, 10.0, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->x = -32 - 1;

  check_obj_offscreen(object, &direction);

  return direction.left == 1;
}

int test_top_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_y = -32 - 1;
  RECT direction;
  object_constructor(object, 1, 10.0, offscreen_y, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->y = -32 - 1;

  check_obj_offscreen(object, &direction);

  return direction.top == 1;
}

int test_bottom_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_y = 160 + 32 + 1;
  RECT direction;
  object_constructor(object, 1, 10.0, offscreen_y, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->y = 160 + 32 + 1;
  check_obj_offscreen(object, &direction);

  return direction.bottom == 1;
}

int test_corner_top_left_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = -32 - 1;
  float offscreen_y = -32 - 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, offscreen_y, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->x = -32 - 1;
  object->y = -32 - 1;

  check_obj_offscreen(object, &direction);

  return direction.top == 1 && direction.left == 1;
}

int test_corner_top_right_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = 240 + 32 + 1;
  float offscreen_y = -32 - 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, offscreen_y, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->x = 240 + 32 + 1;
  object->y = -32 - 1;

  check_obj_offscreen(object, &direction);

  return direction.top == 1 && direction.right == 1;
}

int test_corner_bottom_left_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = -32 - 1;
  float offscreen_y = 160 + 32 + 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, offscreen_y, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));

  object->x = -32 - 1;
  object->y = 160 + 32 + 1;

  check_obj_offscreen(object, &direction);

  return direction.left == 1 && direction.bottom == 1;
}

int test_corner_bottom_right_offscreen(void) {
  Object *object = &(Object){};
  float offscreen_x = 240 + 32 + 1;
  float offscreen_y = 160 + 32 + 1;
  RECT direction;
  object_constructor(object, 1, offscreen_x, offscreen_y, CACTUS);
  object->x = 0;
  object->y = 0;
  obj_set_attr(object->attr,
               ATTR0_Y((int)object->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG,
               ATTR1_X((int)object->x) | ATTR1_SIZE_32x32,
               ATTR2_ID(CACTUS) | ATTR2_PRIO(1) | ATTR2_PALBANK(CACTUS));
  object->x = 240 + 32 + 1;
  object->y = 160 + 32 + 1;

  check_obj_offscreen(object, &direction);

  return direction.bottom == 1 && direction.right == 1;
}

int test_update_moving_obstacles(void) {
  float velocity = -2.5;
  int initial_x = 100;
  int initial_y = 32;

  frame_counter = 50;

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, initial_y, velocity, 50, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, initial_y, velocity, 50, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, initial_y, velocity, 50, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, initial_y, velocity, 50, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  for (int i = 0; i < 4; i++) {
    obj_set_pos(obstacles[i]->obj_args->attr, initial_x, initial_y);
    obstacles[i]->obj_args->x = initial_x;
    obstacles[i]->obj_args->y = initial_y;
    spawn(obstacles[i]);
  }

  update_obstacles(obstacles);

  int has_passed = 1;
  for (int i = 0; i < 4; i++) {
    if (obstacles[i]->obj_args->x != (int)(initial_x + velocity)) {
      has_passed = 0;
      break;
    }
  }

  return has_passed;
}

int test_update_still_obstacles(void) {
  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  frame_counter = 50;

  obstacle_constructor(obstacle_1, 1, 32, 0.3, 50, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, 32, 0.3, 50, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, 32, 0.3, 50, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, 32, 0.3, 50, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  update_obstacles(obstacles);

  int has_passed = 1;

  for (int i = 0; i < 4; i++) {
    if (!obstacles[i]->is_active ||
        obstacles[i]->obj_args->x != SCREEN_WIDTH + OFFSCREEN_OFFSET) {
      has_passed = 0;
    }
  }
  return has_passed;
}

float test_velocity_milestone_1(void) {
  score = 500;
  float vel_multiplier = (((float)(score / 500)) / 10.0);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_BASE_X_VELOCITY, 100, DACTYL);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  update_obstacle_velocities(obstacles);
  int has_passed = 1;
  float comparison_1 = (obstacles[0]->x_velocity -
                        (DACTYL_BASE_X_VELOCITY * (1 + vel_multiplier)));
  if ((comparison_1 > 0 ? comparison_1 : -1 * comparison_1) >= EPSILON) {
    has_passed = 0;
  }

  for (int i = 1; i < 4; i++) {
    int comparison_2 = (obstacles[i]->x_velocity -
                        (CACTI_BASE_X_VELOCITY * (1 + vel_multiplier)));

    if ((comparison_2 > 0 ? comparison_2 : -1 * comparison_2) >= EPSILON) {
      has_passed = 0;
      break;
    }
  }
  score = 0;
  return has_passed;
}

int test_velocity_milestone_2(void) {
  score = 1000;
  float vel_multiplier = (((float)(score / 500)) / 10.0);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_BASE_X_VELOCITY, 100, DACTYL);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  update_obstacle_velocities(obstacles);
  int has_passed = 1;
  float comparison_1 = (obstacles[0]->x_velocity -
                        (DACTYL_BASE_X_VELOCITY * (1 + vel_multiplier)));
  if ((comparison_1 > 0 ? comparison_1 : -1 * comparison_1) >= EPSILON) {
    has_passed = 0;
  }

  for (int i = 1; i < 4; i++) {
    int comparison_2 = (obstacles[i]->x_velocity -
                        (CACTI_BASE_X_VELOCITY * (1 + vel_multiplier)));
    if ((comparison_2 > 0 ? comparison_2 : -1 * comparison_2) >= EPSILON) {
      has_passed = 0;
      break;
    }
  }
  score = 0;
  return has_passed;
}

int test_velocity_milestone_3(void) {
  score = 0;
  score = 1500;
  float vel_multiplier = (((float)(score / 500)) / 10.0);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_BASE_X_VELOCITY, 100, DACTYL);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  update_obstacle_velocities(obstacles);
  int has_passed = 1;
  float comparison_1 = (obstacles[0]->x_velocity -
                        (DACTYL_BASE_X_VELOCITY * (1 + vel_multiplier)));
  if ((comparison_1 > 0 ? comparison_1 : -1 * comparison_1) >= EPSILON) {
    has_passed = 0;
  }

  for (int i = 1; i < 4; i++) {
    int comparison_2 = (obstacles[i]->x_velocity -
                        (CACTI_BASE_X_VELOCITY * (1 + vel_multiplier)));
    if ((comparison_2 > 0 ? comparison_2 : -1 * comparison_2) >= EPSILON) {
      has_passed = 0;
      break;
    }
  }
  score = 0;
  return has_passed;
}

int test_velocity_milestone_4(void) {
  score = 2000;
  float vel_multiplier = (((float)(score / 500)) / 10.0);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_BASE_X_VELOCITY, 100, DACTYL);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY, 100,
                       CACTUS);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  update_obstacle_velocities(obstacles);
  int has_passed = 1;
  float comparison_1 = (obstacles[0]->x_velocity -
                        (DACTYL_BASE_X_VELOCITY * (1 + vel_multiplier)));
  if ((comparison_1 > 0 ? comparison_1 : -1 * comparison_1) >= EPSILON) {
    has_passed = 0;
  }

  for (int i = 1; i < 4; i++) {
    int comparison_2 = (obstacles[i]->x_velocity -
                        (CACTI_BASE_X_VELOCITY * (1 + vel_multiplier)));
    if ((comparison_2 > 0 ? comparison_2 : -1 * comparison_2) >= EPSILON) {
      has_passed = 0;
      break;
    }
  }
  score = 0;
  return has_passed;
}

int test_restart_obstacles(void) {
  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  int initial_x = 100;
  int initial_y = 30;

  obstacle_constructor(obstacle_1, 1, initial_y, 0.3, 100, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, initial_y, 0.3, 100, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, initial_y, 0.3, 100, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, initial_y, 0.3, 100, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  for (int i = 0; i < 4; i++) {
    obj_set_pos(obstacles[i]->obj_args->attr, initial_x, initial_y);
    obstacles[i]->obj_args->x = initial_x;
    obstacles[i]->obj_args->y = initial_y;
    spawn(obstacles[i]);
  }

  restart_obstacles(obstacles);

  int has_passed = 1;
  for (int i = 0; i < 4; i++) {
    if (obstacles[i]->is_active ||
        obstacles[i]->obj_args->x != SCREEN_WIDTH + OFFSCREEN_OFFSET) {
      has_passed = 0;
      break;
    }
  }
  return has_passed;
}

int test_collisions(void) {
  Player *player = &(Player){};
  player->obj_args = &(Object){};
  player_constructor(player);

  int player_x = 100, player_y = 100;
  obj_set_pos(player->obj_args->attr, player_x, player_y);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1,
                       player_y - (obj_get_width(player->obj_args->attr) - 1),
                       0.3, 100, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, 160, 0.3, 100, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, 150, 0.3, 100, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, 133, 0.3, 100, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  for (int i = 0; i < 4; i++) {
    obj_set_pos(obstacles[i]->obj_args->attr, 250 - ((i + 1) * 50),
                obstacles[i]->obj_args->y);
    obstacles[i]->obj_args->x = 250 - ((i + 1) * 50);
    spawn(obstacles[i]);
  }

  bool result = check_player_collision(player, obstacles);

  return result == true;
}

int test_no_collisions(void) {
  Player *player = &(Player){};
  player->obj_args = &(Object){};
  player_constructor(player);

  int player_x = 100, player_y = 100;
  obj_set_pos(player->obj_args->attr, player_x, player_y);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, 0, 0.3, 100, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, 0, 0.3, 100, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, 0, 0.3, 100, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, 0, 0.3, 100, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  for (int i = 0; i < 4; i++) {
    obj_set_pos(obstacles[i]->obj_args->attr, 250 - ((i + 1) * 50),
                obstacles[i]->obj_args->y);
    obstacles[i]->obj_args->x = 250 - ((i + 1) * 50);
    spawn(obstacles[i]);
  }

  bool result = check_player_collision(player, obstacles);

  return result == false;
}

int test_cheat_toggle_pokemon(void) {
  cheat_sprite_state = 0;
  frame_counter = 27;

  Player *player = &(Player){};
  player->obj_args = &(Object){};
  player_constructor(player);

  Obstacle *obstacle_1 = &(Obstacle){};
  obstacle_1->obj_args = &(Object){};

  obstacle_constructor(obstacle_1, 1, 32, 0.3, 100, BLOB);

  Obstacle *obstacle_2 = &(Obstacle){};
  obstacle_2->obj_args = &(Object){};

  obstacle_constructor(obstacle_2, 2, 32, 0.3, 100, BLOB);

  Obstacle *obstacle_3 = &(Obstacle){};
  obstacle_3->obj_args = &(Object){};

  obstacle_constructor(obstacle_3, 3, 32, 0.3, 100, BLOB);

  Obstacle *obstacle_4 = &(Obstacle){};
  obstacle_4->obj_args = &(Object){};

  obstacle_constructor(obstacle_4, 4, 32, 0.3, 100, BLOB);

  Obstacle *obstacles[4] = {obstacle_1, obstacle_2, obstacle_3, obstacle_4};

  cheat_toggle_pokemon(player, obstacles);

  return cheat_sprite_state == 1 && last_cheat_frame == frame_counter;
}
