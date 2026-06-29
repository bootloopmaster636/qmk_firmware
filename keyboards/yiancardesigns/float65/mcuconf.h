<<<<<<<< HEAD:keyboards/kbdksp/cacah/config.h
/* Copyright 2023 sendz
========
/* Copyright 2024 Yiancar-Designs
>>>>>>>> master:keyboards/yiancardesigns/float65/mcuconf.h
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

<<<<<<<< HEAD:keyboards/kbdksp/cacah/config.h
/* key matrix size */

#define MATRIX_ROWS 5
#define MATRIX_COLS 4

/* Keyboard Matrix Assignments */
// clang-format off

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
========
#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE
>>>>>>>> master:keyboards/yiancardesigns/float65/mcuconf.h
