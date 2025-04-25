#include "system_utils.h"
#include "text.h"
#include "tonc.h"
#include "types.h"

#include "assets/bg_with_road.h"
#include "assets/blob.h"
#include "assets/cactus_1.h"
#include "assets/dactyl_glide.h"
#include "assets/dino_walk.h"
int score;
Game_State game_state;
RECT offscreen;
int frame_counter;
int animation_dino_frame;

void init_main(void) {
  oam_init(oam_mem, MAX_SPRITES);

  memcpy16(pal_obj_mem + DINO_WALK_1, dino_walkPal, dino_walkPalLen / 2);
  memcpy32((u32 *)MEM_VRAM_OBJ, dino_walkTiles, dino_walkTilesLen / 4);

  memcpy16(pal_obj_mem + DINO_WALK_1 + CACTUS, cactus_1Pal, cactus_1PalLen / 2);
  memcpy32((u32 *)MEM_VRAM_OBJ + dino_walkTilesLen / 4, cactus_1Tiles,
           cactus_1TilesLen / 4);

  memcpy16(pal_obj_mem + DINO_WALK_1 + CACTUS + DACTYL, dactyl_glidePal,
           dactyl_glidePalLen / 2);
  memcpy32((u32 *)MEM_VRAM_OBJ + (dino_walkTilesLen / 4) +
               (cactus_1TilesLen / 4),
           dactyl_glideTiles, dactyl_glideTilesLen / 4);

  memcpy16(pal_bg_mem, bg_with_roadPal, bg_with_roadPalLen / 2);
  memcpy32(tile_mem[0], bg_with_roadTiles, bg_with_roadTilesLen / 4);
  memcpy16(se_mem[31], bg_with_roadMap, bg_with_roadMapLen / 2);

  REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0;
  REG_BG0CNT = BG_CBB(0) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  score = 0;
  game_state = PRE_GAME;
  frame_counter = 1;
  animation_dino_frame = 0;
  score_init();
  start_text();
}

void reset_game_state(void) {
  game_state = GAME;
  frame_counter = 1;
  animation_dino_frame = 0;
  score = 0;
}

void end_game(void) { game_state = POST_GAME; }
