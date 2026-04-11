// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <complex.h>
#include <stdint.h>
#include <sys/_intsup.h>
#include <time.h>
#include "action_layer.h"
#include "config.h"
#include "jpe230.h"
#include "keyboard.h"
#include "oled_driver.h"
#include "processes.h"
#include "timer.h"
#ifdef OLED_ENABLE
uint8_t logged_row;
uint8_t logged_col;

__attribute__((weak)) void handle_oled_keypress(uint16_t keycode, keyrecord_t *record) {}

__attribute__((weak)) oled_rotation_t rotate_master(oled_rotation_t rotation) {
    return rotation;
}
__attribute__((weak)) oled_rotation_t rotate_slave(oled_rotation_t rotation) {
    return rotation;
}

// Global variables
static uint32_t   oled_timer          = 0;
static bool       logo_finished       = false;
static kb_modes_t last_layer          = -1;
static bool       enable_logo         = false;
static bool       wrong_side_rendered = false;
static bool screen_inverted = false;

void oled_timer_reset(void) {
    oled_timer = timer_read32();
}

void oled_post_init(void) {
    oled_timer = timer_read32();

    // whether to render easter egg or not
    uint32_t hardware_seed = *(volatile uint32_t *)(0x40060000 + 0x1C);
    srand(hardware_seed);
    int random_result = (rand() % 16) + 1;
    enable_logo       = random_result == 1;
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
    kb_modes_t layer = (kb_modes_t)get_highest_layer(layer_state | default_layer_state);
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
            render_stats_screen();
            break;
    }
}

bool oled_task_user(void) {
    if (kb_state.is_suspended || last_input_activity_elapsed() > OLED_TIMEOUT) {
        render_stats_screen();
        oled_off();
        return false;
    } else {
        oled_on();
    }

    // Render logo if the keyboard just booted
    if (!logo_finished) {
        render_logo(enable_logo);

        if (timer_elapsed32(oled_timer) > 3000) {
            oled_clear();
            logo_finished = true;
        }

        return true;
    }

    if (is_keyboard_master() && !wrong_side_rendered) {
        // Bc the oled is on the slave side, just print out
        // warning message if the slave side got plugged usb plugged in
        render_wrong_side();
        wrong_side_rendered = true;
        return true;
    } else {
        render_screen_by_layer();
        invert_periodically();
    }

    return false;
}

void invert_periodically(void) {
    if (timer_read32() % 30000 == 0) {
        screen_inverted = !screen_inverted;
        oled_invert(screen_inverted);
    }
}

#endif
