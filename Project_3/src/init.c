// init.c
#include "init.h"

void initI2C() {

    // Display I2C
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Sensor I2C
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void initializeSystem(void) {
    stdio_init_all();
    sleep_ms(1000);

    // configura I2C em 400 kHz
    printf("Configurando I2C do OLED...\n");
    initI2C();

    printf("Iniciando SSD1306...\n");
    // inicializa display; se der erro, imprime e trava
    if ( initializeDisplay() != 0 ) {
        printf("Erro ao inicializar o SSD1306\n");
    }

    // configura o MPU6050
    printf("Configurando o MPU6050...\n");
    mpu6050_init();

    // configura o servo
    printf("Configurando o servo...\n");
    servo_init();

    // tela limpa
    printf("Tela limpa.\n");
    clearScreen();
}


