#include "object_utils.h"
#include "kinematics.h"
#include "system_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

extern RECT offscreen;
extern int frame_counter;
extern int animation_dino_frame;

void object_constructor(Object *obj, int obj_counter, float x, float y,
                        int tile_number) {
  obj->object_counter = obj_counter;
  obj->attr = &oam_mem[obj_counter];
  obj->x = x;
  obj->y = y;

  obj->attr->attr0 =
      ATTR0_Y((int)obj->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  obj->attr->attr1 = ATTR1_X((int)obj->x) | ATTR1_SIZE_16x16;
  obj->attr->attr2 = ATTR2_ID(tile_number) | ATTR2_PRIO(obj_counter) |
                     ATTR2_PALBANK(tile_number);

  update_obj_x(obj);
  update_obj_y(obj);
}

void obstacle_constructor(Obstacle *obs, int obj_counter, float y,
                          int frame_spawn_threshold, int tile_number) {
  object_constructor(obs->obj_args, obj_counter,
                     SCREEN_WIDTH + OFFSCREEN_OFFSET, y, tile_number);

  obs->is_active = false;
  obs->x_velocity = 0;
  obs->frame_spawn_threshold = frame_spawn_threshold;
  despawn(obs);
}

void player_constructor(Player *obj) {
  object_constructor(obj->obj_args, 0, PLAYER_X_POS, FLOOR_LEVEL, DINO_WALK_1);
  obj->y_velocity = 0;
  obj->y_acceleration = PLAYER_Y_ACCEL;
}

void despawn(Obstacle *obs) {
  obj_hide(obs->obj_args->attr);
  obs->is_active = false;
}

void spawn(Obstacle *obs) {
  obj_unhide(obs->obj_args->attr, 0);
  obs->is_active = true;
}

void update_obstacle(Obstacle *obs) {
  // if object is moving
  if (obs->is_active) {
    // if the object is offscreen, make sure it is hidden
    check_obj_offscreen(obs->obj_args, &offscreen);
    if (offscreen.left) {
      despawn(obs);
    }

    // progress the object
    obj_set_pos(obs->obj_args->attr,
                (int)(obs->obj_args->x - OBSTACLE_X_VELOCITY),
                (int)obs->obj_args->y);
    update_obj_x(obs->obj_args);
    update_obj_y(obs->obj_args);

    // if object is waiting to spawn
  } else if (frame_counter % obs->frame_spawn_threshold == 0) {
    spawn(obs);
    reset_obstacle_position(obs);
  }
}

void restart_obstacles(Obstacle **obstacles) {
  for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
    despawn(obstacles[i]);
    reset_obstacle_position(obstacles[i]);
  }
}

bool check_obj_overlap(const Object *obj1, const Object *obj2) {
  // features of object 1
  int obj1_x = obj1->x;
  int obj1_y = obj1->y;
  int obj1_width = obj_get_width(obj1->attr);
  int obj1_height = obj_get_height(obj1->attr);

  // features of object 2
  int obj2_x = obj2->x;
  int obj2_y = obj2->y;
  int obj2_width = obj_get_width(obj2->attr);
  int obj2_height = obj_get_height(obj2->attr);

  // AABB collision detection
  int not_right = obj1_x < obj2_x + obj2_width;
  int not_left = obj1_x + obj1_width > obj2_x;
  int not_below = obj1_y < obj2_y + obj2_height;
  int not_above = obj1_y + obj1_height > obj2_y;
  if (not_right && not_left && not_below && not_above) {
    return true;
  }

  return false;
}

void check_obj_offscreen(const Object *obj, RECT *dir) {

  dir->left = 0;
  dir->right = 0;
  dir->top = 0;
  dir->bottom = 0;

  // features of object
  int obj_x = obj->x;
  int obj_y = obj->y;
  int obj_width = obj_get_width(obj->attr);
  int obj_height = obj_get_height(obj->attr);

  // left/right
  if (obj_x - obj_width > SCREEN_WIDTH) {
    dir->right = 1;
  }
  if (obj_x + obj_width < 0) {
    dir->left = 1;
  }

  // up/down
  if (obj_y - obj_height > SCREEN_HEIGHT) {
    dir->bottom = 1;
  }
  if (obj_y + obj_height < 0) {
    dir->top = 1;
  }
}

bool check_player_collision(Player *player, Obstacle **obstacles) {
  for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
    if (check_obj_overlap(player->obj_args, obstacles[i]->obj_args)) {
      return true;
    }
  }
  return false;
}

void dino_walk_animation(Object *dino, int frame) {
  if (frame % 7 == 1) {
    if (animation_dino_frame == 0) {
      dino->attr->attr2 = ATTR2_ID(DINO_WALK_1) |
                          ATTR2_PRIO(dino->object_counter) |
                          ATTR2_PALBANK(DINO_WALK_1);
    } else {
      dino->attr->attr2 = ATTR2_ID(DINO_WALK_2) |
                          ATTR2_PRIO(dino->object_counter) |
                          ATTR2_PALBANK(DINO_WALK_2);
    }
    animation_dino_frame = !animation_dino_frame;
  }
}
