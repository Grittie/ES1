#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#define UART_NUM UART_NUM_0 // Use UART0 for this example

int LED_R = 17;
int LED_Y = 18;
int LED_G = 8;

void uart_task(void *pvParameters)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, 1024, 0, 0, NULL, 0);

    gpio_set_direction(LED_R, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_Y, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);

    // Read input in a loop
    while (1) {
        uint8_t data[64];
        int length = uart_read_bytes(UART_NUM, data, sizeof(data), 20 / portTICK_RATE_MS);
        if (length > 0) {
            // Check if the received data is "1"
            if (data[0] == '1') {
                uart_write_bytes(UART_NUM, "R1\n", 4);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                gpio_set_level(LED_R, 1);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }

            if (data[0] == '2') {
                uart_write_bytes(UART_NUM, "Y1\n", 4);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                gpio_set_level(LED_Y, 1);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }

            if (data[0] == '3') {
                uart_write_bytes(UART_NUM, "G1\n", 4);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                gpio_set_level(LED_G, 1);
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
        }
    }
}

void app_main()
{
    xTaskCreate(uart_task, "uart_task", 1024, NULL, 5, NULL);
}
