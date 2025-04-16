#include "player_movement.h"
#include "types.h"
#include "tonc.h"

void update_obj_x(Object *obj)
{
    int x_val = obj->attr->attr1 & 0x01FF;
    obj->x = x_val;
}

void update_obj_y(Object *obj)
{
    int y_val = obj->attr->attr0 & 0x00FF;
    obj->y = y_val;
}

void set_obj_x_velocity(Object *obj, float x_velocity)
{
    obj->x_velocity = x_velocity;
}

void set_obj_y_velocity(Object *obj, float y_velocity)
{
    obj->y_velocity = y_velocity;
}

void set_obj_x_acceleration(Object *obj, float x_acceleration)
{
    obj->x_acceleration = x_acceleration;
}

void set_obj_y_acceleration(Object *obj, float y_acceleration)
{
    obj->y_acceleration = y_acceleration;
}

void set_jumping(Object *obj, bool jumping) { obj->jumping = jumping; }

void key_input(Object *obj)
{
    key_poll();
    if (!obj->jumping)
    {
        if (key_is_down(KEY_UP))
        {
            set_obj_y_velocity(obj, -10);
            set_jumping(obj, true);
        }
    }
}

void update_physics(Object *obj)
{
    set_obj_y_velocity(obj, obj->y_velocity += obj->y_acceleration);
    obj_set_pos(obj->attr, obj->x, obj->y + (obj->y_velocity + 0.5 * obj->y_acceleration));
    update_obj_x(obj);
    update_obj_y(obj);
}

void despawn(Object *obj)
{
    obj_hide(obj->attr);
    obj->is_active = false;
}
