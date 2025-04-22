#include "tonc.h"

#include "input.h"
#include "kinematics.h"
#include "text.h"
#include "utils.h"

#include "assets/bg_with_road.h"
#include "assets/blob.h"

int main(void) {

  oam_init(oam_mem, MAX_SPRITES);

  memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
  memcpy32((u32 *)MEM_VRAM_OBJ, blobTiles, blobTilesLen / 4);

  memcpy16(pal_bg_mem, bg_with_roadPal, bg_with_roadPalLen / 2);
  memcpy32(tile_mem[0], bg_with_roadTiles, bg_with_roadTilesLen / 4);
  memcpy16(se_mem[31], bg_with_roadMap, bg_with_roadMapLen / 2);

  REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0;
  REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  int score = 0;
  score_init();

  int game_state = 0;
  display_init();

  int floor_level = 112;

  Object blob_1 = (Object){.attr = &oam_mem[0],
                           .x = 40,
                           .y = floor_level,
                           .is_active = true,
                           .x_velocity = 0,
                           .y_velocity = 0,
                           .x_acceleration = 0,
                           .y_acceleration = 0.5,
                           .jumping = false};

  blob_1.attr->attr0 =
      ATTR0_Y((int)blob_1.y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  blob_1.attr->attr1 = ATTR1_X((int)blob_1.x) | ATTR1_SIZE_16x16;
  blob_1.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

  Object blob_2 = (Object){
      .attr = &oam_mem[1], .x = 250, .y = floor_level, .is_active = false};

  blob_2.attr->attr0 = ATTR0_Y((int)blob_2.y) | ATTR0_SQUARE | ATTR0_4BPP |
                       ATTR0_MODE(ATTR0_REG);
  blob_2.attr->attr1 = ATTR1_X((int)blob_2.x) | ATTR1_SIZE_16x16;
  blob_2.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(1) | ATTR2_PALBANK(0);

  Object blob_3 = (Object){
      .attr = &oam_mem[2], .x = 250, .y = floor_level - 10, .is_active = false};

  blob_3.attr->attr0 = ATTR0_Y((int)blob_3.y) | ATTR0_SQUARE | ATTR0_4BPP |
                       ATTR0_MODE(ATTR0_REG);
  blob_3.attr->attr1 = ATTR1_X((int)blob_3.x) | ATTR1_SIZE_16x16;
  blob_3.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(2) | ATTR2_PALBANK(0);

  despawn(&blob_2);
  despawn(&blob_3);

  direction offscreen;

  update_obj_x(&blob_1);
  update_obj_y(&blob_1);

  update_obj_x(&blob_2);
  update_obj_y(&blob_2);

  update_obj_x(&blob_3);
  update_obj_y(&blob_3);

  int obj_2_timer = 0;
  int obj_3_timer = 0;

  int frame_counter = 0;

  int obj_2_threshold = 100;
  int obj_3_threshold = 250;

  while (1) {
    vid_vsync();

    switch (game_state) {
    case 0:
      poll_key_input(NULL, &game_state, &score);
      break;
    case 1: {

      // key input and physics update
      poll_key_input(&blob_1, &game_state, NULL);
      update_physics(&blob_1, floor_level);

      if (blob_1.is_active) {

        // update object while on screen, else update its timer
        if (!blob_2.is_active) {
          obj_2_timer++;
        } else {
          blob_2.x = blob_2.x - 1.5;
          obj_set_pos(blob_2.attr, (int)blob_2.x, (int)blob_2.y);
          update_obj_x(&blob_2);
          update_obj_y(&blob_2);
        }

        // spawn object after a timer
        if (obj_2_timer == obj_2_threshold) {
          spawn(&blob_2);
          set_obj_beginning(&blob_2);
          obj_2_timer = 0;
        }

        // update object while on screen, else update its timer
        if (!blob_3.is_active) {
          obj_3_timer++;
        } else {
          blob_3.x = blob_3.x - 1.2;
          obj_set_pos(blob_3.attr, (int)blob_3.x, (int)blob_3.y);
          update_obj_x(&blob_3);
          update_obj_y(&blob_3);
        }

        // spawn object after a timer
        if (obj_3_timer == obj_3_threshold) {
          spawn(&blob_3);
          set_obj_beginning(&blob_3);
          obj_3_timer = 0;
        }

        // load objects off screen
        check_obj_offscreen(&blob_2, &offscreen);
        if (offscreen.left) {
          despawn(&blob_2);
        }
        check_obj_offscreen(&blob_3, &offscreen);
        if (offscreen.left) {
          despawn(&blob_3);
        }

        if (!check_obj_overlap(&blob_1, &blob_2) &&
            !check_obj_overlap(&blob_1, &blob_3)) {
          // score update
          if (frame_counter % 5 == 0) {
            score_update();
          }
        } else {
          // game ending consequence
          despawn(&blob_1);
          despawn(&blob_2);
          despawn(&blob_3);
        }
      }
      // while loop loops is equivalent to amount of frames displayed
      frame_counter++;

      break;
    }

    case 2:
      break;
    }
  }
  return 0;
}
