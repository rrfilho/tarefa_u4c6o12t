#include "pico/stdlib.h"

static const uint GREEN_LED = 11;
static const uint BLUE_LED = 12;
static const uint RED_LED = 13;

static void led_init(uint led_pin) {
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}

void leds_init() {
    led_init(GREEN_LED);
    led_init(BLUE_LED);
    led_init(RED_LED);
}

void leds_status(bool green_status, bool blue_status, bool red_status) {
    gpio_put(GREEN_LED, green_status);
    gpio_put(BLUE_LED, blue_status);
    gpio_put(RED_LED, red_status);
}