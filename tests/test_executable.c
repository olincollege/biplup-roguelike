#include "tonc.h"

#include "test_input.h"
#include "test_kinematics.h"
#include "test_object_utils.h"
#include "test_system_utils.h"
#include "test_text.h"

#include <stdio.h>

#define MAX_SPRITES 128

int main(void) {
  oam_init(oam_mem, MAX_SPRITES);

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

  char test_buffer[128];

  tte_init_se(0,                      // Background number (BG 0)
              BG_CBB(0) | BG_SBB(31), // BG control (for REG_BGxCNT)
              0,                      // Tile offset (special cattr)
              CLR_BLACK,              // Ink color
              14,                     // BitUnpack offset (on-pixel = 15)
              NULL,                   // Default font (sys8)
              NULL);

  snprintf(test_buffer, sizeof(test_buffer),
           "system_utils.c:\n\n%d%d%d\n\ntext.c:\n\n%d%d%d%d\n\ninput.c:\n\n%d"
           "%d%d%d%d%d%d%d%d\n\nobject_utils.c:\n\n%d%d%d%d%d%d%d%d%d%d%d%d%d%d"
           "%d%d%d%d%d%d%d%d%d%d%d%d%d\n\nkinematics.c:\n\n%d%d%d%d%d%d%d",
           SYSTEM_UTILS_TESTS, TEXT_TESTS, INPUT_TESTS, OBJECT_UTILS_TESTS,
           KINEMATICS_TESTS);

  oam_init(oam_mem, MAX_SPRITES);

  while (1) {
    // tte_erase_screen();
    tte_set_pos(5, 7);
    tte_write(test_buffer);
  }
}
