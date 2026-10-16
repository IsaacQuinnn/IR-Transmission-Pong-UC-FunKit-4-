/** @file   paddle.h
    @author Alex Shepherd and Isaac Quinn
    @date   14 October 2026
    @brief  Movement of the paddle support

    @defgroup Movement of the paddle module
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

/** Initialise 
    @return PADDLE_START    */
uint8_t paddle_init(void);


/** Updates the paddles position based on Navstick response 
    @param paddle_mask row mask for the paddle  */
void paddle_update(uint8_t* paddle_mask);


/** Return middle value 
    @return middle value of paddle  */
int get_middle(void);


/** Return upper value 
    @return upper value of paddle   */
int get_upper(void);


/** Return lower value 
    @return lower value of paddle   */
int get_lower(void);

#endif
