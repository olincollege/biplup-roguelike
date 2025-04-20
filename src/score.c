#include "score.h"
#include "tonc_tte.h"
#include <stdio.h>
#include <tonc.h>

// Use LibTonc's built-in 8x8 font
extern const TFont sys8Font;

int score = 0;
char buffer[64];

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
  snprintf(buffer, sizeof(buffer), "Score: %d", score);

  // Clear previous text (optional but useful in bitmap mode)

  // Draw the updated score
  tte_set_pos(0, 15);
  tte_write(buffer); // Write the score

  score++;
}
