// De bedoeling van dit programma is om met een LED bar en een 7 segment display het spel pong te spelen.
// @date 12/1/23
// @author Lars Grit
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "SevSeg.h"
#define BUF_SIZE (1024)

// Variables to define GPIO pins
int LED[10] = {38, 37, 36, 35, 2, 45, 48, 47, 1, 21};
int led_length = 10;
int BUTTON_LEFT = 42;
int BUTTON_RIGHT = 41;

uint8_t numDigits = 4;
uint8_t digitPins[] = {8, 3, 46, 9};
uint8_t segmentPins[] = {4, 5, 6, 7, 15, 16, 17, 18};

// Variables for the game logic_
int count = 0;
int hit_state = 0;
int is_button_pressed = 0;

// Variables for the points 
int points_left = 0;
int points_right = 0;
int scoreboard = 0000;

// Variables that define the ammount of points needed and the speed of the game in MS
int rounds = 5;
int led_delay_length = 50;

void uart_config() {
    // Uart configuration logic
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void app_main() {
    // Set GPIO Direction for buttons and leds
    gpio_set_direction(BUTTON_LEFT, GPIO_MODE_INPUT);
    gpio_set_direction(BUTTON_RIGHT, GPIO_MODE_INPUT);

    // 7 seg
    sevseg_begin(numDigits, digitPins, segmentPins);
    sevseg_setNumber(scoreboard, -1, false);

    for (size_t i = 0; i <= led_length; i++)
    {
        gpio_set_direction(LED[i], GPIO_MODE_OUTPUT);
    }
    
    while (true)
    {
        for (int i = 0; i < led_length; i++) {
            gpio_set_level(LED[i], 1);
            vTaskDelay(led_delay_length / portTICK_PERIOD_MS);
            gpio_set_level(LED[i], 0 << i);
            vTaskDelay(led_delay_length / portTICK_PERIOD_MS);
            
            count++;

            if (gpio_get_level(BUTTON_RIGHT) == 1 && is_button_pressed == 0)
            {
                is_button_pressed = 1;

                vTaskDelay(led_delay_length / portTICK_PERIOD_MS);

                if (count == 9)
                {
                    uart_write_bytes(UART_NUM_0, "pong ", 5);
                    hit_state = 1;   
                } else {
                    uart_write_bytes(UART_NUM_0, "miss ", 5);
                }
            }
        }

        if (hit_state == 0)
        {
            uart_write_bytes(UART_NUM_0, "Point for left!\n", 17);
            points_left++;
            
            scoreboard = scoreboard + 100;
            sevseg_setNumber(scoreboard, -1, false);

            hit_state = 0;
            is_button_pressed = 0;

            if (points_left >= rounds)
            {
                vTaskDelay(1000 / portTICK_PERIOD_MS);
                uart_write_bytes(UART_NUM_0, "Left wins!\n", 12);
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                uart_write_bytes(UART_NUM_0, "Resetting score!\n", 18);

                points_right = 0;
                points_left = 0;

                scoreboard = 0000;
                sevseg_setNumber(scoreboard, -1, false);
            }

            vTaskDelay(1000 / portTICK_PERIOD_MS); 
        } else {
            uart_write_bytes(UART_NUM_0, "continue\n", 10); 
            hit_state = 0;
            is_button_pressed = 0;
        }
        

        for (int i = 0; i < led_length; i++) {
            gpio_set_level(LED[count], 1);
            vTaskDelay(led_delay_length / portTICK_PERIOD_MS);
            gpio_set_level(LED[count], 0 << i);
            vTaskDelay(led_delay_length / portTICK_PERIOD_MS);

            count--;    

            if (gpio_get_level(BUTTON_LEFT) == 1 && is_button_pressed == 0)
            {
                is_button_pressed = 1;
                vTaskDelay(led_delay_length / portTICK_PERIOD_MS);

                if (count == 0)
                {
                    uart_write_bytes(UART_NUM_0, "pong ", 5);
                    hit_state = 1;   
                } else {
                    uart_write_bytes(UART_NUM_0, "miss ", 5);
                }
            }
        }

        if (hit_state == 0)
        {
            uart_write_bytes(UART_NUM_0, "Point for right!\n", 18);
            points_right++;

            scoreboard = scoreboard + 1;
            sevseg_setNumber(scoreboard, -1, false);


            hit_state = 0;
            is_button_pressed = 0;

            if (points_right >= rounds)
            {
                uart_write_bytes(UART_NUM_0, "Right wins!\n", 13);
                vTaskDelay(500 / portTICK_PERIOD_MS);
                uart_write_bytes(UART_NUM_0, "Resetting score!\n", 18);

                points_right = 0;
                points_left = 0;

                scoreboard = 0000;
                sevseg_setNumber(scoreboard, -1, false);
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        } else {
            uart_write_bytes(UART_NUM_0, "continue\n", 10); 
            hit_state = 0;
            is_button_pressed = 0;
        }
    }
}