#include "test_text.h"

#include "text.h"
#include "tonc.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

extern char display_buffer[64];
extern char score_buffer[64];
extern int score;
extern u32 high_score;

int test_end_text() {
  score = 1;
  char test_buffer[64];
  end_text();
  tte_erase_screen();
  snprintf(test_buffer, sizeof(test_buffer),
           "game over :(\nfinal score: %d.\npress up to restart", score);
  if (strcmp(test_buffer, display_buffer) == 0) {
    return 1;
  }
  return 0;
}

int test_start_text() {
  score = 1;
  start_text();
  tte_erase_screen();
  char test_buffer[64];
  snprintf(test_buffer, sizeof(test_buffer), "press up to start");
  if (strcmp(test_buffer, display_buffer) == 0) {
    return 1;
  }
  return 0;
}

int test_score_text() {
  score = 1;
  high_score = 73;
  char test_buffer[64];
  score_update();
  snprintf(test_buffer, sizeof(test_buffer), "Score: %d\nHigh Score: %lu",
           score, high_score <= (u32)score ? (u32)score : high_score);
  tte_erase_screen();
  if (strcmp(test_buffer, score_buffer) == 0) {
    return 1;
  }
  return 0;
}

int test_score_update() {
  score = 1;
  score_update();
  tte_erase_screen();
  if (score == 2) {
    return 1;
  }
  return 0;
}
