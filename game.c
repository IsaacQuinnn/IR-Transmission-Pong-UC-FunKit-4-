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
#define TOP_ROW 0x01   /* bit 0 = row 1 */
#define BOTTOM_ROW 0x40   /* bit 6 = row 7 */
#define PADDLE_COL 4
#define BALL_SPEED_DIVIDER 125

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

    uint8_t paddle_pattern = (col == PADDLE_COL) ? paddle : 0;
    
    uint8_t ball_pattern = ball_get_pattern(&my_ball, col);
    ledmat_display_column (paddle_pattern | ball_pattern, col);
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

    
    /*ball movement - straight line FOR NOW*/
    my_ball = ball_init(); 
    uint16_t ball_tick_counter = 0;
    int ball_active = (player == 1) ? 1 : 0;
    
    if (!ball_active) {
        my_ball.current_col = -1; 
    }

    while (1) {

        while (player == 0) {
            navswitch_update();

            if (ir_uart_read_ready_p() && ir_uart_getc() == 'S') {
                player = 2;
            } else if (navswitch_push_event_p(NAVSWITCH_PUSH) ) {
                ir_uart_putc('S');
                player = 1;
            }
        }

        pacer_wait ();
        paddle_update ();
        
        if (ir_uart_read_ready_p() && ir_uart_getc() == 'R') {
            player = 0
        }

        if (!ball_active && ir_uart_read_ready_p()) {
            uint8_t received_row = ir_uart_getc();
            my_ball.row_mask = received_row;
            ball_active = 1;
            my_ball.current_col = 0;
            my_ball.direction = 1;
        }

        if (ball_active) {
            ball_tick_counter++;
            if (ball_tick_counter >= BALL_SPEED_DIVIDER) {
                ball_tick_counter = 0;
                ball_update(&my_ball);
                
                if (my_ball.current_col == 4) {
                    if (my_ball.row_mask & paddle) {
                        my_ball.direction = -1;
                        my_ball.current_col = 3;
                    } else {
                        my_ball.direction = 1; 
                    }
                }
                
                if (my_ball.current_col < 0) {
                    ir_uart_putc(my_ball.row_mask);
                    ball_active = 0;
                    my_ball.current_col = -1;
                    player = 0;
                    ir_uart_putc('R');
                }
            }
        }



        display_update ();
    }
}