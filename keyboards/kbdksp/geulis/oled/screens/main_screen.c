#include <stdint.h>
#include "../jpe230.h"
#include "action_util.h"
#include "host.h"
#include "oled_driver.h"
#include "progmem.h"

void render_main_screen(kb_modes_t active_layer) {
    switch (active_layer) {
        case QWERTY:
            oled_write_P(PSTR("QWTY "), true);
            break;
        case NUM:
            oled_write_P(PSTR("NUM-F"), true);
        default:
            break;
    }

    led_t led_state = host_keyboard_led_state();
    uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();
    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("CAPS "), led_state.caps_lock);
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("SHIFT"), mods & MOD_MASK_SHIFT);
    oled_write_P(PSTR("CTRL "), mods & MOD_MASK_CTRL);
    oled_write_P(PSTR("ALT  "), mods & MOD_MASK_ALT);
    oled_write_P(PSTR("SUPER"),mods & MOD_MASK_GUI);
}
