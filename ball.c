#include "ball.h"

Ball ball_init(void)
{
    Ball new_ball;
    new_ball.current_col = BALL_COL_START;
    new_ball.row_mask = BALL_ROW_START;
    new_ball.direction = 1; // 1 = right, -1 = left
    return new_ball;
}

void ball_update(Ball* ball)
{
    // Simply move the ball in its current direction
    ball->current_col += ball->direction;
    
    // Do NOT automatically wrap or bounce here anymore!
    // The main game loop will handle what happens when current_col goes out of bounds.
}

uint8_t ball_get_pattern(Ball* ball, uint8_t display_col)
{
    // Only display if the column index is valid (0 to 4)
    if (display_col == ball->current_col && ball->current_col >= 0 && ball->current_col < 5) {
        return ball->row_mask;
    }
    return 0;
}
