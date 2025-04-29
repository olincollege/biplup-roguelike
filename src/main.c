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
  // initialize key variables and GBA screen
  init_main();

  // player
  Player *player = &(Player){0};
  player->obj_args = &(Object){0};
  player_constructor(player);

  // my obstacles :) TODO: wrap into for loops per obstacle type, which clears
  // out last magic numbers in main
  Obstacle *above_blob = &(Obstacle){0};
  above_blob->obj_args = &(Object){0};

  obstacle_constructor(above_blob, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_BASE_X_VELOCITY, DACTYL_FRAME_SPAWN_THRESHOLD,
                       DACTYL);
  Obstacle *middle_blob_1 = &(Obstacle){0};
  middle_blob_1->obj_args = &(Object){0};

  obstacle_constructor(middle_blob_1, 2, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY,
                       CACTUS_FRAME_SPAWN_THRESHOLD, CACTUS);

  Obstacle *middle_blob_2 = &(Obstacle){0};
  middle_blob_2->obj_args = &(Object){0};
  obstacle_constructor(middle_blob_2, 3, FLOOR_LEVEL, CACTI_BASE_X_VELOCITY,
                       CACTUS_FRAME_SPAWN_THRESHOLD * 2, CACTUS);

  Obstacle *obstacles[OBSTACLE_AMOUNT] = {above_blob, middle_blob_1,
                                          middle_blob_2};

  while (true) {
    // sync up the video
    vid_vsync();

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

      dino_walk_animation(player->obj_args, frame_counter);

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
      frame_counter++;
      break;
    }
    case POST_GAME: {
      end_text();
      postgame_key_input(obstacles);
      break;
    }
    }
  }
  return EXIT_SUCCESS;
}
