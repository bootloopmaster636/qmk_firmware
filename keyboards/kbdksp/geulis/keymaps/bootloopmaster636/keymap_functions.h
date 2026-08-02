#pragma once

#include <stdint.h>
#include "os_detection.h"
void send_unicode(uint32_t code_point, os_variant_t detected_os);
