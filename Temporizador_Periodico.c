#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LEDR 11
#define LEDY 12
#define LEDG 13

struct repeating_timer timer;
volatile uint8_t current_led = 0; // 0-Vermelho, 1-Amarelo, 2-Verde

bool timer_callback(struct repeating_timer *t) {

    // Desliga todos os LEDs
    gpio_put(LEDR, false);
    gpio_put(LEDY, false);
    gpio_put(LEDG, false);
    
    // Avança para o próximo LED da sequência
    current_led = (current_led + 1) % 3;
    
    // Liga o novo LED
    switch(current_led) {
        case 0: gpio_put(LEDR, true); break;
        case 1: gpio_put(LEDY, true); break;
        case 2: gpio_put(LEDG, true); break;
    }
    return true;
}

int main() {
    stdio_init_all();

    // Configuração inicial dos LEDs
    gpio_init(LEDR);
    gpio_init(LEDY);
    gpio_init(LEDG);
    
    gpio_set_dir(LEDR, GPIO_OUT);
    gpio_set_dir(LEDY, GPIO_OUT);
    gpio_set_dir(LEDG, GPIO_OUT);

    // Inicia com o vermelho ligado
    gpio_put(LEDR, true);

    // Configura o temporizador para 3 segundos
    add_repeating_timer_ms(3000, timer_callback, NULL, &timer);

    while(true) {
        sleep_ms(1000);
        
        // Verifica e imprime o estado atual
        if(gpio_get(LEDR)) printf("LED VERMELHO LIGADO\n");
        else if(gpio_get(LEDY)) printf("LED AMARELO LIGADO\n");
        else if(gpio_get(LEDG)) printf("LED VERDE LIGADO\n");
    }
}