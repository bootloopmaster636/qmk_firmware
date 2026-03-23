#include <stdbool.h>
#include "../jpe230.h"
#include "oled_driver.h"
#include "progmem.h"
void render_wrong_side(void) {
    oled_write_P(PSTR("WRONG"), true);
    oled_write_P(PSTR("PORT?"), true);
    oled_write_P(PSTR("-----"), true);
    oled_write_P(PSTR("Plug "), false);
    oled_write_P(PSTR("cable"), false);
    oled_write_P(PSTR("to   "), false);
    oled_write_P(PSTR("left "), false);
    oled_write_P(PSTR("side."), false);
}
