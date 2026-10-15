#include "ledmat.h"
#include "system.h"
#include "tinygl.h"
#include "end.h"
#include "pacer.h"
#include "font3x5_1.h"

#define PACER_RATE 500

static const uint8_t happy_face[]=
{
    0x10, 0x22, 0x20, 0x22, 0x10
};

static const uint8_t sad_face[]=
{
    0x10, 0x12, 0x10, 0x12, 0x10
};

void show_face(bool won, uint16_t time)
{
    const uint8_t* face = won ? happy_face : sad_face;
    uint16_t ticks = time * PACER_RATE / 1000;
    uint8_t col = 0;

    while (ticks--) {
        pacer_wait();
        ledmat_display_column(face[col], col);
        col = (col + 1) % 5;
        pacer_wait();
    }
    ledmat_display_column(0, 0);
}

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

    tinygl_clear ();
    tinygl_update ();
}