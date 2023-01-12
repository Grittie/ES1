#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

int LED[10] = {4, 5, 6, 7, 15, 16, 17, 18, 8, 3};
size_t array_size = sizeof(LED)/sizeof(LED[0]);

int num = 0;
// int waarde = 0b1111111111;
//              0b0000101010;

// gpio_set_level(led_1, waarde);
// gpio_set_level(led2, waarde >> 1);
// gpio_set_level(led3, waarde >> 1);
// gpio_set_level(led4, waarde >> 2);
// gpio_set_level(led5, waarde >> 3);



  
void app_main() {
    for (size_t i = 0; i < array_size; i++)
    {
        gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
    }
    
    while (true)
    {           
        for (size_t i = 0; i < array_size; i++)
        {
            gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
            gpio_set_level(LED[i], num >> i & 1);
            vTaskDelay(50 / portTICK_PERIOD_MS); // 1000 milliseconde = 1 seconde
        }
        num++;
    }
}