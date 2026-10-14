#include "paddle.h"
#include "navswitch.h"

//defines whether movement is straight, upwards, or downwards
static int Lower;
static int Middle;
static int Upper;

uint8_t paddle_init(void)
{
    Lower = 2;
    Middle = 3;
    Upper = 4;
    return PADDLE_START;
}

void paddle_update(uint8_t* paddle_mask)
{
    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_NORTH) && !(*paddle_mask & TOP_ROW)) {
        *paddle_mask >>= 1;
        Lower -=1;
        Middle -= 1;
        Upper -= 1;
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && !(*paddle_mask & BOTTOM_ROW)) {
        *paddle_mask <<= 1;
        Lower +=1;
        Middle += 1;
        Upper += 1;
    }
}

int get_middle(void) {
    return Middle;
}

int get_upper(void) {
    return Upper;
}

int get_lower(void) {
    return Lower;
}

