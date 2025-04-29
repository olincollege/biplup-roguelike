#include "system_utils.h"
#include "text.h"
#include "tonc.h"
#include "types.h"

#include "assets/aero_fly_32.h"
#include "assets/bg_with_road.h"
#include "assets/biplup_walk_32.h"
#include "assets/blob.h"
#include "assets/cactus_1_32.h"
#include "assets/cloud_32.h"
#include "assets/dactyl_glide_32.h"
#include "assets/dino_walk_32.h"
#include "assets/sudowoodo_32.h"
int score;
Game_State game_state;
RECT offscreen;
int frame_counter;
int animation_frame;

void init_main(void) {
  oam_init(oam_mem, MAX_SPRITES);

  memcpy16(pal_obj_mem + DINO, dino_walk_32Pal, dino_walk_32PalLen / 2);
  memcpy32(*tile_mem_obj, dino_walk_32Tiles, dino_walk_32TilesLen / 4);

  memcpy16(pal_obj_mem + CACTUS, cactus_1_32Pal, cactus_1_32PalLen / 2);
  memcpy32(*tile_mem_obj + CACTUS, cactus_1_32Tiles, cactus_1_32TilesLen / 4);

  memcpy16(pal_obj_mem + DACTYL, dactyl_glide_32Pal, dactyl_glide_32PalLen / 2);
  memcpy32(*tile_mem_obj + DACTYL, dactyl_glide_32Tiles,
           dactyl_glide_32TilesLen / 4);

  memcpy16(pal_obj_mem + CLOUD, cloud_32Pal, cloud_32PalLen / 2);
  memcpy32(*tile_mem_obj + CLOUD, cloud_32Tiles, cloud_32TilesLen / 4);

  memcpy16(pal_obj_mem + BIPLUP, biplup_walk_32Pal, biplup_walk_32PalLen / 2);
  memcpy32(*tile_mem_obj + BIPLUP, biplup_walk_32Tiles,
           biplup_walk_32TilesLen / 4);

  memcpy16(pal_obj_mem + SUDOWOODO, sudowoodo_32Pal, sudowoodo_32PalLen / 2);
  memcpy32(*tile_mem_obj + SUDOWOODO, sudowoodo_32Tiles,
           sudowoodo_32TilesLen / 4);

  memcpy16(pal_obj_mem + AERODACTYL, aero_fly_32Pal, aero_fly_32PalLen / 2);
  memcpy32(*tile_mem_obj + AERODACTYL, aero_fly_32Tiles,
           aero_fly_32TilesLen / 4);

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
  animation_frame = 0;
  score_init();
  start_text();
}

void reset_game_state(void) {
  game_state = GAME;
  frame_counter = 1;
  animation_frame = 0;
  score = 0;
}

void end_game(void) { game_state = POST_GAME; }
