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
