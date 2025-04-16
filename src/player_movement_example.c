#include "tonc.h"
#include "blob.h"
#include "player_movement.h"

int main(void)
{
    oam_init(oam_mem, MAX_SPRITES);

    memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
    memcpy32((u32 *)MEM_VRAM_OBJ, blobTiles, blobTilesLen / 4);

    Object blob = (Object){.attr = &oam_mem[0],
                           .x = 10,
                           .y = 100,
                           .x_velocity = 0,
                           .y_velocity = 0,
                           .x_acceleration = 0,
                           .y_acceleration = 1,
                           .jumping = false};

    blob.attr->attr0 = ATTR0_Y((int)blob.y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
    blob.attr->attr1 = ATTR1_X((int)blob.x) | ATTR1_SIZE_16x16;
    blob.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D;

    while (1)
    {
        vid_vsync();
        key_input(&blob);
        update_physics(&blob);
        if (blob.y >= 100)
        {
            blob.y = 100;
            set_jumping(&blob, false);
        }
        obj_set_pos(blob.attr, blob.x, blob.y);
        update_obj_x(&blob);
        update_obj_y(&blob);
        // key_input(&blob);

        // x = (x + 3) % SCREEN_WIDTH;
        // y = (y + 3) % SCREEN_HEIGHT;
        // blob_attrs->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
        // blob_attrs->attr1 = ATTR1_X(x) | ATTR1_SIZE_16x16;
        // blob_attrs->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);
    }
    return 0;
}
