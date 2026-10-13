#ifndef BALL_H
#define BALL_H

#include "ledmat.h"
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

#define BALL_COL_START 1
#define BALL_ROW_START 0x08 /*middle position on touching paddle*/
#define WALL_LEFT 0x00, 0x01, 0x01, 0x01, 0x01 /*bitmapping of wall location*/
#define WALL_RIGHt 0x00, 0x7F, 0x7F, 0x7F, 0x7F /*bitmapping of wall location*/
#define COL_TO_SEND 4

/*make a thing that moves straight accross*/
typedef struct {
    uint8_t current_col;    // Current column index (0 to 4)
    uint8_t row_mask;       // The row bitmask (0x08)
    int8_t direction;       // 1 for moving right, -1 for moving left
} Ball;

Ball ball_init(void);
void ball_update(Ball* ball);
uint8_t ball_get_pattern(Ball* ball, uint8_t display_col);

#endif