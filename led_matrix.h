#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pio_matrix.h"
#include "numbers_frames.h"

#define PIXELS 25
#define COLOR 6
#define FIRST_BYTE 24
#define SECOND_BYTE 16
#define THIRD_BYTE 8
static const uint led_pin = 7;
static const PIO pio = pio0;
static uint sm;
static int normal[5] = {0,0,0,0,0};
static int reverse[5] = {4,2,0,-2,-4};

void led_matrix_init() {
    set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, led_pin);
}

static uint to_decimal(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else {
        return -1;
    }
}

static uint to_rgb(char hex[COLOR]) {
    uint r = (to_decimal(hex[0]) * 16) + to_decimal(hex[1]);
    uint g = (to_decimal(hex[2]) * 16) + to_decimal(hex[3]);
    uint b = (to_decimal(hex[4]) * 16) + to_decimal(hex[5]);
    return (g << FIRST_BYTE) | (r << SECOND_BYTE) | (b << THIRD_BYTE);
}

static bool is_valid_number(uint number) {
    return number < 10;
}

void led_matrix_draw(uint number) {
    if (!is_valid_number(number)) return;
    char **frame = numbers_frames[number];
    int *direction = normal;
    for (uint i = 0; i < PIXELS; i++) {
        uint led_value = to_rgb(frame[24 - i + direction[(24 - i)%5]]);
        pio_sm_put_blocking(pio, sm, led_value);
        if ((24 - i)%5 == 0 && direction == normal) { direction = reverse; continue; }
        if ((24 - i)%5 == 0 && direction == reverse) { direction = normal; continue; }
    }
}

