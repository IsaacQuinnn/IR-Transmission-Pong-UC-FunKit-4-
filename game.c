#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ledmat.h"
#include "ir_uart.h"
#include "ball.h"

/* PADDLE CODE */
#define PACER_RATE 500
#define NUM_COLS   5


#define PADDLE_START 0x1C   /* 0b0011100: 3 LEDs in the middle */
#define TOP_ROW      0x01   /* bit 0 = row 1 */
#define BOTTOM_ROW   0x40   /* bit 6 = row 7 */
#define PADDLE_COL 4

static uint8_t paddle = PADDLE_START;
static Ball my_ball;    

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

static void display_update (void)
{
    static uint8_t col = 0;

    // 1. Keep your original paddle logic (assigning the paddle mask to column 4)
    uint8_t paddle_pattern = (col == PADDLE_COL) ? paddle : 0;
    
    // 2. Add the ball pattern from your new ball.c module
    uint8_t ball_pattern = ball_get_pattern(&my_ball, col);

    // 3. Combine them using the OR (|) operator so they both light up on the matrix
    ledmat_display_column (paddle_pattern | ball_pattern, col);

    // 4. Keep your original column loop incrementor
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

    my_ball = ball_init(); 
    uint16_t ball_tick_counter = 0;

    /* GAME LOOPING*/
    while (1) {
        pacer_wait ();
        paddle_update ();
        
        // Move the ball every 250 ticks
        ball_tick_counter++;
        if (ball_tick_counter >= 250) {
            ball_tick_counter = 0;
            ball_update(&my_ball);
        }

        display_update ();
    }