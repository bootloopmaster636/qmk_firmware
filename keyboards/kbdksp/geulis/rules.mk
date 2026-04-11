SERIAL_DRIVER = vendor

OLED_DRIVER = ssd1306

OLED_DIR = oled
OLED_FILES = oled_handler.c \
				screens/bootlogo.c \
				screens/main_screen.c \
				screens/mouse_screen.c \
				screens/wrong_side.c \
				screens/dfu_screen.c \
				screens/stats_screen.c \

SRC += $(addprefix $(OLED_DIR)/, $(OLED_FILES)) processes.c tap_dances_hold.c

DEBUG_MATRIX_SCAN_RATE_ENABLE = no

RGBLIGHT_ENABLE = no
RGBLIGHT_DRIVER = ws2812
WS2812_DRIVER = vendor

# Tap Dance
TAP_DANCE_ENABLE = yes

# Mouse Keys
MOUSEKEY_ENABLE = yes

# Other
COMBO_ENABLE = yes
DEBOUNCE_TYPE = sym_eager_pr
NKRO_ENABLE = yes
