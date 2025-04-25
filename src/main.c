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
  Object *player = &(Object){};
  player_constructor(player);

  // my obstacles :) TODO: wrap into for loops per obstacle type, which clears
  // out last magic numbers in main
  Object *above_blob = &(Object){};

  obstacle_constructor(above_blob, 1, FLOOR_LEVEL + DACTYL_HEIGHT_DIFF,
                       DACTYL_FRAME_SPAWN_THRESHOLD, BLOB);
  Object *middle_blob_1 = &(Object){};

  obstacle_constructor(middle_blob_1, 2, FLOOR_LEVEL,
                       CACTUS_FRAME_SPAWN_THRESHOLD, BLOB);

  Object *middle_blob_2 = &(Object){};

  obstacle_constructor(middle_blob_2, 3, FLOOR_LEVEL,
                       CACTUS_FRAME_SPAWN_THRESHOLD * 2, BLOB);

  Object *obstacles[OBSTACLE_AMOUNT] = {above_blob, middle_blob_1,
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
      for (int i = 0; i < OBSTACLE_AMOUNT; i++) {
        update_obstacle(obstacles[i]);
      }

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
