#include "keymap_functions.h"
#include <stdint.h>
#include "unicode.h"

void send_unicode(uint32_t code_point, os_variant_t detected_os) {
    switch (detected_os) {
        case OS_LINUX:
            set_unicode_input_mode(1);
            break;
        case OS_MACOS:
        case OS_IOS:
            set_unicode_input_mode(0);
            break;
        case OS_WINDOWS:
            set_unicode_input_mode(2);
            break;
        case OS_UNSURE:
            return;
    }

    register_unicode(code_point);
}
