/** @file   paddle.c
    @author Alex Shepherd and Isaac Quinn
    @date   14 October 2026
    @brief  Movement of the paddle module
*/

#include "paddle.h"
#include "navswitch.h"

//defines whether movement is straight, upwards, or downwards
static int Lower;
static int Middle;
static int Upper;

/** Initialise 
    @return PADDLE_START    */
uint8_t paddle_init(void)
{
    Lower = 0x04;
    Middle = 0x08;
    Upper = 0x10;
    return PADDLE_START;
}

/** Updates the paddles position based on Navstick response 
    @param paddle_mask row mask for the paddle  */
void paddle_update(uint8_t* paddle_mask)
{
    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_NORTH) && !(*paddle_mask & TOP_ROW)) {
        *paddle_mask >>= 1;
        Lower >>=1;
        Middle >>= 1;
        Upper >>= 1;
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && !(*paddle_mask & BOTTOM_ROW)) {
        *paddle_mask <<= 1;
        Lower <<=1;
        Middle <<= 1;
        Upper <<= 1;
    }
}

/** Return middle value 
    @return middle value of paddle  */
int get_middle(void) {
    return Middle;
}

/** Return upper value 
    @return upper value of paddle   */
int get_upper(void) {
    return Upper;
}

/** Return lower value 
    @return lower value of paddle   */
int get_lower(void) {
    return Lower;
}

