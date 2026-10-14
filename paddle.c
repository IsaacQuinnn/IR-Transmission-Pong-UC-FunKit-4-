
#include "paddle.h"
#include "navswitch.h"


static uint8_t paddle = PADDLE_START;

static void paddle_update (void)
{
    navswitch_update ();

    if (navswitch_push_event_p (NAVSWITCH_NORTH) && !(paddle & TOP_ROW)) {
        paddle >>= 1;
    }
    if (navswitch_push_event_p (NAVSWITCH_SOUTH) && !(paddle & BOTTOM_ROW)) {
        paddle <<= 1;
    }
}