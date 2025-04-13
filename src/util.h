#pragma once

typedef struct dir {
  int up;
  int down;
  int left;
  int right;
} dir;

/**
 * Initialize a new dir struct in the heap.
 *
 * Initialize a new dir struct in the heap. Set all values to zero by default.
 * If different values are desired, they can be set by the caller. The caller
 * is also responsible for freeing the allocated memory.
 *
 * @return A pointer to the new dir struct.
 */
void make_dir();

/**
 * Free a dir object.AFF_DST
 *
 * Given a pointer to a dir struct currently in the heap, free its associated
 * memory space.
 *
 * @param to_free The dir struct to free.
 */
void free_dir(dir *to_free);
