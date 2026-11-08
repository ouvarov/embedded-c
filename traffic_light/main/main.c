#include <stdbool.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_RED GPIO_NUM_25
#define LED_YELLOW GPIO_NUM_26
#define LED_GREEN GPIO_NUM_27
#define BUTTON GPIO_NUM_33

const gpio_num_t LEDS[] = {LED_RED, LED_YELLOW, LED_GREEN};
const int LED_COUNT = sizeof(LEDS) / sizeof(LEDS[0]);

const gpio_num_t SEQUENCE[] = {LED_RED, LED_YELLOW, LED_GREEN, LED_YELLOW};
const int SEQUENCE_COUNT = sizeof(SEQUENCE) / sizeof(SEQUENCE[0]);

bool wait_or_button(int duration_ms)
{
    for (int elapsed = 0; elapsed < duration_ms; elapsed += 10) {
        if (gpio_get_level(BUTTON) == 0) {
            return true;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    return false;
}

void app_main(void)
{
    int x = 0;

    gpio_reset_pin(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    for (int i = 0; i < LED_COUNT; i++) {
        gpio_reset_pin(LEDS[i]);
        gpio_set_direction(LEDS[i], GPIO_MODE_OUTPUT);
    }

    while (1) {
        gpio_set_level(SEQUENCE[x], 1);

        if (SEQUENCE[x] == LED_GREEN) {
          vTaskDelay(pdMS_TO_TICKS(1000));
          wait_or_button(2000);
        } else if (x % 2 == 0) {
            vTaskDelay(pdMS_TO_TICKS(6000));
        } else {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        gpio_set_level(SEQUENCE[x], 0);

        x++;
        if (x == SEQUENCE_COUNT) {
            x = 0;
        }
    }
}
