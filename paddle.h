/** @file   ball.h
    @author Alex Shepherd & Isaac Quinn
    @date   14 October 2026

    @brief Routines for moving the paddle
*/

#ifndef PADDLE_H
#define PADDLE_H

#include "ledmat.h"
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

#define PADDLE_START 0x1C
#define TOP_ROW 0x01
#define BOTTOM_ROW 0x40
#define PADDLE_COL 4


uint8_t paddle_init(void);
void paddle_update(uint8_t* paddle_mask);
int get_middle(void);
int get_upper(void);
int get_lower(void);

#endif
