#ifndef BALL_H
#define BALL_H

#include "ledmat.h"
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

#define BALL_COL_START 3
#define BALL_ROW_START 0x08 /*middle position on touching paddle*/
#define WALL_LEFT 0x00, 0x01, 0x01, 0x01, 0x01 /*bitmapping of wall location*/
#define WALL_RIGHt 0x00, 0x7F, 0x7F, 0x7F, 0x7F /*bitmapping of wall location*/
#define COL_TO_SEND 0

/*make a thing that moves straight accross*/
typedef struct {
    int8_t current_col;
    uint8_t row_mask;
    int8_t direction;
} Ball;

Ball ball_init(void);
void ball_update(Ball* ball);
uint8_t ball_get_pattern(Ball* ball, uint8_t display_col);
void ball_transfer(Ball* ball);

#endif