#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ledmat.h"
#include "ir_uart.h"
#include "ball.h"
#include "paddle.h"
#include "start.h"
#include "end.h"

/* PADDLE & BALL INITIALISATION */
#define PACER_RATE 500
#define NUM_COLS   5
#define BALL_SPEED_DIVIDER 125
#define PADDLE_SPEED_DIVIDER 20

static uint8_t paddle = PADDLE_START;
static Ball my_ball; 
static int ball_active = 0;   
static int player;

/*when called, game is reset & p1/p2 can be chosen again*/
static void reset_game(void)
{
    player = 0;
    ball_active = 0;
}

static void display_update_game (void)
{
    static uint8_t col = 0;

    uint8_t paddle_pattern = (col == PADDLE_COL) ? paddle : 0;
    /*decides the pattern for the ball column*/
    uint8_t ball_pattern = ball_get_pattern(&my_ball, col);
    ledmat_display_column (paddle_pattern | ball_pattern, col);
    col = (col + 1) % NUM_COLS;
}


int main (void)
{
    //Initialise
    system_init ();
    start_init ();
    ledmat_init ();
    navswitch_init ();
    ir_uart_init (); 
    pacer_init (PACER_RATE);
    

    player = 0;
    uint16_t ball_tick_counter = 0;


    while (1) {
         /*PLAYER SELECTION - First to send*/
        while (player == 0) {
            navswitch_update();
            start_update();

            /*if recieved, you are player 2*/
            if (ir_uart_read_ready_p() && ir_uart_getc() == 'S') {
                player = 2;
                my_ball.current_col = -1;
                paddle = PADDLE_START;
            /*if sent, you are player 1 & start with the ball*/
            } else if (navswitch_push_event_p(NAVSWITCH_PUSH) ) {
                ir_uart_putc('S');
                player = 1;
                ball_active = 1;
                paddle = PADDLE_START;
                my_ball = ball_init(); 
                
            }
        }

        pacer_wait ();
        paddle_update (&paddle);
        
        /*ball movement*/
        if (!ball_active && ir_uart_read_ready_p()) {

            uint8_t received = ir_uart_getc();

            // You Win!
            if (received == 'R') {
                // Happy face
                show_face(true, 3000);
                reset_game();
            
                
            } else { //Receive ball
                ball_active = 1;
                ball_received(&my_ball, received);
            }

        }
        /*if ball is active, update its position*/
        if (ball_active) {
            ball_tick_counter++;
            if (ball_tick_counter >= BALL_SPEED_DIVIDER) {
                ball_tick_counter = 0;
                ball_update(&my_ball);
                
                //ball hits paddle side
                if (my_ball.current_col == 4) {
                    //ball hits paddle
                    if (my_ball.row_mask & paddle) {
                        hit_paddle(&my_ball, paddle);
                    
                    //ball misses paddle
                    } else {
                        // You lose 
                        ir_uart_putc('R');
                        // Sad face
                        show_face(false, 3000);

                        reset_game();
                        
                    }
                }
                
                // ball transfers to other controller
                if (my_ball.current_col < 0) {
                    ball_transfer(&my_ball);
                    ball_active = 0;
                }
            }
        }


        /*update display*/
        display_update_game ();
    }
}