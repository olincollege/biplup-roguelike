#include "example.h"
#include "tonc.h"
#include "assets/blob/blob.h"

typedef struct object_t {
    OBJ_ATTR* attr;
    int x;
    int y;
} Object;

void set_obj_x(Object* obj, int x);

void set_obj_x(Object* obj, int x) {
    obj->attr->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
    obj->x = x;
}

void set_obj_y(Object *obj, int y);

void set_obj_y(Object *obj, int y) {
    obj->attr->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
    obj->y = y;
}

void key_input(Object *obj) {
    key_poll();

    if (key_is_down(KEY_DOWN)) {
        obj->y = obj->y + 5;
        set_obj_y(obj, obj->y);
    }

    if (key_is_down(KEY_UP)) {
        obj->y  = obj->y - 5;
        set_obj_y(obj, obj->x);
    }
}

int main(void)
{
    // general idea - generate object way off the screen and as it moves over the screen,
    // check for collisions. when it goes way off the screen, despawn it.
    memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
    memcpy32((u32*)MEM_VRAM_OBJ, blobTiles, blobTilesLen / 4);

    Object blob = (Object) {
        .attr = &((OBJ_ATTR*) MEM_OAM)[0],
        .x = 239,
        .y = 0
    };

    set_obj_x(&blob, blob.x);
    set_obj_y(&blob, blob.y);

    blob.attr->attr2 = ATTR2_ID(10) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

    // OBJ_ATTR *blob_attrs = &((OBJ_ATTR*) MEM_OAM)[0];
    // int x = 0, y = 0;
    // blob_attrs->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
    // blob_attrs->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
    // blob_attrs->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

    REG_DISPCNT = DCNT_MODE3 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG2;

    while (1) {
        vid_vsync();
        blob.x = (blob.x - 3);
        if (blob.x <= 1) {
            blob.x = 239;
        }
        set_obj_x(&blob, blob.x);
        key_input(&blob);
 
        // x = (x + 3) % SCREEN_WIDTH;
        // y = (y + 3) % SCREEN_HEIGHT;
        // blob_attrs->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
        // blob_attrs->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
        // blob_attrs->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);
    }
    return 0;
}

// void init_main() {
    
// }

// void update_main() {

    
// }
