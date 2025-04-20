#include "press_to_start.h"
#include "tonc.h"

void display_init(void) {
  char buffer[64];
  tte_erase_screen();
  snprintf(buffer, sizeof(buffer), "press up to start");

  // Draw the text
  tte_set_pos(50, 50);
  tte_write(buffer);
}

void display_key_input(int *game_state) {
  key_poll();
  if (key_is_down(KEY_UP)) {
    despawn_startup(game_state);
  }
}

void despawn_startup(int *game_state) {
  tte_erase_screen();
  *game_state = 1;
}
