#ifndef LEDS_BUTTONS_H
#define LEDS_BUTTONS_H

#include "pico/stdlib.h"
#include "servo.h"

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

void initGpioButtons();
void buttons_callback(uint gpio, uint32_t events);

#endif