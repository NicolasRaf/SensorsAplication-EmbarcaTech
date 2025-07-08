// init.c
#include "init.h"

void initI2C() {
    i2c_init(i2c0, 100 * 1000); // Inicializa I2C na porta 0 a 100kHz
    gpio_set_function(AHT10_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(AHT10_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(AHT10_SDA_PIN); // Ativa pull-ups internos (externos são melhores)
    gpio_pull_up(AHT10_SCL_PIN);

    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
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

    // configura o AHT10
    printf("Configurando o AHT10...\n");
    aht10_init();

    // tela limpa
    printf("Tela limpa.\n");
    clearScreen();
}


