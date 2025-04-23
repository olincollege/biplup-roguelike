#include "system_utils.h"
#include "text.h"
#include "tonc.h"
#include "types.h"

#include "assets/bg_with_road.h"
#include "assets/blob.h"

int score;
Game_State game_state;
RECT offscreen;
int frame_counter;

void init_main(void) {
  oam_init(oam_mem, MAX_SPRITES);

  memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
  memcpy32(tile_mem_obj[0], blobTiles, blobTilesLen / 4);

  memcpy16(pal_bg_mem, bg_with_roadPal, bg_with_roadPalLen / 2);
  memcpy32(tile_mem[0], bg_with_roadTiles, bg_with_roadTilesLen / 4);
  memcpy16(se_mem[31], bg_with_roadMap, bg_with_roadMapLen / 2);

  REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0;
  REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  score = 0;
  game_state = PRE_GAME;
  frame_counter = 0;
  score_init();
  start_text();
}

void reset_game_state(void) {
  game_state = GAME;
  score = 0;
}

void end_game(void) { game_state = POST_GAME; }
