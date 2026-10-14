#include "ball.h"
#include "ir_uart.h"
#include "paddle.h"

Ball ball_init(void)
{
    Ball new_ball;
    new_ball.current_col = BALL_COL_START;
    new_ball.row_mask = BALL_ROW_START;
    new_ball.direction = -1;
    new_ball.diagonal = 0; // 1 = right, 0 = straight, -1 = left
    return new_ball;
}

void ball_update(Ball* ball)
{
    ball->current_col += ball->direction;

    if (ball->diagonal == -1) {
        ball->row_mask >>= 1;

        if (ball->row_mask == TOP_ROW) {
            ball->diagonal = 1;
        }

    } else if (ball->diagonal) {
        ball->row_mask <<=1;

        if (ball->row_mask == BOTTOM_ROW) {
            ball->diagonal = -1;
        }
    }


}

uint8_t ball_get_pattern(Ball* ball, uint8_t display_col)
{
    if (display_col == ball->current_col && ball->current_col >= 0 && ball->current_col < 5) {
        return ball->row_mask;
    }
    return 0;
}

void ball_transfer(Ball* ball)
{
    ir_uart_putc(ball->row_mask);
    ball->current_col = -1;
}

void hit_paddle(Ball* ball)
{
    ball->direction = -1;
    ball->current_col = 3;

    // diagonal movement
    if (ball->row_mask == get_lower()) { //hits the left side of the paddle
        ball->diagonal = -1;

    } else if (ball->row_mask == get_middle()) { // hits the middle of the paddle
        ball->diagonal = 0;

    } else if (ball->row_mask == get_upper()) {//hits the right side of the paddle
        ball->diagonal = 1;
    }
}

void ball_received(Ball* ball, uint8_t row)
{
    ball->row_mask = row;
    ball->current_col = 0;
    ball->direction = 1;
}

