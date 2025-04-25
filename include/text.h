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

void end_text(void);

void start_text(void);

void score_init(void);

void score_update(void);

void erase_screen(void);
