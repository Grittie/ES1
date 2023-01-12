#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"

int LED_R = 17;
int LED_Y = 18;
int LED_G = 8;

int BUTTON_PIN = 15;
  
void app_main() {
    
    gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_Y, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    
    while (true)
    {
        if (gpio_get_level(BUTTON_PIN) == 1)
        {
            vTaskDelay(2000 / portTICK_PERIOD_MS);
   
            gpio_set_level(LED_R, 0);
            gpio_set_level(LED_Y, 0);        
            gpio_set_level(LED_G, 1);

            vTaskDelay(3000 / portTICK_PERIOD_MS);

            gpio_set_level(LED_R, 0);
            gpio_set_level(LED_Y, 1);        
            gpio_set_level(LED_G, 0);

            vTaskDelay(500 / portTICK_PERIOD_MS);

            gpio_set_level(LED_R, 1);
            gpio_set_level(LED_Y, 0);        
            gpio_set_level(LED_G, 0);

            vTaskDelay(500 / portTICK_PERIOD_MS);

        } else {
            gpio_set_level(LED_R, 1);
            gpio_set_level(LED_Y, 0);        
            gpio_set_level(LED_G, 0);   
        }
    }
}