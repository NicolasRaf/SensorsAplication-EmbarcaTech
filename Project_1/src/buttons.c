#include "buttons.h"

void initGpioButtons() {
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);
}


void buttons_callback(uint gpio, uint32_t events) {

    if (gpio == BUTTON_A_PIN) {
        servoState = 1;
    } else if (gpio == BUTTON_B_PIN) {
        servoState = 0;
        servo_set_angle(0);
    }
}