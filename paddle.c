
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

static void display_update (void)
{
    static uint8_t col = 0;

    uint8_t paddle_pattern = (col == PADDLE_COL) ? paddle : 0;
    
    uint8_t ball_pattern = ball_get_pattern(&my_ball, col);
    ledmat_display_column (paddle_pattern | ball_pattern, col);
    col = (col + 1) % NUM_COLS;
}
