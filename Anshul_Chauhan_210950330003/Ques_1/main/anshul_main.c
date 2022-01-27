#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t handle_queue;

void Task_1(void *pvParameters)
{
    while(1)
    {
        printf("Task_1: Priority = 5: Periodicity = 1000\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void Task_2(void *pvParameters)
{
    while(1)
    {
        printf("Task_2: Priority = 6: Periodicity = 2000\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void Task_3(void *pvParameters)
{
    while(1)
    {
        printf("Task_3: Priority = 7: Periodicity = 5000\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void Task_4(void *pvParameters)
{
    int temp_send = 1;
    while(1)
    {
        printf("Task_4: Priority = 8\n");
        printf("Sent Data: positive integer: %d\n", temp_send);
        xQueueSend(handle_queue, &temp_send, portMAX_DELAY);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        temp_send++;
    }
}

void Task_5(void *pvParameters)
{
    int temp_recv;
    while(1)
    {
        xQueueReceive(handle_queue, &temp_recv, portMAX_DELAY);
        printf("Task_5: Priority = 9\n");
        printf("Received Data: Positive integer: %d\n", temp_recv + 273);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    handle_queue = xQueueCreate(7, sizeof(int));
    xTaskCreate(Task_1, "Task_1", 1024, NULL, 5, NULL);
    xTaskCreate(Task_2, "Task_2", 1024, NULL, 6, NULL);
    xTaskCreate(Task_3, "Task_3", 1024, NULL, 7, NULL);
    xTaskCreate(Task_4, "Task_4", 2048, NULL, 8, NULL);
    xTaskCreate(Task_5, "Task_5", 2048, NULL, 9, NULL);

    printf("Main Task\n");             
}