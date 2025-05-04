#pragma once

#include <stdbool.h>

/**
 * Tests to see if toggling cheat mode off sets all sprites to the default
 * sprite.
 *
 * In this test, both the player and obstacle have their default sprite set to
 * DINO. Therefore, their sprite id's should remain as DINO.
 *
 * @return 1 if both the player and obstacle sprite IDs are the default, 0
 * otherwise.
 */
int test_toggle_cheat_state_off();

/**
 * Tests to see if toggling cheat mode on sets all sprites to the cheat mode
 * sprite.
 *
 * In this test, both the player and obstacle have their default sprite set to
 * DINO. Therefore, their sprite id's should become BIPLUP.
 *
 * @return 1 if both the player and obstacle sprite IDs are the the cheat mode
 * sprite, 0 otherwise.
 */
int test_toggle_cheat_state_on();
