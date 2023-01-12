#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#define POT_CHANNEL ADC1_CHANNEL_0

int LED[10] = {13, 12, 11, 10, 9, 46, 3, 8, 18, 17};
int array_size = 11;

int num = 0;
  
void app_main() {
    while (true)
    {         
            // Initialize the ADC and LED GPIO
        adc1_config_width(ADC_WIDTH_12Bit);
        adc1_config_channel_atten(POT_CHANNEL, ADC_ATTEN_DB_11);


        for (size_t i = 0; i < array_size; i++)
        {
            int pot_value = adc1_get_raw(POT_CHANNEL);

            // Map the potentiometer value to a delay range
            int delay = map(pot_value, 0, 4095, 100, 1000);

            gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
            gpio_set_level(LED[i], num >> 1);
            vTaskDelay(delay / portTICK_PERIOD_MS);
            num++;
        }
    }
}