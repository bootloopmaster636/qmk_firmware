#include <stdint.h>
#include "../jpe230.h"
#include "action_util.h"
#include "host.h"
#include "oled_driver.h"
#include "progmem.h"

static void render_typing_icon(void) {
    static const char PROGMEM typing_icon[] = {
        0, 0, 0, 0, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0, 0, 0, 0, 0, 0, 0, 255, 255, 1, 1, 193, 217, 25, 1, 193, 217, 25, 1, 193, 217, 25, 1, 193, 217, 25, 25, 217, 193, 1, 1, 255, 255, 0, 0, 0, 0, 0, 0, 255, 255, 128, 128, 128, 128, 134, 134, 176, 176, 182, 182, 176, 176, 182, 182, 176, 176, 134, 134, 128, 128, 128, 128, 255, 255, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    };
    oled_write_raw_P(typing_icon, sizeof(typing_icon));
}

static void render_num_icon(void) {
    static const char PROGMEM num_icon[] = {
        0, 0, 0, 128, 192, 192, 192, 0, 0, 0, 0, 192, 192, 192, 192, 192, 192, 192, 192, 192, 0, 0, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 28, 28, 31, 31, 255, 255, 255, 0, 0, 0, 0, 193, 193, 193, 193, 193, 193, 255, 255, 255, 0, 0, 193, 193, 193, 193, 193, 193, 193, 255, 255, 255, 192, 192, 192, 192, 255, 255, 255, 192, 192, 192, 0, 255, 255, 255, 193, 193, 193, 193, 193, 193, 0, 0, 193, 193, 193, 193, 193, 193, 193, 255, 255, 255, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    oled_write_raw_P(num_icon, sizeof(num_icon));
}

static void render_caps(bool active) {
    static const char PROGMEM caps_off[] = {
        0, 0, 0, 0, 12, 12, 14, 14, 14, 14, 60, 60, 240, 240, 0, 0, 0, 0, 127, 103, 85, 85, 65, 127, 127, 65, 87, 87, 71, 127, 0, 0,
    };
    static const char PROGMEM caps_on[] = {
        255, 255, 15, 15, 195, 195, 241, 241, 241, 241, 195, 195, 15, 15, 255, 255, 255, 255, 128, 188, 146, 146, 188, 128, 128, 190, 170, 170, 190, 128, 255, 255,
    };

    if (active) {
        oled_write_raw_P(caps_on, sizeof(caps_on));
    } else {
        oled_write_raw_P(caps_off, sizeof(caps_off));
    }
}

static void render_shift(bool active) {
    static const char PROGMEM shift_off[] = {
        0, 0, 0, 0, 0, 192, 192, 48, 48, 192, 192, 0, 0, 0, 0, 0, 0, 12, 12, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 12, 12, 0,
    };
    static const char PROGMEM shift_on[] = {
        255, 255, 255, 63, 63, 15, 15, 195, 195, 15, 15, 63, 63, 255, 255, 255, 243, 240, 240, 252, 252, 231, 231, 231, 231, 231, 231, 252, 252, 240, 240, 243,
    };

    if (active) {
        oled_write_raw_P(shift_on, sizeof(shift_on));
    } else {
        oled_write_raw_P(shift_off, sizeof(shift_off));
    }
}


static void render_alt(bool active) {
    static const char PROGMEM alt_off[] = {
        0,128, 64,160, 80, 40, 16, 40, 16, 40, 16, 40, 16, 40, 16, 40, 15, 14, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
    };
    static const char PROGMEM alt_on[] = {
        255,127, 63, 31, 15,135,199,199,199,199,199,199,199,199,199,199,244,250,244,250,245,251,245,251,245,251,245,251,245,251,245,251,
    };

    if (active) {
        oled_write_raw_P(alt_on, sizeof(alt_on));
    } else {
        oled_write_raw_P(alt_off, sizeof(alt_off));
    }
}


static void render_control(bool active) {
    static const char PROGMEM ctrl_off[] = {
        0,  0,252,252, 12, 12, 12, 12,108, 48, 26,  6,238,224,  0,  0,  0,  0, 63, 63, 48, 48, 48, 48, 48, 48, 48, 48, 63, 63,  0,  0,
    };
    static const char PROGMEM ctrl_on[] = {
        255,255,  3,  3,243,243,243,243,147,207,229,249, 17, 31,255,255,255,255,192,192,207,207,207,207,207,207,207,207,192,192,255,255,
    };

    if (active) {
        oled_write_raw_P(ctrl_on, sizeof(ctrl_on));
    } else {
        oled_write_raw_P(ctrl_off, sizeof(ctrl_off));
    }
}

void render_main_screen(kb_modes_t active_layer) {
    switch (active_layer) {
        case QWERTY:
            oled_write_P(PSTR("QWTY "), true);
            break;
        case COLEMAK_DH:
            oled_write_P(PSTR("CLMDH"), true);
            break;
        case NUM:
            oled_write_P(PSTR("NUM F"), true);
        default:
            break;
    }

    led_t   led_state = host_keyboard_led_state();
    uint8_t mods      = get_mods() | get_oneshot_mods() | get_weak_mods();
    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("CAPS "), led_state.caps_lock);
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("SHIFT"), mods & MOD_MASK_SHIFT);
    oled_write_P(PSTR("CTRL "), mods & MOD_MASK_CTRL);
    oled_write_P(PSTR("ALT  "), mods & MOD_MASK_ALT);
    oled_write_P(PSTR("SUPER"), mods & MOD_MASK_GUI);
}
