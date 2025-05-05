#include "tonc.h"

#include "test_input.h"
#include "test_kinematics.h"
#include "test_object_utils.h"
#include "test_system_utils.h"
#include "test_text.h"

#include <stdbool.h>
#include <stdio.h>

int main(void) {
  // clear OAM (Object Attribute Memory) for test use
  oam_init(oam_mem, 64);

  irq_init(NULL);
  irq_add(II_VBLANK, NULL);

  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

  char test_buffer[128];

  // set modes for text
  tte_init_se(0, BG_CBB(0) | BG_SBB(31), 0, CLR_BLACK, 14, NULL, NULL);

  snprintf(test_buffer, sizeof(test_buffer),
           "system_utils.c:\n\n%d%d%d\n\ntext.c:\n\n%d%d%d%d\n\ninput.c:\n\n%d"
           "%d%d%d%d%d%d%d%d\n\nobject_utils.c:\n\n%d%d%d%d%d%d%d%d%d%d%d%d%d%d"
           "%d%d%d%d%d%d%d%d%d%d%d%d%d\n\nkinematics.c:\n\n%d%d%d%d%d%d%d",
           SYSTEM_UTILS_TESTS, TEXT_TESTS, INPUT_TESTS, OBJECT_UTILS_TESTS,
           KINEMATICS_TESTS);

  // clear OAM for display use
  oam_init(oam_mem, 64);

  while (true) {
    tte_set_pos(5, 7);
    tte_write(test_buffer);
  }
}
