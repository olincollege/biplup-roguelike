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
u32 high_score;
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
  high_score = retrieve_high_score();
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
u32 retrieve_high_score(void) {
  int total_size = 4;
  vu8 byte_parts_of_data[] = {0, 0, 0, 0};
  for (int i = 0; i < total_size; i++) {
    byte_parts_of_data[i] = ((vu8 *)MEM_SRAM)[i];
  }

  u32 high_score_num = 0;
  vu32 building_high_score = 0;

  for (int i = 0; i < total_size; i++) {
    building_high_score |= byte_parts_of_data[i]
                           << (((total_size - 1) - i) * 8);
  }

  high_score_num = (u32)building_high_score;

  return 0; // returning 0 resets the game high score across resets
}

void save_high_score(void) {
  vu32 high_score_num = (vu32)high_score;
  vu8 byte_parts_of_data[] = {0, 0, 0, 0};
  int total_size = 4;

  for (int i = 0; i < total_size; i++) {
    byte_parts_of_data[i] = high_score_num >> (((total_size - 1) - i) * 8);
  }

  for (int i = 0; i < total_size; i++) {
    ((vu8 *)MEM_SRAM)[i] = byte_parts_of_data[i];
  }
}
