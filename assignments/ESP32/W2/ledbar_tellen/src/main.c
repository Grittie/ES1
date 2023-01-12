#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

int LED[10] = {4, 5, 6, 7, 15, 16, 17, 18, 8, 3};
int BUTTON[2] = {9, 11};

size_t led_array_size = sizeof(LED)/sizeof(LED[0]);

uint16_t num = 0;
  
void app_main() {
    gpio_set_direction(BUTTON[0], GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON[1], GPIO_MODE_INPUT);

    while (true)
    {

        if (gpio_get_level(BUTTON[0]) == 1) { 
            num++;
        }

        if (gpio_get_level(BUTTON[1]) == 1) { 
            num--;
        }

        for (size_t i = 0; i < led_array_size; i++)
        {
            gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
            gpio_set_level(LED[i], num >> i & 1);
            vTaskDelay(50 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
        }
        

        printf("button 1 = %d\n", gpio_get_level(BUTTON[0]));
        printf("button 2 = %f\n", gpio_get_level(BUTTON[1]));
        vTaskDelay(1);
    }
}