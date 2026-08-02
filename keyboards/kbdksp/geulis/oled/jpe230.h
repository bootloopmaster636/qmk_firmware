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
void oled_post_init(void);

// Layers enum
typedef enum {
    QWERTY     = 0,
    COLEMAK_DH = 1,
    MOUSE      = 2,
    NUM        = 3,
    DFU        = 4,
} kb_modes_t;

// Screens
void render_logo(void);
void render_main_screen(kb_modes_t active_layer);
void render_mouse_screen(void);
void render_dfu_screen(void);
void render_stats_screen(void);
void invert_periodically(void);
