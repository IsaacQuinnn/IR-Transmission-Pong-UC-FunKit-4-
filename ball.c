#include "ball.h"
#include "ir_uart.h"

Ball ball_init(void)
{
    Ball new_ball;
    new_ball.current_col = BALL_COL_START;
    new_ball.row_mask = BALL_ROW_START;
    new_ball.direction = -1; // 1 = right, -1 = left
    return new_ball;
}

void ball_update(Ball* ball)
{
    ball->current_col += ball->direction;
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

