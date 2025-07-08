#include <stdio.h>
#include "pico/stdlib.h"
#include "init.h"

int main() {
    // Inicializa a saída serial para podermos ver as mensagens com printf
    initializeSystem();
    sleep_ms(2000); // Delay para dar tempo de conectar o monitor serial

    // Inicializa o nosso servo
    ssd1306_show(&display);

    // Variáveis para armazenar o valor lido
    float temp_value;
    char temp_str[32];
    float hum_value;
    char hum_str[32];

    // Configura o pino do LED para saída
    gpio_init(LED_RED_PIN);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);

    // Loop infinito para mover o servo
    while (1) {

        updateTextLine("======= AHT10 =======", 0, 0, 1, 128);
        if (!aht10_read(&hum_value, &temp_value)) {
            printf("Falha ao ler o sensor AHT10\n");
            updateTextLine("Falha ao ler o sensor AHT10", 0, 0, 1, 128);

            temp_value = 0;
            hum_value = 0; 
            sleep_ms(500);
        }; 


        sprintf(temp_str, "Temperatuara: %.2f C", temp_value); 
        sprintf(hum_str, "Umidade: %.2f %%", hum_value);

        if (hum_value > 70) {
            updateTextLine("Umidade alta!", 0, 40, 1, 128);
            gpio_put(LED_RED_PIN, 1);
        } else if (temp_value < 20) {
            updateTextLine("Temperatura baixa!", 0, 40, 1, 128);
            gpio_put(LED_RED_PIN, 1);
        } else {
            updateTextLine("", 0, 40, 1, 128);
            gpio_put(LED_RED_PIN, 0);
        }

        updateTextLine(temp_str, 0, 20, 1, 128); 
        updateTextLine(hum_str, 0, 30, 1, 128); 
        updateTextLine("======= AHT10 =======", 0, 55, 1, 128);

        ssd1306_show(&display);

        sleep_ms(500); // Pausa na posição mínima
    }

    return 0; // Este código nunca será alcançado
}