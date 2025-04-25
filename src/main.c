#include "tonc.h"

#include "input.h"
#include "kinematics.h"
#include "object_utils.h"
#include "system_utils.h"
#include "text.h"
#include "types.h"

#include <stdbool.h>
#include <stdlib.h>

extern Game_State game_state;
extern int frame_counter;

int main(void) {
  init_main();

  // Object *obstacles[OBSTACLE_AMOUNT] = {};
  // Object *clouds[CLOUDS_AMOUNT];

  // player
  Object *player = &(Object){};
  player_constructor(player, 0, 40, FLOOR_LEVEL, BLOB);

  // my obstacles :)
  Object *above_blob = &(Object){};

  obstacle_constructor(above_blob, 1, SCREEN_WIDTH + (OFFSCREEN_OFFSET),
                       FLOOR_LEVEL + DACTYL_HEIGHT_DIFF, DACTYL_THRESHOLD,
                       BLOB);
  Object *middle_blob_1 = &(Object){};

  obstacle_constructor(middle_blob_1, 2, SCREEN_WIDTH + (OFFSCREEN_OFFSET),
                       FLOOR_LEVEL, CACTUS_THRESHOLD, BLOB);

  Object *middle_blob_2 = &(Object){};

  obstacle_constructor(middle_blob_2, 3, SCREEN_WIDTH + (OFFSCREEN_OFFSET),
                       FLOOR_LEVEL, CACTUS_THRESHOLD * 2, BLOB);

  Object *obstacles[OBSTACLE_AMOUNT] = {above_blob, middle_blob_1,
                                        middle_blob_2};

  // Object *above_blob = &(Object){};

  // obstacle_constructor(above_blob, 1, SCREEN_WIDTH + (OFFSCREEN_OFFSET),
  //                      FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
  //                      DACTYL_THRESHOLD, BLOB);
  // Object *middle_blob_1 = &(Object){};

  // obstacle_constructor(middle_blob_1, 2, SCREEN_WIDTH +
  // (OFFSCREEN_OFFSET),
  //                      FLOOR_LEVEL, CACTUS_THRESHOLD, BLOB);

  // Object *middle_blob_2 = &(Object){};

  // obstacle_constructor(middle_blob_2, 3, SCREEN_WIDTH +
  // (OFFSCREEN_OFFSET),
  //                      FLOOR_LEVEL, CACTUS_THRESHOLD * 2, BLOB);

  //  = {above_blob, middle_blob_1,
  //                                       middle_blob_2};
  // construct_obstacles(obstacles);
  // for (int i = 0; i < DACTYL_AMOUNT; i++) {
  //   // obstacle_constructor(dactyls[i], (i + 1),
  //   //                      SCREEN_WIDTH - (OFFSCREEN_OFFSET * (i + 1)),
  //   //                      FLOOR_LEVEL + DACTYL_HEIGHT_DIFF, BLOB);

  //   dactyls[i]->attr = &oam_mem[i + 1];
  //   dactyls[i]->x = SCREEN_WIDTH - (OFFSCREEN_OFFSET * (i + 1));
  //   dactyls[i]->y = FLOOR_LEVEL + DACTYL_HEIGHT_DIFF;
  //   dactyls[i]->is_active = false;

  //   dactyls[i]->attr->attr0 =
  //       ATTR0_Y((int)dactyls[i]->y) | ATTR0_SQUARE | ATTR0_4BPP |
  //       ATTR0_REG;
  //   dactyls[i]->attr->attr1 = ATTR1_X((int)dactyls[i]->x) |
  //   ATTR1_SIZE_16x16; dactyls[i]->attr->attr2 =
  //       ATTR2_ID(BLOB) | ATTR2_PRIO(i + 1) | ATTR2_PALBANK(BLOB);

  //   dactyls[i]->frame_spawn_threshold = DACTYL_THRESHOLD * (i + 1);
  //   update_obj_x(dactyls[i]);
  //   update_obj_y(dactyls[i]);
  //   despawn(dactyls[i]);
  // }
  // for (int i = 0; i < CACTUS_AMOUNT; i++) {

  //   cacti[i]->attr = &oam_mem[DACTYL_AMOUNT + (i + 1)];
  //   cacti[i]->x = SCREEN_WIDTH - (OFFSCREEN_OFFSET * (i + 1));
  //   cacti[i]->y = FLOOR_LEVEL;
  //   cacti[i]->is_active = false;

  //   cacti[i]->attr->attr0 =
  //       ATTR0_Y((int)cacti[i]->y) | ATTR0_SQUARE | ATTR0_4BPP |
  //       ATTR0_REG;
  //   cacti[i]->attr->attr1 = ATTR1_X((int)cacti[i]->x) | ATTR1_SIZE_16x16;
  //   cacti[i]->attr->attr2 = ATTR2_ID(BLOB) |
  //                           ATTR2_PRIO(DACTYL_AMOUNT + (i + 1)) |
  //                           ATTR2_PALBANK(BLOB);
  //   // obstacle_constructor(cacti[i], DACTYL_AMOUNT + (i + 1),
  //   //                      (SCREEN_WIDTH - (OFFSCREEN_OFFSET * (i +
  //   1))),
  //   //                      FLOOR_LEVEL, BLOB);
  //   cacti[i]->frame_spawn_threshold = CACTUS_THRESHOLD * (i + 1);
  //   update_obj_x(cacti[i]);
  //   update_obj_y(cacti[i]);
  //   despawn(cacti[i]);
  // }
  // manual test object
  // Object *obj = &(Object){};
  // obj->attr = &oam_mem[3];
  // obj->x = SCREEN_WIDTH;
  // obj->y = FLOOR_LEVEL;
  // obj->is_active = true;

  // obj->attr->attr0 =
  //     ATTR0_Y((int)obj->y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  // obj->attr->attr1 = ATTR1_X((int)obj->x) | ATTR1_SIZE_16x16;
  // obj->attr->attr2 = ATTR2_ID(BLOB) | ATTR2_PRIO(3) |
  // ATTR2_PALBANK(BLOB);

  while (true) {
    // sync up the video
    vid_vsync();

    // the whole game is wrapped into a switch-case based on game state
    switch (game_state) {
    case PRE_GAME: { // game has not started
      poll_key_input(NULL, NULL);
      break;
    }
    case GAME: { // main game

      // receive player input and update physics
      poll_key_input(player, NULL);
      update_physics(player, FLOOR_LEVEL);

      // allow each object to move, spawn, or wait
      for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
        update_obstacle(obstacles[i]);
      }

      // update_obstacle(dactyls[0]);

      // update_obstacle(cacti[0]);
      // update_obstacle(cacti[1]);

      // update_obstacle(obj);

      // check if the player is colliding with each object
      if (!check_player_collision(player, obstacles)) {
        // score update
        if (frame_counter % 5 == 0) {
          score_update();
        }
      } else {
        // game ending consequence
        end_game();
      }
      // while loop loops is equivalent to amount of frames displayed
      frame_counter++;
      break;
    }
    case POST_GAME: {
      end_text();
      poll_key_input(NULL, obstacles);
      break;
    }
    }
  }
  return EXIT_SUCCESS;
}
