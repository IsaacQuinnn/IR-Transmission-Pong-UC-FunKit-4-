/** @file   ball.h
    @author Alex Shepherd & Isaac Quinn
    @date   14 October 2026
    @brief Routines for moving the ball
*/

#ifndef BALL_H
#define BALL_H

#include "ledmat.h"
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

#define BALL_COL_START 3
#define BALL_ROW_START 0x08 /*middle position on touching paddle*/
#define WALL_LEFT (0x00, 0x01, 0x01, 0x01, 0x01) /*bitmapping of wall location*/
#define WALL_RIGHT (0x00, 0x7F, 0x7F, 0x7F, 0x7F) /*bitmapping of wall location*/
#define COL_TO_SEND 0

/*make a thing that moves straight accross*/
typedef struct {
    int8_t current_col;
    uint8_t row_mask;
    int8_t direction;
    int8_t diagonal;
} Ball;

//Initialise
Ball ball_init(void);

//When sending the ball to other controller, reverse the col bits to it is mirrored on other controlelr screen
uint8_t reverse_col(uint8_t col);

//Update the ball moving across the screen in different directions
void ball_update(Ball* ball);

//Return the row mask pattern
uint8_t ball_get_pattern(Ball* ball, uint8_t display_col);

//Send the ball to the other controller
void ball_transfer(Ball* ball);

//Change directions of the ball when it touches the paddle
void hit_paddle(Ball* ball, uint8_t paddle_mask);

//received the ball from the other controller and set accordingly
void ball_received(Ball* ball, uint8_t row);

#endif