#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ledmat.h"
#include "ir_uart.h"

/* PADDLE CODE */
#define PACER_RATE 500
#define NUM_COLS   5


#define PADDLE_START 0x1C   /* 0b0011100: 3 LEDs in the middle */
#define TOP_ROW      0x01   /* bit 0 = row 0 */
#define BOTTOM_ROW   0x40   /* bit 6 = row 6 */

static uint8_t paddle = PADDLE_START;

static void paddle_update (void)
{
    navswitch_update ();

    if (navswitch_push_event_p (NAVSWITCH_NORTH) && !(paddle & TOP_ROW)) {
        paddle >>= 1;
    }
    if (navswitch_push_event_p (NAVSWITCH_SOUTH) && !(paddle & BOTTOM_ROW)) {
        paddle <<= 1;
    }
}

static void display_update (int PADDLE_COL)
{
    static uint8_t col = 0;

    ledmat_display_column (col == PADDLE_COL ? paddle : 0, col);

    col = (col + 1) % NUM_COLS;
}

int main (void)
{
    system_init ();
    ledmat_init ();
    navswitch_init ();
    ir_uart_init ();
    pacer_init (PACER_RATE);

    /*PLAYER SELECTION - First to send*/
    int player = 0;

    while (player == 0) {
        navswitch_update();

        if (ir_uart_read_ready_p() && ir_uart_getc() == 'S') {
            player = 2;
        } else if (navswitch_push_event_p(NAVSWITCH_PUSH) ) {
            ir_uart_putc('S');
            player = 1;
        }
    }

    int PADDLE_COL = (player = 1) ? 0 : 4;

    /* GAME LOOPING*/
    while (1) {
        pacer_wait ();
        paddle_update ();
        display_update (PADDLE_COL);
    }
}