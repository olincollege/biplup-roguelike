#pragma once

#include <stdbool.h>

/**
 * Function: end_text
 *
 * Test to see that when end_text runs, the expected message is placed in the
 * display buffer.
 *
 * @return A 1 if the correct message is in the display buffer, otherwise a 0.
 */
int test_end_text();

/**
 * Function: start_text
 *
 * Test to see that when start_text runs, the expected message is placed in the
 * display buffer.
 *
 * @return A 1 if the correct message is in the display buffer, otherwise a 0.
 */
int test_start_text();

/**
 * Function: score_update
 *
 * Test to see that when score_update runs, the expected message is placed in
 * the display buffer.
 *
 * @return A 1 if the correct message is in the display buffer, otherwise a 0.
 */
int test_score_text();

/**
 * Function: score_update
 *
 * Test to see that when score_update runs, the score new score is 2.
 *
 * @return A 1 if the score is 2, otherwise a 0.
 */
int test_score_update();
