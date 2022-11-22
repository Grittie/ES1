#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <time.h>
#include <stdlib.h>
  
#define LED_PIN 2
  
void app_main() {
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    while (true)
    {
        int r = rand() % 1000;

        gpio_set_level(LED_PIN, 1);
        vTaskDelay(r / portTICK_PERIOD_MS);
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(r / portTICK_PERIOD_MS);
    }
} 