#include <stdint.h>
#include <stdio.h>
#include "../jpe230.h"
#include "action_util.h"
#include "host.h"
#include "modifiers.h"
#include "oled_driver.h"
#include "progmem.h"
#include "wpm.h"

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

static const char PROGMEM caps_off[] = {
    0, 112, 118, 114, 114, 114, 124, 0, 0, 60, 66, 66, 66, 0, 124, 18, 18, 124, 0, 124, 18, 18, 12, 0, 76, 74, 90, 50, 0, 0, 0, 0,
};
static const char PROGMEM caps_on[] = {
    255, 131, 141, 141, 141, 141, 131, 255, 255, 195, 189, 189, 189, 255, 131, 237, 237, 131, 255, 131, 237, 237, 243, 255, 179, 181, 165, 205, 255, 255, 255, 255,
};

static const char PROGMEM shift_off[] = {
    0, 32, 16, 8, 8, 16, 32, 0, 0, 76, 74, 90, 50, 0, 126, 8, 8, 126, 0, 122, 0, 124, 10, 10, 2, 0, 54, 72, 72, 72, 0, 0,
};
static const char PROGMEM shift_on[] = {
    255, 231, 243, 137, 137, 243, 231, 255, 255, 179, 181, 165, 205, 255, 129, 247, 247, 129, 255, 133, 255, 131, 245, 245, 253, 255, 201, 183, 183, 183, 255, 255,
};

static const char PROGMEM alt_off[] = {
    0, 48, 40, 36, 32, 36, 32, 0, 0, 124, 18, 18, 124, 0, 62, 64, 64, 64, 0, 54, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
static const char PROGMEM alt_on[] = {
    255, 199, 243, 219, 251, 219, 251, 255, 255, 131, 237, 237, 131, 255, 193, 191, 191, 191, 255, 201, 183, 183, 183, 255, 255, 255, 255, 255, 255, 255, 255, 255,
};

static const char PROGMEM ctrl_off[] = {
    0, 48, 72, 8, 8, 28, 8, 0, 0, 60, 66, 66, 66, 0, 54, 72, 72, 72, 0, 124, 18, 42, 76, 0, 62, 64, 64, 64, 0, 0, 0, 0,
};
static const char PROGMEM ctrl_on[] = {
    255, 207, 247, 247, 213, 227, 247, 255, 255, 195, 189, 189, 189, 255, 201, 183, 183, 183, 255, 131, 237, 213, 179, 255, 193, 191, 191, 191, 255, 255, 255, 255,
};

static char wpm_str[6];

void render_mods_icon(bool state_caps_on, bool state_shift_on, bool state_alt_on, bool state_ctrl_on) {
    oled_write_raw(state_caps_on ? caps_on : caps_off, sizeof(caps_off));
    oled_advance_page(false);

    oled_write_raw(state_shift_on ? shift_on : shift_off, sizeof(shift_off));
    oled_advance_page(false);

    oled_write_raw(state_alt_on ? alt_on : alt_off, sizeof(alt_off));
    oled_advance_page(false);

    oled_write_raw(state_ctrl_on ? ctrl_on : ctrl_off, sizeof(ctrl_off));
    oled_advance_page(false);
}

void render_main_screen(kb_modes_t active_layer) {
    oled_set_cursor(0, 0);
    switch (active_layer) {
        case QWERTY:
            render_typing_icon();
            oled_set_cursor(0, 4);
            oled_write_P(PSTR("QWRTY"), false);
            break;
        case COLEMAK_DH:
            render_typing_icon();
            oled_set_cursor(0, 4);
            oled_write_P(PSTR("CLMDH"), false);
            break;
        case NUM:
            render_num_icon();
            oled_set_cursor(0, 4);
            oled_write_P(PSTR("NUM F"), false);
        default:
            break;
    }

    // render mods
    led_t   led_state = host_keyboard_led_state();
    uint8_t mods      = get_mods() | get_oneshot_mods() | get_weak_mods();
    oled_advance_page(false);
    oled_advance_page(false);
    render_mods_icon(led_state.caps_lock, mods & MOD_MASK_SHIFT, mods & MOD_MASK_ALT, mods & MOD_MASK_CTRL);

    // render wpm
    oled_set_cursor(0, 14);
    oled_write_P(PSTR(" WPM "), true);
    sprintf(wpm_str, " %03d ", get_current_wpm());
    oled_write_P(wpm_str, true);
}
