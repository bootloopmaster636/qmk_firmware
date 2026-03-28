/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
 * Modification for Vial support by Drew Petersen
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// clang-format off

#include <stdint.h>
#include "keycodes.h"
#include "keymap_us.h"
#include "modifiers.h"
#include "process_combo.h"
#include "progmem.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

// TAP DANCES
enum {
    TD_EQUAL_PLUS,
    TD_COMMA_PLUS,
    TD_DOT_PLUS,
    TD_BRACKETS
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_EQUAL_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_EQUAL, LSFT(KC_1)),
    [TD_COMMA_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, LSFT(KC_9)),
    [TD_DOT_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, LSFT(KC_0)),
    [TD_BRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_BRACKET, KC_RIGHT_BRACKET)
};

// COMBOS
const uint16_t PROGMEM capslock_combo[] = {KC_TAB, OSM(MOD_LCTL), COMBO_END};
const uint16_t PROGMEM auto_underscore_combo[] = {OSM(MOD_LSFT), KC_SPACE, COMBO_END};
const uint16_t PROGMEM bootloader_combo[] = {KC_SPACE, KC_TAB, KC_ESCAPE, COMBO_END};
const uint16_t PROGMEM qwerty_pdf[] = {KC_SPACE, KC_ENTER, KC_MINUS, COMBO_END};
const uint16_t PROGMEM colemak_pdf[] = {KC_SPACE, KC_ENTER, TD(TD_EQUAL_PLUS), COMBO_END};
combo_t key_combos[] = {
    COMBO(capslock_combo, KC_CAPS_LOCK),
    COMBO(auto_underscore_combo, LSFT(KC_MINUS)),
    COMBO(bootloader_combo, MO(4)),
    COMBO(qwerty_pdf, PDF(0)),
    COMBO(colemak_pdf, PDF(1)),
};



// KEYMAPS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Layer 0 and 1, base layout qwerty, colemak dh
 */

[0] = LAYOUT_split_3x6_5t_plus(
    KC_ESCAPE,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                                                                       KC_Y,   KC_U,   KC_I,   KC_O,   KC_MINS,    TD(TD_EQUAL_PLUS),
    KC_TAB   ,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G, KC_MEDIA_PLAY_PAUSE,                                                  KC_MUTE,        KC_H,   KC_J,   KC_K,   KC_L,   KC_P,       KC_QUOTE,
    OSM(MOD_LCTL),KC_Z, KC_X,   KC_C,   KC_V,   KC_B, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,             LCA(KC_F13), LCA(KC_F14),       KC_N,   KC_M,   TD(TD_COMMA_PLUS), TD(TD_DOT_PLUS), KC_SLASH, KC_SEMICOLON,
    KC_LGUI  ,  OSM(MOD_LALT),  OSL(2), OSM(MOD_LSFT),  KC_SPACE,                                                                           KC_ENT, TT(3),  KC_BACKSPACE,   TD(TD_BRACKETS),   KC_BACKSLASH
),

[1] = LAYOUT_split_3x6_5t_plus(
    KC_ESCAPE,  KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,                                                                                       KC_J,   KC_L,   KC_U,   KC_Y,   KC_MINS,    TD(TD_EQUAL_PLUS),
    KC_TAB   ,  KC_A,   KC_R,   KC_S,   KC_T,   KC_G, KC_MEDIA_PLAY_PAUSE,                                                  KC_MUTE,        KC_M,   KC_N,   KC_E,   KC_I,   KC_O,       KC_QUOTE,
    OSM(MOD_LCTL),KC_Z, KC_X,   KC_C,   KC_D,   KC_V, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,             LCA(KC_F13), LCA(KC_F14),       KC_K,   KC_H,   TD(TD_COMMA_PLUS), TD(TD_DOT_PLUS), KC_SLASH, KC_SEMICOLON,
    KC_LGUI  ,  OSM(MOD_LALT),  OSL(2), OSM(MOD_LSFT),  KC_SPACE,                                                                           KC_ENT, TT(3),  KC_BACKSPACE,   TD(TD_BRACKETS),   KC_BACKSLASH
),

/*
 * Layer 2, number and F keys
 */
[2] = LAYOUT_split_3x6_5t_plus(
    KC_GRAVE ,  KC_PRINT_SCREEN,KC_F1,  KC_F2,  KC_F3,  KC_F4,                                                          KC_PSLS,    KC_1,       KC_2,       KC_3,   KC_PGUP,    KC_PGDN,
    KC_NO    ,  KC_NO,          KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_TRNS,                        KC_TRNS,                KC_PAST,    KC_4,       KC_5,       KC_6,   KC_HOME,    KC_END,
    KC_TRNS  ,  KC_NO,          KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,               KC_TRNS,    KC_TRNS,    KC_PMNS,    KC_7,       KC_8,       KC_9,   KC_INSERT,  KC_DELETE,
    KC_TRNS  ,  KC_TRNS,        KC_TRNS,KC_TRNS,KC_TRNS,                                                    KC_TRNS,    KC_PLUS,    KC_TRNS,    KC_0,   KC_DOT
),

/*
 * Layer 3, mouse keys and navigation
 */
[3] = LAYOUT_split_3x6_5t_plus(
    KC_NO  ,  KC_NO,    QK_MOUSE_BUTTON_3,      QK_MOUSE_CURSOR_UP,     QK_MOUSE_BUTTON_2,      KC_NO,                                              KC_NO,                  KC_NO,              KC_NO,                  KC_NO,                  KC_NO, KC_NO,
    KC_NO  ,  KC_NO,    QK_MOUSE_CURSOR_LEFT,   QK_MOUSE_CURSOR_DOWN,   QK_MOUSE_CURSOR_RIGHT,  KC_NO, KC_NO,                     KC_NO,            KC_LEFT,                KC_DOWN,            KC_UP,                  KC_RIGHT,               KC_NO, KC_NO,
    KC_TRNS,  KC_NO,    KC_NO,                  QK_MOUSE_BUTTON_4,      QK_MOUSE_BUTTON_5,      KC_NO, KC_NO, KC_NO,              KC_NO, KC_NO,     QK_MOUSE_WHEEL_RIGHT,   QK_MOUSE_WHEEL_UP,  QK_MOUSE_WHEEL_DOWN,    QK_MOUSE_WHEEL_LEFT,    KC_NO, KC_NO,
    KC_NO  ,  KC_TRNS,  KC_NO,                  KC_TRNS,                QK_MOUSE_BUTTON_1,                                               KC_NO,     KC_TRNS,                KC_NO,                  KC_NO,                  KC_NO
),

/*
 * Layer 4, reboot to bootloader
 */
[4] = LAYOUT_split_3x6_5t_plus(
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                                  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  QK_REBOOT,  QK_BOOTLOADER,  KC_NO, KC_NO,         KC_NO,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                                    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
