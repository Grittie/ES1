#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
  
#define LED_PIN 2
  
void app_main() {
    while (true)
    {
        gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
    }
} 