/** @file   end.c
    @author Alex Shepherd and Isaac Quinn
    @date   16 October 2026
    @brief  Ending / Play again screen for when a player Wins/Loses module
*/

#include "ledmat.h"
#include "system.h"
#include "tinygl.h"
#include "end.h"
#include "pacer.h"
#include "font3x5_1.h"

#define PACER_RATE 500

//Winning happy face map
static const uint8_t happy_face[]=
{
    0x0, 0x14, 0x0, 0x22, 0x1C
};

//Losing sad face map
static const uint8_t sad_face[]=
{
    0x0, 0x14, 0x0, 0x1C, 0x22
};

/** Shows the Win/Lose face once Won/Lost 
    @param won 1 = player has one, 0 = player has lost
    @param time time in ms  */
void show_face(int won, uint32_t time)
{
    pacer_init(PACER_RATE);
    const uint8_t* face = won ? happy_face : sad_face;
    uint16_t ticks = time * PACER_RATE / 1000;
    uint8_t col = 0;

    while (ticks--) {
        pacer_wait();
        ledmat_display_column(face[col], col);
        col = (col + 1) % 5;
    }
    ledmat_display_column(0, 0);
}

//Displays "PLAY AGAIN?" on screen
void play_again(void) {
    tinygl_clear();
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (20);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text ("PLAY AGAIN? ");

    while (1) {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            break;
        }
    }
}