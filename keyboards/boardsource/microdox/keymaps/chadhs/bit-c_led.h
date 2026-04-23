#pragma once

#include "quantum.h"

#define LED_ON          2
#define LED_DIM         1
#define LED_OFF         0

#define PIN_LED         F0

void set_bit_c_LED(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            gpio_set_pin_output(PIN_LED);
            gpio_write_pin_high(PIN_LED);
        break;

        case LED_DIM:
            gpio_set_pin_input(PIN_LED);
        break;

        case LED_OFF:
            gpio_set_pin_output(PIN_LED);
            gpio_write_pin_low(PIN_LED);
        break;

        default:
        break;
    }
}
