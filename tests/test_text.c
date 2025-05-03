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

int test_end_text() {
  score = 1;
  char test_buffer[64];
  end_text();
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
  char test_buffer[64];
  snprintf(test_buffer, sizeof(test_buffer), "press up to start");
  if (strcmp(test_buffer, display_buffer) == 0) {
    return 1;
  }
  return 0;
}

int test_score_text() {
  score = 1;
  unsigned long high_score = 73;
  char test_buffer[64];
  snprintf(test_buffer, sizeof(test_buffer), "Score: %d\nHigh Score: %lu",
           score, high_score <= (u32)score ? (u32)score : high_score);
  score_update();
  if (strcmp(test_buffer, score_buffer) == 0) {
    return 1;
  }
  return 0;
}

int test_score_update() {
  score = 1;
  score_update();
  if (score == 2) {
    return 1;
  }
  return 0;
}
