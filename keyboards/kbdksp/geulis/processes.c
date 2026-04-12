// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "processes.h"
#include <complex.h>
#include <stdint.h>
#include "chschd.h"
#include "chthreads.h"
#include "hal_pal.h"
#include "keyboard.h"
#include "keycodes.h"
#include "matrix.h"
#include "oled/jpe230.h"
#include "oled_driver.h"
#include "quantum_keycodes.h"
#include "suspend.h"
#include "transactions.h"
#include "usb_report_handling.h"

split_sync_state_t kb_state        = {false, 0};
split_sync_state_t last_sent_state = {false, 0};

uint8_t  chars_typed  = 0;
uint16_t last_keycode = 0;

void keyboard_post_init_kb(void) {
    // render bootlogo
    oled_post_init();

    if (!is_keyboard_master()) {
        transaction_register_rpc(KB_TRANSACTION_SYNC_STATE, slave_receive_handler);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_A ... KC_0:
                if (keycode != last_keycode) {
                    chars_typed++;
                }
                if (chars_typed == 255) {
                    kb_state.words_typed++;
                    chars_typed = 0;
                }
                last_keycode = keycode;
                break;
            case KC_SPACE:
                if (chars_typed >= 3) {
                    kb_state.words_typed++;
                    chars_typed = 0;
                }
                break;
        }
    }

    return true;
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        transaction_rpc_send(KB_TRANSACTION_SYNC_STATE, sizeof(split_sync_state_t), &kb_state);
    }
}

void suspend_power_down_kb() {
    if (is_keyboard_master()) {
        if (!kb_state.is_suspended) {
            kb_state.is_suspended = true;
            transaction_rpc_send(KB_TRANSACTION_SYNC_STATE, sizeof(split_sync_state_t), &kb_state);
        }
    }
}

void suspend_wakeup_init_kb(void) {
    if (is_keyboard_master()) {
        if (kb_state.is_suspended) {
            kb_state.is_suspended = false;
            transaction_rpc_send(KB_TRANSACTION_SYNC_STATE, sizeof(split_sync_state_t), &kb_state);
        }
    }
}

void matrix_scan_kb(void) {
    if (kb_state.is_suspended) {
        chThdSleepMilliseconds(500);
    }
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        oled_clear();
        oled_render();
        render_dfu_screen();
    }
    return true;
}

//////////////// Split transport related code below ////////////////
void slave_receive_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    const split_sync_state_t *received_config = (const split_sync_state_t *)in_data;
    kb_state.is_suspended                     = received_config->is_suspended;
    kb_state.words_typed                      = received_config->words_typed;

    // do something regarding the data
    if (last_sent_state.is_suspended != kb_state.is_suspended) {
        if (!is_keyboard_master()) {
            oled_clear();
            oled_render();
        }
        if (kb_state.is_suspended) {
            suspend_power_down();
        } else {
           suspend_wakeup_init();
        }
    }

    last_sent_state = *received_config;
}
