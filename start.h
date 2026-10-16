/** @file   start.h
    @author Alex Shepherd & Isaac Quinn
    @date   15 October 2026
    @brief Displays "PRESS TO PLAY" when the microcontroller turns on support

    @defgroup Displays "PRESS TO PLAY" when the microcontroller turns on module

*/
#ifndef START_H
#define START_H

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"

//Initialise
void start_init(void);

//Call tinygl function
void start_update(void);


#endif

