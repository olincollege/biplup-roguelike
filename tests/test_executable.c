#include "test_input.h"
#include "test_object_utils.h"
#include "test_text.h"
#include "tonc.h"
#include <stdio.h>

int main(void) {
  oam_init(oam_mem, 128);

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
  // REG_BG0CNT = BG_CBB(0) | BG_SBB(31);

  tte_init_se(0,                      // Background number (BG 0)
              BG_CBB(0) | BG_SBB(31), // BG control (for REG_BGxCNT)
              0,                      // Tile offset (special cattr)
              CLR_WHITE,              // Ink color
              14,                     // BitUnpack offset (on-pixel = 15)
              NULL,                   // Default font (sys8)
              NULL);

  int total_tests = 13;

  int passed_tests =
      test_pregame_reset_score() + test_pregame_reset_frame() +
      test_pregame_to_game() + test_jump_state() + test_postgame_reset_score() +
      test_postgame_reset_frame() + test_postgame_to_game() +
      test_postgame_obst_reset() + test_cheat_mode_toggle() + test_end_text() +
      test_start_text() + test_score_text() + test_score_update();
  int failed_tests = total_tests - passed_tests;

  char test_buffer[64];

  snprintf(test_buffer, sizeof(test_buffer),
           "Passed Tests: %d\n\n      Failed Tests: %d", passed_tests,
           failed_tests);

  while (1) {
    // tte_erase_screen();
    tte_set_pos(50, 50);
    tte_write(test_buffer);
  }
}
