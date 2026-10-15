#include "ledmat.h"
#include "system.h"
#include "tinygl.h"
#include "end.h"
#include "pacer.h"

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
    tinygl_clear();
    for (uint8_t col=0; col < 5; col++) {
        for (uint8_t row=0; row < 7; row++) {
            if (face[col]& (1<<row)) {
                tinygl_draw_point(tinygl_point(row, col), 1);
            }
        }
    }
    while (ticks--) {
        pacer_wait();
        tinygl_update();
    }
}

void play_again(void) {
    tinygl_clear();
    tinygl_draw_string("PLAY AGAIN?");
    while (1) {
        pacer_wait();
        tinygl_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
}