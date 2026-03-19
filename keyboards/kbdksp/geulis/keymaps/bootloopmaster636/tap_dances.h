#include QMK_KEYBOARD_H

// Tap Dance declarations
enum {
    TD_EQUAL_PLUS,
    TD_COMMA_PLUS,
    TD_DOT_PLUS,
    TD_BRACKETS
};

tap_dance_action_t tap_dance_actions[4];
