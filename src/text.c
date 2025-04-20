#include "text.h"
#include "tonc.h"

void restart_init(void) {
  char buffer[64];
  tte_erase_screen();
  snprintf(buffer, sizeof(buffer), "game over :( press up to restart");

  // Draw the text
  tte_set_pos(50, 50);
  tte_write(buffer);
}

void display_init(void) {
  char buffer[64];
  tte_erase_screen();
  snprintf(buffer, sizeof(buffer), "press up to start");

  // Draw the text
  tte_set_pos(50, 50);
  tte_write(buffer);
}

void start_game(int *game_state, int *score) {
  tte_erase_screen();
  *game_state = 1;
  *score = 0;
}
