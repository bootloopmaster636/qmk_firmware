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
    0, 0, 0, 0, 12, 12, 14, 14, 14, 14, 60, 60, 240, 240, 0, 0, 0, 0, 127, 103, 85, 85, 65, 127, 127, 65, 87, 87, 71, 127, 0, 0,
};
static const char PROGMEM caps_on[] = {
    255, 255, 15, 15, 195, 195, 241, 241, 241, 241, 195, 195, 15, 15, 255, 255, 255, 255, 128, 188, 146, 146, 188, 128, 128, 190, 170, 170, 190, 128, 255, 255,
};

static const char PROGMEM shift_off[] = {
    0, 0, 0, 0, 0, 192, 192, 48, 48, 192, 192, 0, 0, 0, 0, 0, 0, 12, 12, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 12, 12, 0,
};
static const char PROGMEM shift_on[] = {
    255, 255, 255, 63, 63, 15, 15, 195, 195, 15, 15, 63, 63, 255, 255, 255, 243, 240, 240, 252, 252, 231, 231, 231, 231, 231, 231, 252, 252, 240, 240, 243,
};

static const char PROGMEM alt_off[] = {
    0, 128, 64, 160, 80, 40, 16, 40, 16, 40, 16, 40, 16, 40, 16, 40, 15, 14, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
};
static const char PROGMEM alt_on[] = {
    255, 127, 63, 31, 15, 135, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 244, 250, 244, 250, 245, 251, 245, 251, 245, 251, 245, 251, 245, 251, 245, 251,
};

static const char PROGMEM ctrl_off[] = {
    0, 0, 252, 252, 12, 12, 12, 12, 108, 48, 26, 6, 238, 224, 0, 0, 0, 0, 63, 63, 48, 48, 48, 48, 48, 48, 48, 48, 63, 63, 0, 0,
};
static const char PROGMEM ctrl_on[] = {
    255, 255, 3, 3, 243, 243, 243, 243, 147, 207, 229, 249, 17, 31, 255, 255, 255, 255, 192, 192, 207, 207, 207, 207, 207, 207, 207, 207, 192, 192, 255, 255,
};

static char PROGMEM mods_images[128] = {};

static char wpm_str[6];

void render_mods_icon(bool state_caps_on, bool state_shift_on, bool state_alt_on, bool state_ctrl_on) {
    for (int row = 0; row < 4; row++) {
        // Determine which status to check
        bool is_on;
        const char *data_on, *data_off;

        // Logic for left half (0-15) and right half (16-31)
        for (int col = 0; col < 32; col++) {
            // Calculate the local row (0 or 1) for the icon data
            int icon_row = row % 2;
            int icon_col = (col < 16) ? col : (col - 16);
            int icon_idx = (icon_row * 16) + icon_col;

            if (col < 16) {
                // Left Icon Selection
                data_on  = (row < 2) ? caps_on  : alt_on;
                data_off = (row < 2) ? caps_off : alt_off;
                is_on    = (row < 2) ? state_caps_on : state_alt_on;
            } else {
                // Right Icon Selection
                data_on  = (row < 2) ? shift_on : ctrl_on;
                data_off = (row < 2) ? shift_off : ctrl_off;
                is_on    = (row < 2) ? state_shift_on : state_ctrl_on;
            }

            // Apply to the final buffer
            mods_images[row * 32 + col] = is_on ? data_on[icon_idx] : data_off[icon_idx];
        }
    }

    oled_write_raw_P(mods_images, sizeof(mods_images));
}

void render_main_screen(kb_modes_t active_layer) {
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
    oled_write_ln_P(" ", false);
    oled_write_ln_P(" ", false);
    render_mods_icon(led_state.caps_lock, mods & MOD_MASK_SHIFT, mods & MOD_MASK_ALT, mods & MOD_MASK_CTRL);

    // render wpm
    oled_set_cursor(0, 13);
    oled_write_P(PSTR(" WPM "), true);
    sprintf(wpm_str, " %03d ", get_current_wpm());
    oled_write_P(wpm_str, true);
}
