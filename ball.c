#include "ball.h"

/**
 * Initializes the ball using your exact starting rules.
 */
Ball ball_init(void)
{
    Ball new_ball;
    new_ball.current_col = BALL_COL_START;
    new_ball.row_mask = BALL_ROW_START;
    new_ball.direction = 1; // Start by moving straight ahead (rightwards)
    return new_ball;
}

/**
 * Moves the ball straight across the columns.
 */
void ball_update(Ball* ball)
{
    // Update the column index by adding the direction step
    ball->current_col += ball->direction;

    // Simple bounds checking to make it bounce off the screen edges
    if (ball->current_col >= 4) {
        ball->direction = -1; // Bounce back left
    }
    if (ball->current_col <= 0) {
        ball->direction = 1;  // Bounce back right
    }
}

/**
 * Checks if the display multiplexing loop is looking at the ball's column.
 * Returns the row bitmask if true, or 0 if false.
 */
uint8_t ball_get_pattern(Ball* ball, uint8_t display_col)
{
    if (display_col == ball->current_col) {
        return ball->row_mask;
    }
    return 0;
}
