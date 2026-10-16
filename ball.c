/** @file   ball.c
    @author Alex Shepherd and Isaac Quinn
    @date   15 October 2026
    @brief  Controll a ball to move across the screen module
*/

#include "ball.h"
#include "ir_uart.h"
#include "paddle.h"

//Initialise Ball
Ball ball_init(void)
{
    Ball new_ball;
    new_ball.current_col = BALL_COL_START;
    new_ball.row_mask = BALL_ROW_START;
    new_ball.direction = -1;
    new_ball.diagonal = 0; // 1 = right, 0 = straight, -1 = left
    return new_ball;
}

/** When sending the ball to other controller, reverse the col bits to it is mirrored on other controlelr screen
    @param col pixel column.
    @return reverse of col.     */
uint8_t reverse_col(uint8_t col) 
{
    uint8_t result = 0;
    for (int i = 0; i < 7; i++) {
        result <<= 1;
        result |= (col & 1);
        col >>= 1;
    }

    return result;
}

/** Update the ball moving across the screen in different directions 
    @param ball the ball struct    */
void ball_update(Ball* ball)
{
    ball->current_col += ball->direction;

    
    if (ball->diagonal == -1) { //Right

        if (ball->row_mask == TOP_ROW) {
            ball->diagonal = 1;
            ball->row_mask <<= 1;

        } else {
            ball->row_mask >>= 1;
        }

    } else if (ball->diagonal == 1) { //Left

        if (ball->row_mask == BOTTOM_ROW) {
            ball->diagonal = -1;
            ball->row_mask >>= 1;

        } else { //Straight ahead
            ball->row_mask <<= 1;
        }
    }
}

/** Return the row mask pattern 
    @param ball the ball struct
    @param display_col the column the ball is in    */
uint8_t ball_get_pattern(Ball* ball, uint8_t display_col)
{
    if (display_col == ball->current_col && ball->current_col >= 0 && ball->current_col < 5) {
        return ball->row_mask;
    }
    return 0;
}

/** Send the ball to the other controller 
    @param ball the ball struct     */
void ball_transfer(Ball* ball)
{
    ir_uart_putc(reverse_col((ball->row_mask)));
    ball->current_col = -1;
}

/** Change directions of the ball when it touches the paddle 
    @param ball the ball struct
    @param paddle_mask row mask of the paddle   */
void hit_paddle(Ball* ball, uint8_t paddle_mask)
{
    ball->direction = -1;
    ball->current_col = 3;

    uint8_t upper = paddle_mask & -paddle_mask;

    uint8_t lower = 0;
    uint8_t temp = paddle_mask;
    while (temp) {
        lower = temp;
        temp &= temp - 1;
    }

    /* CHANGED: Implemented bitwise inversion to isolate the middle pixel without undefined functions */
    uint8_t middle = paddle_mask & ~(upper | lower);

    /* CHANGED: Swapped undefined helper names with the locally calculated pixel bitmasks */
    if (ball->row_mask == upper) {
        ball->diagonal = -1;

    } else if (ball->row_mask == middle) {
        ball->diagonal = 0;

    } else if (ball->row_mask == lower) {
        ball->diagonal = 1;
        
    }
}

/** Received the ball from the other controller and set accordingly 
    @param ball the ball struct
    @param row the row the ball need to go to   */
void ball_received(Ball* ball, uint8_t row)
{
    ball->row_mask = row;
    ball->current_col = 0;
    ball->direction = 1;
}

