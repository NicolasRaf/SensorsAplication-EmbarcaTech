#include "aht10.h"


// --- Funções para o AHT10 ---
void aht10_init() {
    printf("--- DEBUG: Entrou em aht10_init() ---\n");
    uint8_t cmd_init[] = {0xE1, 0x08, 0x00}; 
    int ret_init = i2c_write_blocking(AHT10_I2C_PORT, AHT10_ADDR, cmd_init, sizeof(cmd_init), false);
    sleep_ms(40); 
}

bool aht10_read(float *humidity, float *temperature) {
    uint8_t cmd_trigger_measurement[] = {0xAC, 0x33, 0x00};
    uint8_t data[6]; 

    int ret_write = i2c_write_blocking(AHT10_I2C_PORT, AHT10_ADDR, cmd_trigger_measurement, sizeof(cmd_trigger_measurement), false);
    if (ret_write != sizeof(cmd_trigger_measurement)) {
        printf("--- ERROR: aht10_read() - Falha ao enviar comando Trigger. Código: %d ---\n", ret_write);
        return false;
    }
    sleep_ms(80); 

    int ret_read = i2c_read_blocking(AHT10_I2C_PORT, AHT10_ADDR, data, 6, false);
    if (ret_read != 6) {
        return false;
    }

    if (data[0] & 0x80) { 
        return false; 
    }
    if (!(data[0] & 0x08)) { 
        aht10_init(); 
        return false; 
    }

    uint32_t raw_hum = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4)  | (((uint32_t)data[3] & 0xF0) >> 4);
    uint32_t raw_temp = (((uint32_t)data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8)  | (uint32_t)data[5];

    *humidity = ( (float)raw_hum / (float)(1 << 20) ) * 100.0f;
    *temperature = ( (float)raw_temp / (float)(1 << 20) ) * 200.0f - 50.0f;
    return true;
}