#include "object_utils.h"
#include "kinematics.h"
#include "system_utils.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>

extern RECT offscreen;
extern int frame_counter;
extern int score;
extern int animation_frame;

void object_constructor(Object *obj, int obj_counter, float x, float y,
                        int tile_number) {
  obj->object_counter = obj_counter;
  obj->attr = &oam_mem[obj_counter];
  obj->x = x;
  obj->y = y;
  obj->default_sprite = tile_number;

  obj->attr->attr0 =
      ATTR0_Y((int)obj->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  obj->attr->attr1 = ATTR1_X((int)obj->x) | ATTR1_SIZE_32x32;
  obj->attr->attr1 = ATTR1_X((int)obj->x) | ATTR1_SIZE_32x32;
  obj->attr->attr2 = ATTR2_ID(tile_number) | ATTR2_PRIO(obj_counter) |
                     ATTR2_PALBANK(tile_number);

  update_obj_x(obj);
  update_obj_y(obj);
}

void obstacle_constructor(Obstacle *obj, int obj_counter, float y,
                          float x_velocity, int frame_spawn_threshold,
                          int tile_number) {
  object_constructor(obj->obj_args, obj_counter,
                     SCREEN_WIDTH + OFFSCREEN_OFFSET, y, tile_number);
  obj->is_active = false;
  obj->x_velocity = x_velocity;
  obj->frame_spawn_threshold = frame_spawn_threshold;
  despawn(obj);
}

void player_constructor(Player *obj) {
  object_constructor(obj->obj_args, 0, PLAYER_X_POS, FLOOR_LEVEL, BIPLUP);
  object_constructor(obj->obj_args, 0, PLAYER_X_POS, FLOOR_LEVEL, BIPLUP);
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

void update_obstacles(Obstacle **obstacles) {
  for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
    // if object is moving
    if (obstacles[i]->is_active) {
      // if the object is offscreen, make sure it is hidden
      check_obj_offscreen(obstacles[i]->obj_args, &offscreen);
      if (offscreen.left) {
        despawn(obstacles[i]);
      }

      // progress the object
      obj_set_pos(obstacles[i]->obj_args->attr,
                  (int)(obstacles[i]->obj_args->x + obstacles[i]->x_velocity),
                  (int)obstacles[i]->obj_args->y);
      update_obj_x(obstacles[i]->obj_args);
      update_obj_y(obstacles[i]->obj_args);

      // if object is waiting to spawn
    } else if (frame_counter % obstacles[i]->frame_spawn_threshold == 0) {
      spawn(obstacles[i]);
      reset_obstacle_position(obstacles[i]);
    }
  }
  // if the score is a multiple of 500, the obstacles should speed up
  if (score % SCORE_MILESTONE == 0) {
    update_obstacle_velocities(obstacles);
  }
}

void update_obstacle_velocities(Obstacle **obstacles) {
  for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
    // check to see if its a dactyl or if its a cactus
    bool is_dactyl =
        obstacles[i]->obj_args->y == FLOOR_LEVEL + DACTYL_HEIGHT_DIFF;
    // determine multiplier based on how long your run is
    float vel_multiplier = (((float)(score / SCORE_MILESTONE)) / 10.0);

    float base_obstacle_velocity =
        (is_dactyl) ? DACTYL_BASE_X_VELOCITY : CACTI_BASE_X_VELOCITY;

    float new_obstacle_vel = base_obstacle_velocity * (1 + vel_multiplier);

    set_obstacle_x_velocity(obstacles[i], new_obstacle_vel);
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
  int obj1_width = obj_get_width(obj1->attr) - HITBOX_BUFFER;
  int obj1_width = obj_get_width(obj1->attr) - HITBOX_BUFFER;
  int obj1_height = obj_get_height(obj1->attr);

  // features of object 2
  int obj2_x = obj2->x;
  int obj2_y = obj2->y;
  int obj2_width = obj_get_width(obj2->attr) - HITBOX_BUFFER;
  int obj2_width = obj_get_width(obj2->attr) - HITBOX_BUFFER;
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

void animation(Object *obj, int frame, int id) {
  void animation(Object * obj, int frame, int id) {
    if (frame % 7 == 1) {
      if (animation_frame == 0) {
        obj->attr->attr2 =
            ATTR2_ID(id) | ATTR2_PRIO(obj->object_counter) | ATTR2_PALBANK(id);
        if (animation_frame == 0) {
          obj->attr->attr2 = ATTR2_ID(id) | ATTR2_PRIO(obj->object_counter) |
                             ATTR2_PALBANK(id);
        } else {
          obj->attr->attr2 = ATTR2_ID(id + 16) |
                             ATTR2_PRIO(obj->object_counter) |
                             ATTR2_PALBANK(id + 16);
          obj->attr->attr2 = ATTR2_ID(id + 16) |
                             ATTR2_PRIO(obj->object_counter) |
                             ATTR2_PALBANK(id + 16);
        }
        animation_frame = !animation_frame;
        animation_frame = !animation_frame;
      }
    }

    Sprite_ID get_sprite_id(Object * obj) {
      return obj->default_sprite + 96 * cheat_sprite_state;
    }
