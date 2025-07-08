
#ifndef AHT10_H
#define AHT10_H

#include <stdio.h>
#include <string.h>      
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h" 

// --- AHT10 (Sensor de Temperatura e Umidade) ---
#define AHT10_I2C_PORT    i2c0
#define AHT10_SDA_PIN     0
#define AHT10_SCL_PIN     1
#define AHT10_ADDR        0x38

void aht10_init();
bool aht10_read(float *humidity, float *temperature);

#endif  // AHT10_H