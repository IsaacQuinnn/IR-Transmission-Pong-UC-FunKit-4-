/** @file   ball.h
    @author Alex Shepherd & Isaac Quinn
    @date   15 October 2026
    @brief Ending / Play again screen for when a player Wins/Loses support

    @defgroup Ending / Play again screen for when a player Wins/Loses module
*/
#ifndef END_H
#define END_H

#include "ledmat.h"
#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "pacer.h"

/** Shows the Win/Lose face once Won/Lost 
    @param won 1 = player has one, 0 = player has lost
    @param time time in ms  */
void show_face(int won, uint32_t time);


//Displays "PLAY AGAIN?" on screen
void play_again(void);

#endif

