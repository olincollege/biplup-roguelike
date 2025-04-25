#include "text.h"
#include "tonc.h"
#include <stdio.h>

// Use LibTonc's built-in 8x8 font
extern const TFont sys8Font;

// here are some important globals
extern int score;
char display_buffer[BUFFER_SIZE];
char score_buffer[BUFFER_SIZE];

void end_text(void) {
  tte_erase_screen();
  snprintf(display_buffer, sizeof(display_buffer),
           "game over :( final score: %d. press up to restart", score);

  // Draw the text
  tte_set_pos(CENTRAL_TEXT_X, CENTRAL_TEXT_Y);
  tte_write(display_buffer);
}

void start_text(void) {
  tte_erase_screen();
  snprintf(display_buffer, sizeof(display_buffer), "press up to start");

  // Draw the text
  tte_set_pos(CENTRAL_TEXT_X, CENTRAL_TEXT_Y);
  tte_write(display_buffer);
}

void score_init(void) {
  tte_init_se(0,                      // Background number (BG 0)
              BG_CBB(0) | BG_SBB(31), // BG control (for REG_BGxCNT)
              0,                      // Tile offset (special cattr)
              CLR_BLACK,              // Ink color
              14,                     // BitUnpack offset (on-pixel = 15)
              NULL,                   // Default font (sys8)
              NULL);
}

void score_update(void) {
  tte_erase_screen();
  snprintf(score_buffer, sizeof(score_buffer), "Score: %d", score);

  // Clear previous text (optional but useful in bitmap mode)

  // Draw the updated score
  tte_set_pos(SCORE_TEXT_X, SCORE_TEXT_Y);
  tte_write(score_buffer); // Write the score

  score++;
}

void erase_screen(void) { tte_erase_screen(); }
