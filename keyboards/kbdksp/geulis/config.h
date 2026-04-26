 /* Copyright 2024 sendz
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

#pragma once

#include "config_rp2040.h"
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap to bootloader behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN        GP3
#define I2C1_SDA_PIN        GP2
#define I2C_DRIVER I2CD1
#define OLED_FONT_H "keyboards/kbdksp/geulis/fonts/glcdfont.c"

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define VBUS_SENSE GP12

// oled settings
#define OLED_TIMEOUT (60000*3)
#define OLED_BRIGHTNESS 8
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 15

// Configurations
#define TAPPING_TERM 200
#define SPECULATIVE_HOLD

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000
#define TAPPING_TOGGLE 2

#define MOUSEKEY_INERTIA
#define MOUSEKEY_DELAY 60
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 40
#define MOUSEKEY_TIME_TO_MAX 24
#define MOUSEKEY_FRICTION 32
#define MOUSEKEY_MOVE_DELTA 1
#define MOUSEKEY_SENS_Y 0.86

// Split transport stuff
#define SPLIT_TRANSACTION_IDS_KB KB_TRANSACTION_SYNC_STATE


// RGB stuff
#ifdef RGBLIGHT_ENABLE
  #define WS2812_DI_PIN GP13
  #define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral

	#define RGBLIGHT_EFFECT_BREATHING
	#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	#define RGBLIGHT_EFFECT_SNAKE
	#define RGBLIGHT_EFFECT_KNIGHT
	#define RGBLIGHT_EFFECT_CHRISTMAS
	#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	#define RGBLIGHT_EFFECT_RGB_TEST
	#define RGBLIGHT_EFFECT_ALTERNATING
	#define RGBLIGHT_EFFECT_TWINKLE

  #define RGBLIGHT_LED_COUNT 16

  #define RGBLED_SPLIT { 8, 8 }

  #define RGBLIGHT_LIMIT_VAL 120
  #define RGBLIGHT_HUE_STEP 10
  #define RGBLIGHT_SAT_STEP 17
  #define RGBLIGHT_VAL_STEP 17
#endif
