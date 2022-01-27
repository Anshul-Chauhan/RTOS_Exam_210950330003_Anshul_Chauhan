/*Ques_1: Create 3 realtime tasks each with the periodicity T1 = 1000ms, T2 = 2000ms, T3 = 5000ms.
    Also create two additional task T4 and T5 where T4 sends integer data to T5 using Message Queues.*/    

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

QueueHandle_t handle_queue;

void T1(void *pvParameters)
{
    while(1)
    {
        printf("T1: Priority = 5: Periodicity = 1000\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void T2(void *pvParameters)
{
    while(1)
    {
        printf("T2: Priority = 6: Periodicity = 2000\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void T3(void *pvParameters)
{
    while(1)
    {
        printf("T3: Priority = 7: Periodicity = 5000\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void T4(void *pvParameters)
{
    int temp_send = 1;
    while(1)
    {
        printf("T4: Priority = 8\n");
        printf("Sent Data: Positive integer: %d\n", temp_send);
        xQueueSend(handle_queue, &temp_send, portMAX_DELAY);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        temp_send++;
    }
}

void T5(void *pvParameters)
{
    int temp_recv;
    while(1)
    {
        xQueueReceive(handle_queue, &temp_recv, portMAX_DELAY);
        printf("T5: Priority = 9\n");
        printf("Received Data: Positive integer: %d\n", temp_recv);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
    handle_queue = xQueueCreate(7, sizeof(int)); // creating a message queue
    xTaskCreate(T1, "T1", 1024, NULL, 5, NULL);
    xTaskCreate(T2, "T2", 1024, NULL, 6, NULL);
    xTaskCreate(T3, "T3", 1024, NULL, 7, NULL);
    xTaskCreate(T4, "T4", 2048, NULL, 8, NULL);
    xTaskCreate(T5, "T5", 2048, NULL, 9, NULL);

    int i = 0;
    while(1)
    {
        printf("%d000 ms\n\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        i++;        
    }                
}