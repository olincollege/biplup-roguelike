#include "text.h"

#include "tonc.h"

#include <stdio.h>

// Use LibTonc's built-in 8x8 font
extern const TFont sys8Font;

// Here are some important globals
extern int score;
extern u32 high_score;
char display_buffer[64];
char score_buffer[64];
char high_score_buffer[64];

void end_text(void) {
  erase_screen();
  snprintf(
      display_buffer, sizeof(display_buffer),
      "game over :(\n\n       final score: %d.\n\n     press up to restart",
      score);

  // Draw the text
  tte_set_pos(70, 30);
  tte_write(display_buffer);
}

void start_text(void) {
  erase_screen();
  snprintf(display_buffer, sizeof(display_buffer), "press up to start");

  // Draw the text
  tte_set_pos(50, 50);
  tte_write(display_buffer);
}

void text_init(void) {
  tte_init_se(0,                      // Background number (BG 0)
              BG_CBB(0) | BG_SBB(31), // BG control (for REG_BGxCNT)
              0,                      // Tile offset (special cattr)
              CLR_BLACK,              // Ink color
              14,                     // BitUnpack offset (on-pixel = 15)
              NULL,                   // Default font (sys8)
              NULL);
}

void score_update(void) {
  // Clear previous text (optional but useful in bitmap mode)
  erase_screen();

  // Update the score
  score++;

  // Construct the text
  snprintf(score_buffer, sizeof(score_buffer), "Score: %d\nHigh Score: %lu",
           score, high_score <= (u32)score ? (u32)score : high_score);

  // Draw the text
  tte_set_pos(0, 15);
  tte_write(score_buffer);
}

void erase_screen(void) { tte_erase_screen(); }
