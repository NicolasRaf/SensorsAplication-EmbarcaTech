#include "init.h"

void initDisplayI2C() {
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

void initInterrupts() {
    gpio_set_irq_enabled_with_callback(BUTTON_A_PIN, GPIO_IRQ_EDGE_RISE, true, buttons_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B_PIN, GPIO_IRQ_EDGE_RISE, true, buttons_callback);
}

void initializeSystem(void) {
    stdio_init_all();
    sleep_ms(1000);

    // configura I2C em 400 kHz
    printf("Configurando I2C do OLED...\n");
    initDisplayI2C();

    printf("Iniciando SSD1306...\n");
    // inicializa display; se der erro, imprime e trava
    if ( initializeDisplay() != 0 ) {
        printf("Erro ao inicializar o SSD1306\n");
    }

    servo_init();
    initGpioButtons();
    
    sleep_ms(200);
    initInterrupts();
  
    // tela limpa
    printf("Tela limpa.\n");
    clearScreen();
}