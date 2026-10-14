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

#endif
