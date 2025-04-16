#include "assets/blob/blob.h"
#include "example.h"
#include "player_movement.h"


int main(void) {
  // general idea - generate object way off the screen and as it moves over the
  // screen, check for collisions. when it goes way off the screen, despawn it.
  memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
  memcpy32((u32 *)MEM_VRAM_OBJ, blobTiles, blobTilesLen / 4);

  Object blob = (Object){.attr = &((OBJ_ATTR *)MEM_OAM)[0],
                         .x = 10,
                         .y = 100,
                         .x_velocity = 0,
                         .y_velocity = 0,
                         .x_acceleration = 0,
                         .y_acceleration = 1,
                         .jumping = false};

  set_obj_x(&blob, blob.x);
  set_obj_y(&blob, blob.y);

  blob.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

  // OBJ_ATTR *blob_attrs = &((OBJ_ATTR*) MEM_OAM)[0];
  // int x = 0, y = 0;
  // blob_attrs->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
  // blob_attrs->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
  // blob_attrs->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

  REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D;

  while (1) {
    vid_vsync();
    key_input(&blob);
    update_physics(&blob);
    if (blob.y >= 100) {
      blob.y = 100;
      set_jumping(&blob, false);
    }
    set_obj_x(&blob, blob.x);
    set_obj_y(&blob, blob.y);
    // key_input(&blob);

    // x = (x + 3) % SCREEN_WIDTH;
    // y = (y + 3) % SCREEN_HEIGHT;
    // blob_attrs->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
    // blob_attrs->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
    // blob_attrs->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);
  }
  return 0;
}

// void init_main() {

// }

// void update_main() {

// }
