// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include "action_layer.h"
#include "jpe230.h"
#include "keyboard.h"
#include "oled_driver.h"
#ifdef OLED_ENABLE
uint8_t logged_row;
uint8_t logged_col;

__attribute__ ((weak)) void handle_oled_keypress(uint16_t keycode, keyrecord_t *record) {}

__attribute__ ((weak)) oled_rotation_t rotate_master(oled_rotation_t rotation) {return rotation;}
__attribute__ ((weak)) oled_rotation_t rotate_slave(oled_rotation_t rotation) {return rotation;}


// Global variables
static uint32_t oled_timer = 0;
static bool logo_finished = false;
static bool is_oled_enabled = true;
static kb_modes_t last_layer = -1;

void oled_timer_reset(void) { oled_timer = timer_read32(); }

void keyboard_post_init_user(void) {
    oled_timer = timer_read32();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // Because all of my screen is portrait, we use this rotation
    return OLED_ROTATION_270;
}

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    logged_row = record->event.key.row;
    logged_col = record->event.key.col;

    handle_oled_keypress(keycode, record);
}

void render_screen_by_layer(void) {
    kb_modes_t layer = (kb_modes_t) get_highest_layer(layer_state | default_layer_state);
    if (layer != last_layer) {
            oled_clear();
            last_layer = layer;
        }

    switch (layer) {
        case QWERTY:
        case COLEMAK_DH:
        case NUM:
            render_main_screen(layer);
            break;
        case MOUSE:
            render_mouse_screen();
            break;
        case DFU:
            break;
    }
}

bool oled_task_user(void) {
    if (!is_oled_enabled) {
        oled_off();
        return false;
    } else  {
        oled_on();
    }

    // Render logo if the keyboard just booted
    if (!logo_finished) {
        render_logo();

        if (timer_elapsed32(oled_timer) > 3000) {
            oled_clear();
            logo_finished = true;
        }

        return true;
    }

    if (is_keyboard_master()) {
        // Bc the oled is on the slave side, just print out
        // warning message if the slave side got plugged usb plugged in
        render_wrong_side();
        return true;
    } else {
        render_screen_by_layer();
    }


    return false;
}

void housekeeping_task_user(void) {
    is_oled_enabled = (bool)(last_input_activity_elapsed() < 10000);
}
#endif
