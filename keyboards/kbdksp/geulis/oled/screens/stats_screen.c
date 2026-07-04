#include <stdbool.h>
#include <stdint.h>
#include "../jpe230.h"
#include "oled_driver.h"
#include "processes.h"
#include "progmem.h"

void render_stats_screen(void) {
    char words_typed_string[6];
    snprintf(words_typed_string, sizeof(words_typed_string), "%5lu", kb_state.words_typed);

    char     hours_str[4];
    char     mins_str[4];
    uint32_t timer_value   = timer_read32();
    uint8_t  hour_active   = (timer_value / 3600000) % 100;
    uint8_t  minute_active = (timer_value / 60000) % 60;

    snprintf(hours_str, sizeof(hours_str), "%02dh", hour_active);
    snprintf(mins_str, sizeof(mins_str), "%02dm", minute_active);

    oled_set_cursor(0, 0);
    if (kb_state.is_suspended) {
        oled_write_P(PSTR("SLEEP"), false);
    } else {
        oled_write_P(PSTR("STATS"), false);
    }
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("-----"), false);

    oled_set_cursor(0, 3);
    oled_write_P(PSTR("Words"), false);
    oled_set_cursor(0, 4);
    oled_write_P(PSTR("typed"), false);
    oled_set_cursor(0, 5);
    oled_write(words_typed_string, false);

    oled_set_cursor(0, 7);
    oled_write_P(PSTR("Time:"), false);
    oled_set_cursor(0, 8);
    oled_write(hours_str, false);
    oled_set_cursor(0, 9);
    oled_write(mins_str, false);
}
