#include "paddle.h"
#include "navswitch.h"

uint8_t paddle_init(void)
{
    return PADDLE_START;
}

void paddle_update(uint8_t* paddle_mask)
{
    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_NORTH) && !(*paddle_mask & TOP_ROW)) {
        *paddle_mask >>= 1;
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && !(*paddle_mask & BOTTOM_ROW)) {
        *paddle_mask <<= 1;
    }
}
