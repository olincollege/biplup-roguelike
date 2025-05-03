/**
 * text.h
 *
 * Describe functions and constants that assist in drawing screen text.
 *
 * The constants in this file describe where text is drawn, while the functions
 * generally use buffers to write and erase text directly to the screen.
 */

#pragma once

#define BUFFER_SIZE 64    // size of a standard text buffer
#define SCORE_TEXT_X 0    // x position of score text
#define SCORE_TEXT_Y 15   // y position of score text
#define CENTRAL_TEXT_X 50 // x position of start and end text
#define CENTRAL_TEXT_Y 50 // y position of start and end text

/**
 * Display endgame text when the player loses.
 *
 * Erase the screen. Then write text to the tte buffer that displays the
 * player's ending score and prompt them to restart.
 */
void end_text(void);

/**
 * Display pregame text when the game starts.
 *
 * Erase the screen. Then write text to the tte buffer that prompts the player
 * to start playing.
 */
void start_text(void);

/**
 * Initialize default displays for all in-game text.
 */
void text_init(void);

/**
 * Update and display the player's current score.
 *
 * Erase the screen. Then update and display the current score and high score.
 */
void score_update(void);

/**
 * Erase the screen.
 */
void erase_screen(void);
