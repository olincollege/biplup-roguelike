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
extern int end_game_frame;
extern int last_cheat_frame;
extern int animation_frame;

int main(void) {
  // initialize key variables and GBA screen
  init_main();

  // player
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);

  // my obstacles :0
  Obstacle *dactyl = &(Obstacle){0};
  dactyl->obj_args = &(Object){0};

  obstacle_constructor(dactyl, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_BASE_X_VELOCITY, DACTYL_FRAME_SPAWN_THRESHOLD,
                       DACTYL);

  Obstacle *cactus_1 = &(Obstacle){0};
  cactus_1->obj_args = &(Object){0};

  obstacle_constructor(cactus_1, 2, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY,
                       CACTUS_FRAME_SPAWN_THRESHOLD, CACTUS);

  Obstacle *cactus_2 = &(Obstacle){0};
  cactus_2->obj_args = &(Object){0};
  obstacle_constructor(cactus_2, 3, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY,
                       CACTUS_FRAME_SPAWN_THRESHOLD * 2, CACTUS);

  Obstacle *cloud = &(Obstacle){0};
  cloud->obj_args = &(Object){0};
  obstacle_constructor(cloud, 4, FLOOR_LEVEL + CLOUD_HEIGHT_DIFF,
                       CLOUD_BASE_X_VELOCITY, CLOUD_FRAME_SPAWN_THRESHOLD * 2,
                       CLOUD);

  Obstacle *obstacles[OBSTACLE_AMOUNT] = {dactyl, cactus_1, cactus_2, cloud};

  while (true) {
    // sync up the video
    vid_vsync();
    if (frame_counter - last_cheat_frame > KEY_DEBOUNCE) {
      cheat_key_input(player, obstacles);
    }

    // the whole game is wrapped into a switch-case based on game state
    switch (game_state) {
    case PRE_GAME: { // game has not started
      pregame_key_input();
      break;
    }
    case GAME: { // main game

      // receive player input and update physics
      game_key_input(player);
      update_player_physics(player);

      // allow each object to move, spawn, or wait
      update_obstacles(obstacles);

      animation(player->obj_args, frame_counter);
      animation(obstacles[0]->obj_args, frame_counter);
      animation_frame = !animation_frame;

      // check if the player is colliding with each object
      if (!check_player_collision(player, obstacles)) {
        // score update
        if (frame_counter % COUNT_SCORE_ON_FRAME == 0) {
          score_update();
        }
      } else {
        // game ending consequence
        end_game();
      }
      // while loop loops is equivalent to amount of frames displayed
      break;
    }
    case POST_GAME: {
      end_text();
      if (frame_counter - end_game_frame > KEY_DEBOUNCE) {
        postgame_key_input(obstacles);
      }
      break;
    }
    }
    frame_counter++;
  }
  return EXIT_SUCCESS;
}
