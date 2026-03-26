#include <stdint.h>
#include "../jpe230.h"
#include "action_util.h"
#include "host.h"
#include "oled_driver.h"
#include "progmem.h"


static void render_mouse_icon(void) {
    static const char PROGMEM mouse_icon[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,  0,144,200,196,200,144,  0, 64,128,  0, 32, 32, 32, 96, 64, 64,128,  0,  0,128,128,192,192,192,128,128,128,128,  0,  1,  2,  4,  0, 19, 39, 71, 39, 19,  0,  4,  2,  1,  0,  0,  0,112,252, 14, 14, 31, 31, 30, 30, 61, 61, 59, 91, 79, 71, 67,195,129,129,129,194,226,226,242,252,252,240,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  2,  4,  4,  4,  4,  8,  8, 24, 31, 31, 15, 15, 15,  7,  7,  7,  3,  1,  0,  0,  0,  0,
    };
    oled_write_raw_P(mouse_icon, sizeof(mouse_icon));
}

void render_mouse_screen(void) {
    oled_set_cursor(0, 5);
    render_mouse_icon();
    oled_set_cursor(0, 9);
    oled_write_P(PSTR("MOUSE"), false);
}
