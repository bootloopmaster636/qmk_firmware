#pragma once

#include <stdint.h>
#include "keyboard.h"
#include "oled/jpe230.h"
#include "suspend.h"
#include "transactions.h"

typedef struct {
    bool is_suspended;
} split_sync_state_suspend_t;

extern split_sync_state_suspend_t suspend_state;
extern uint32_t words_typed;


void slave_receive_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);
