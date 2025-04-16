#pragma once

#include "tonc.h"
#include <stdbool.h>
#include <stdint.h>

typedef RECT direction;

typedef struct object_t {
    OBJ_ATTR* attr;
    int x;
    int y;
    bool is_active;
} Object;

static const int width_table[3][4] = {
    {8, 16, 32, 64},  // Square
    {16, 32, 32, 64}, // Wide
    {8, 8, 16, 32}    // Tall
};

static const int height_table[3][4] = {
    {8, 16, 32, 64}, // Square
    {8, 8, 16, 32},  // Wide
    {16, 32, 32, 64} // Tall
};

#define MAX_SPRITES 128