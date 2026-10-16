/** @file   start.c
    @author Alex Shepherd and Isaac Quinn
    @date   15 October 2026
    @brief  Displays "PRESS TO PLAY" when the microcontroller turns on module
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "start.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20

//Initialise
void start_init(void)
{
    system_init();
    tinygl_init (PACER_RATE);

    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);

    tinygl_text("PRESS TO PLAY");

    pacer_init (PACER_RATE);
}

//Call tinygl function
void start_update(void)
{   
    pacer_wait();
    
    tinygl_update();
}