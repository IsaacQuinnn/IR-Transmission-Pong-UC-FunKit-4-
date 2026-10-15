#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "start.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

//Initialise
void start_init(void)
{
    system_init();
    tinygl_init (PACER_RATE);

    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    tinygl_text("PRESS JOYSTICK TO PLAY");

    pacer_init (PACER_RATE);
}

//Call tinygl function
void start_update(void)
{   
    pacer_wait();
    
    tinygl_update();
}