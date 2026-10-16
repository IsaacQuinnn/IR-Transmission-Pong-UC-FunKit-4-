/** @file   paddle.h
    @author Alex Shepherd and Isaac Quinn
    @date   14 October 2026
    @brief  Movement of the paddle
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

//Initialise
uint8_t paddle_init(void);

//Updates the paddles position based on Navstick response
void paddle_update(uint8_t* paddle_mask);

//Return middle value
int get_middle(void);

//Return upper value
int get_upper(void);

//Return lower value
int get_lower(void);

#endif
