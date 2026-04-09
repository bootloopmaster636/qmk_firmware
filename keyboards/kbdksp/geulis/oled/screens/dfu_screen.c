#include <stdint.h>
#include "../jpe230.h"
#include "action_util.h"
#include "host.h"
#include "keyboard.h"
#include "oled_driver.h"
#include "progmem.h"


static void render_dfu_icon(void) {
    static const char PROGMEM dfu_icon[] = {
        0,  0,  0, 15, 31, 31, 27, 31, 27, 31, 31, 31, 31, 24, 24,152,152, 24, 24, 24, 31, 31, 31, 31, 31, 31, 31, 31, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 96,224,255,255,255,255,224, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240,112,112, 49,115, 51,113, 48,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,127,255,245,192,239,207,239,207,224,234,255,127,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(dfu_icon, sizeof(dfu_icon));
}

void render_dfu_screen(void) {
    oled_set_cursor(0, 3);
    render_dfu_icon();
    oled_set_cursor(0, 7);
    oled_write_P(PSTR(" DFU "), false);


    // because we have the oled at the right slave side
    if (is_keyboard_master()){
        oled_write_P(PSTR("Master"), true);
    } else {
        oled_write_P(PSTR("Slave "), true);
    }
}
