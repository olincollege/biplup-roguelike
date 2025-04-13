#pragma once

#include "tonc.h"

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

/**
 * Determine if there is overlap between two objects on the screen.
 *
 * Given two object's attributes, determine whether or not the sprites are
 * colliding based on their (x,y) coordinates and sprite dimensions. Writing a
 * 1 to the result pointer indicates a collision, whereas a 0 indicates that
 * the objects are not colliding. If the result is a negative value, an error
 * has occurred.
 *
 * @param obj1 A pointer to the first object.
 * @param obj2 A pointer to the second object.
 * @return An int to indicate if the objects are colliding.
 */
int check_obj_overlap(const OBJ_ATTR *obj1, const OBJ_ATTR *obj2);

/**
 * Determine if any part of an object is offscreen.
 *
 * Given a pointer to an object, use the position and size of the object to
 * determine if it is off of the screen in any way. Return a dir struct
 * describing which parts of the screen it is off from.
 *
 * @param obj1 A pointer to the  object.
 * @return An pointer to a dir struct with values of 1 wherever the object
 *         is offscreen.
 */
dir *check_obj_offscreen(const OBJ_ATTR *obj1);
