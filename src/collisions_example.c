#include "tonc.h"

#include "types.h"
#include "move.h"
#include "player_movement.h"

#include "blob.h"

int main(void)
{

    oam_init(oam_mem, MAX_SPRITES);

    memcpy16(pal_obj_mem, blobPal, blobPalLen / 2);
    memcpy32((u32 *)MEM_VRAM_OBJ, blobTiles, blobTilesLen / 4);

    Object blob_1 = (Object){
        .attr = &oam_mem[0],
        .x = 200,
        .y = 40,
        .is_active = true};

    blob_1.attr->attr0 = ATTR0_Y((int)blob_1.y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
    blob_1.attr->attr1 = ATTR1_X((int)blob_1.x) | ATTR1_SIZE_16x16;
    blob_1.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(0) | ATTR2_PALBANK(0);

    Object blob_2 = (Object){
        .attr = &oam_mem[1],
        .x = 40,
        .y = 40,
        .is_active = true};

    // set_obj_x(&blob_2, blob_2.x);
    // set_obj_y(&blob_2, blob_2.y);

    blob_2.attr->attr0 = ATTR0_Y((int)blob_2.y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_MODE(ATTR0_REG);
    blob_2.attr->attr1 = ATTR1_X((int)blob_2.x) | ATTR1_SIZE_16x16;
    blob_2.attr->attr2 = ATTR2_ID(0) | ATTR2_PRIO(1) | ATTR2_PALBANK(0);

    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D;

    direction offscreen;
    int direction_ = 1;

    update_obj_x(&blob_1);
    update_obj_y(&blob_1);

    update_obj_x(&blob_2);
    update_obj_y(&blob_2);
    while (1)
    {
        vid_vsync();
        if (blob_1.is_active)
        {
            blob_1.x = (blob_1.x + direction_);
            obj_set_pos(blob_1.attr, (int)blob_1.x, (int)blob_1.y);
            update_obj_x(&blob_1);
            update_obj_y(&blob_1);
        }

        obj_set_pos(blob_2.attr, (int)blob_2.x, (int)blob_2.y);

        update_obj_x(&blob_2);
        update_obj_y(&blob_2);
        // int y = 40;
        // blob_1.attr->attr0 = ATTR0_Y(y) | ATTR0_SQUARE | ATTR0_4BPP | ATTR0_REG;
        // blob_1.y = y;

        if (check_obj_overlap(&blob_1, &blob_2))
        {
            direction_ = -direction_;
        }

        check_obj_offscreen(&blob_1, &offscreen);
        if (offscreen.left == 1 || offscreen.right == 1)
        {
            // obj_hide(blob_1.attr);
            // blob_1.is_active = false;
            direction_ = -direction_;
        }
    }
    return 0;
}
