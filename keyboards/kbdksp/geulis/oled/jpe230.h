// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include "action_util.h"
/* ---------------------------
 * Custom OLED Fncs Prototypes
 * ---------------------------
 */
void oled_timer_reset(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);


// Layers enum
typedef enum {
    QWERTY = 0,
    NUM = 1,
    MOUSE = 2,
    DFU = 3,
} kb_modes_t;


// Screens
void render_logo(void);
void render_wrong_side(void);
void render_main_screen(kb_modes_t active_layer);
