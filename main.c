#include <stdio.h>
#include "pico/stdlib.h"
#include "display.h"
#include "led_matrix.h"
#include "buttons.h"
#include "leds.h"

volatile bool green_led_status = false;
volatile bool blue_led_status = false;
char message[32];

void on_left_button_press() {
    green_led_status = !green_led_status;
    leds_status(green_led_status, blue_led_status, false);
    sprintf(message, "O LED Verde foi %s.\n", green_led_status ? "ligado" : "desligado");
    display_draw_string_and_flush(message);
    printf(message);
}

void on_right_button_press() {
    blue_led_status = !blue_led_status;
    leds_status(green_led_status, blue_led_status, false);
    sprintf(message, "O LED Azul foi %s.\n", blue_led_status ? "ligado" : "desligado");
    display_draw_string_and_flush(message);
    printf(message);
}

void init() {
    stdio_init_all();
    display_init();
    led_matrix_init();
    buttons_init(on_left_button_press, on_right_button_press);
    leds_init();
    printf("Programa iniciado.");
}

bool is_letter(char content) {
    return (content >= 'A' && content <= 'Z') || (content >= 'a' && content <= 'z');
}

bool is_number(char content) {
    return content >= '0' && content <= '9';
}

int main() {
    char request;
    init();
    while (true) {
        sleep_ms(50);
        if (!stdio_usb_connected()) continue;
        if (scanf("%c", &request) != 1) continue;
        if (is_letter(request)) {
            display_clean();
            sprintf(message, "Recebido o caractere %c", request);
            display_draw_string_and_flush(message);
        }
        if (is_number(request)) {
            led_matrix_draw(request - '0');
        }
    }
}
