#include "test_object_utils.c"
#include "tonc.h"
#include <stdio.h>

int main(void) {
  oam_init(oam_mem, 128);

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  int total_tests = 1;

  int passed_tests = test_right_offscreen();
  int failed_tests = total_tests - passed_tests;

  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
  // REG_BG0CNT = BG_CBB(0) | BG_SBB(31);
  char buffer[64];

  snprintf(buffer, sizeof(buffer), "Passed Tests: %d\n\n      Failed Tests: %d",
           passed_tests, failed_tests);

  tte_init_se(0,                      // Background number (BG 0)
              BG_CBB(0) | BG_SBB(31), // BG control (for REG_BGxCNT)
              0,                      // Tile offset (special cattr)
              CLR_WHITE,              // Ink color
              14,                     // BitUnpack offset (on-pixel = 15)
              NULL,                   // Default font (sys8)
              NULL);
  while (1) {
    // tte_erase_screen();
    tte_set_pos(50, 50);
    tte_write(buffer);
  }
}