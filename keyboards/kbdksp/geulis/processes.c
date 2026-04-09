// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "processes.h"
#include <complex.h>
#include <stdint.h>
#include "chthreads.h"
#include "hal_pal.h"
#include "keyboard.h"
#include "keycodes.h"
#include "matrix.h"
#include "oled/jpe230.h"
#include "quantum_keycodes.h"
#include "suspend.h"
#include "transactions.h"

split_sync_state_suspend_t suspend_state = {false};
uint32_t words_typed = 0;

uint8_t chars_typed = 0;
uint16_t last_keycode = 0;

void keyboard_post_init_user(void) {
    // render bootlogo
    oled_post_init();

    transaction_register_rpc(KB_TRANSACTION_SYNC_SUSPEND, slave_receive_handler);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_BOOT:
                oled_off();
                return true;
            case KC_A ... KC_0:
                if (keycode != last_keycode) {
                    chars_typed++;
                }
                if (chars_typed == 255) {
                    words_typed++;
                    chars_typed = 0;
                }
                last_keycode = keycode;
            case KC_SPACE:
                if (chars_typed >= 3) {
                    words_typed++;
                }
        }
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Nothing to do
}

void housekeeping_task_user(void) {
    // Nothing to do
}

void suspend_power_down_user() {
    if (is_keyboard_master()) {
        if (!suspend_state.is_suspended) {
            suspend_state.is_suspended = true;
            transaction_rpc_send(KB_TRANSACTION_SYNC_SUSPEND, sizeof(split_sync_state_suspend_t), &suspend_state);
        }
    }
}

void suspend_wakeup_init_user(void) {
    if (is_keyboard_master()) {
        if (suspend_state.is_suspended) {
            suspend_state.is_suspended = false;
            transaction_rpc_send(KB_TRANSACTION_SYNC_SUSPEND, sizeof(split_sync_state_suspend_t), &suspend_state);
        }
    }
}

void matrix_scan_user(void) {
    if (suspend_state.is_suspended) {
        chThdSleepMilliseconds(500);
    }
}

bool shutdown_user(bool jump_to_bootloader) {
    if (jump_to_bootloader) {
        render_dfu_screen();
    }
    return true;
}

//////////////// Split transport related code below ////////////////
void slave_receive_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    const split_sync_state_suspend_t *received_config = (const split_sync_state_suspend_t *)in_data;
    suspend_state.is_suspended                        = received_config->is_suspended;
}
