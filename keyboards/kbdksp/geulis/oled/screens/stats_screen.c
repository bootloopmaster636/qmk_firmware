#include <stdbool.h>
#include <stdint.h>
#include "../jpe230.h"
#include "oled_driver.h"
#include "processes.h"
#include "progmem.h"

void render_stats_screen(void) {
    char words_typed_string[6];
    sprintf(words_typed_string, "%lu", kb_state.words_typed);

    char time_active[6];
    uint16_t timer_value = timer_read();
    uint8_t hour_active = (timer_value / 3600000) % 100;
    uint8_t minute_active = (timer_value / 60000) % 60;
    sprintf(time_active, "%02d:%02d", hour_active, minute_active);

    if (kb_state.is_suspended) {
        oled_write_P(PSTR("SYSTEM"), true);
        oled_write_P(PSTR("  IS  "), true);
        oled_write_P(PSTR("SLEEP "), true);
        oled_write_P(PSTR("======"), true);
        return;
    }

    oled_advance_page(true);

    oled_write_P(PSTR("STATS"), true);
    oled_write_ln_P(PSTR("-----"), true);

    oled_advance_page(true);

    oled_write_P(PSTR("Words"), false);
    oled_write_P(PSTR("typed"), false);
    oled_write_ln_P(PSTR(words_typed_string), false);

    oled_advance_page(true);

    oled_write_P(PSTR("Time:"), false);
    oled_write_P(PSTR(time_active), false);
}
