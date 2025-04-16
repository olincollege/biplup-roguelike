#include "score.h"
#include "tonc.h"

int main() {
  irq_init(NULL);
  irq_add(II_VBLANK, NULL);
  REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
  score_init();
  while (1) {

    vid_vsync();
    score_update();
  }

  return 0;
}
