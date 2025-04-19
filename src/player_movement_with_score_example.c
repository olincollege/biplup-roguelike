#include "include/blob.h"
#include "include/player_movement.h"
#include "include/score.h"
#include "tonc.h"

int main(void) {
  // build the blob
  oam_init(oam_mem, MAX_SPRITES);

  memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
  memcpy32((u32 *)MEM_VRAM_OBJ, blobTiles, blobTilesLen / 4);

  Object blob = (Object){.attr = &oam_mem[0],
                         .x = 10,
                         .y = 100,
                         .x_velocity = 0,
                         .y_velocity = 0,
                         .x_acceleration = 0,
                         .y_acceleration = 1,
                         .jumping = false};

  blob.attr->attr0 =
      ATTR0_Y((int)blob.y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  blob.attr->attr1 = ATTR1_X((int)blob.x) | ATTR1_SIZE_16x16;
  blob.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

  // build the score
  irq_init(NULL);
  irq_add(II_VBLANK, NULL);
  score_init();

  REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0;

  while (1) {
    vid_vsync();
    key_input(&blob);
    update_physics(&blob);
    score_update();
  }
  return 0;
}
