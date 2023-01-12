#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
  
#define LED_PIN 37
#define LED_PIN2 36
#define LED_PIN3 38

#define BUTTON_PIN 40
#define BUTTON_PIN2 41
#define BUTTON_PIN3 42

  
void app_main() {
    while (true)
    {
        gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
        gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);

        if(gpio_get_level(BUTTON_PIN) == 1) {
            gpio_set_level(LED_PIN, 1);
        } else {
            gpio_set_level(LED_PIN, 0);
        }

        vTaskDelay(1);
    }
} 