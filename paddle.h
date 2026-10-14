#ifndef PADDLE_H
#define PADDLE_H

#include "ledmat.h"
#include "system.h"
#include "pacer.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define NUM_COLS   5

#define PADDLE_START 0x1C   /* 0b0011100: 3 LEDs in the middle */
#define TOP_ROW 0x01   /* bit 0 = row 1 */
#define BOTTOM_ROW 0x40   /* bit 6 = row 7 */
#define PADDLE_COL 4

static void paddle_update (void);
static void display_update (void);

#endif