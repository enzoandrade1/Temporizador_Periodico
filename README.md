# Simulação de Semáforo com Raspberry Pi Pico W

## Descrição
Este projeto implementa um semáforo utilizando um **Raspberry Pi Pico W**, onde três LEDs (vermelho, amarelo e verde) alternam automaticamente a cada **3 segundos**. O temporizador periódico é gerenciado pela função `add_repeating_timer_ms()` do **Pico SDK**.

Além disso, o programa imprime no terminal, via **porta serial**, o estado atual do semáforo a cada **1 segundo**.

## Requisitos
- **Hardware**:
  - Raspberry Pi Pico W
  - 3 LEDs (vermelho, amarelo e verde)

- **Software**:
  - Pico SDK instalado
  - Compilador ARM GCC

## Ligação dos LEDs
Os LEDs estão conectados aos seguintes **GPIOs**:

| LED       | GPIO |
|-----------|------|
| Vermelho  | 11   |
| Amarelo   | 12   |
| Verde     | 13   |

Cada LED está em série com um resistor de **330Ω** para limitar a corrente.

## Funcionamento
1. O programa inicia com o LED **vermelho** aceso.
2. A cada **3 segundos**, a cor muda na seguinte sequência:
   - **Vermelho** → **Amarelo** → **Verde** → **Vermelho** (loop)
3. O estado do LED é impresso no terminal **a cada 1 segundo**.

## Código Principal
O temporizador é configurado da seguinte forma:

```c
add_repeating_timer_ms(3000, timer_callback, NULL, &timer);
```
Isso garante que a função `timer_callback()` seja chamada a cada **3 segundos**, alternando os LEDs.

No loop principal (`while(true)`), a seguinte lógica é utilizada para imprimir o estado atual do LED a cada **1 segundo**:
```c

while(true) {
    sleep_ms(1000);
    if(gpio_get(LEDR)) printf("LED VERMELHO LIGADO\n");
    else if(gpio_get(LEDY)) printf("LED AMARELO LIGADO\n");
    else if(gpio_get(LEDG)) printf("LED VERDE LIGADO\n");
}
```
## Autor
Desenvolvido por Enzo Andrade Sousa Santos.

