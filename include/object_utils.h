#pragma once

#include "tonc.h"
#include "types.h"
#include <stdbool.h>
#include <stdint.h>

#define OFFSCREEN_OFFSET 10
#define FLOOR_LEVEL 112
#define DACTYL_HEIGHT_DIFF -10
#define CLOUD_HEIGHT_DIFF -30

#define CACTUS_AMOUNT 1
#define DACTYL_AMOUNT 1
#define CLOUD_AMOUNT 0
#define OBSTACLE_AMOUNT CACTUS_AMOUNT + DACTYL_AMOUNT + CLOUD_AMOUNT

#define CACTUS_THRESHOLD 100
#define DACTYL_THRESHOLD 250
#define CLOUD_THRESHOLD 80

void object_constructor(Object *obj, int obj_counter, float x, float y,
                        bool is_active, int tile_number);

void obstacle_constructor(Object *obj, int obj_counter, float x, float y,
                          int tile_number);

void player_constructor(Object *obj, int obj_counter, float x, float y,
                        int tile_number);

void construct_obstacles(Object **obstacles);

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
 * @return An bool to indicate if the objects are colliding.
 */
bool check_obj_overlap(const Object *obj1, const Object *obj2);

/**
 * Determine if any part of an object is offscreen.
 *
 * Given a pointer to an object, use the position and size of the object to
 * determine if it is off of the screen in any way. Return a dir struct
 * describing which parts of the screen it is off from.
 *
 * @param obj1 A pointer to the  object.
 * @param dir An pointer to a dir struct with values of 1 wherever the object
 *            is offscreen.
 */
void check_obj_offscreen(const Object *obj, RECT *dir);

void despawn(Object *obj);
void spawn(Object *obj);
void set_obj_beginning(Object *obj);
void update_obstacle(Object *obj);
bool check_player_collision(Object *player, Object **obstacles);
void restart_objects(Object **obstacles);
