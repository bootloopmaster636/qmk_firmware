#include "tap_dances.h"
#include "keycodes.h"
#include "quantum_keycodes.h"

tap_dance_action_t tap_dance_actions[] = {
    [TD_EQUAL_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_ASTERISK),
    [TD_COMMA_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_COMMA, LSFT(KC_9)),
    [TD_DOT_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, LSFT(KC_0)),
    [TD_BRACKETS] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_BRACKET, KC_RIGHT_BRACKET)
};
