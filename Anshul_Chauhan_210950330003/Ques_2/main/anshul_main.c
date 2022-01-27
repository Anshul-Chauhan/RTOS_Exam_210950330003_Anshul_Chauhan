/*Ques_2: Create 3 realtime tasks each with the periodicity T1 = 1000ms, T2 = 2000ms, T3 = 5000ms.
    Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.*/

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>

TimerHandle_t handle_timer;

void Timer_Callback(TimerHandle_t xTimer)
{
    printf("This is the callback function of a one-shot software timer triggered from the task 'Task_3'.\n");
}

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
    int count = 0;
    while(1)
    {
        printf("T3: Priority = 7: Periodicity = 5000\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        count++;
        if(count == 2)
            xTimerStart(handle_timer, 0);  // triggering a callback function from task T3 after 10000ms
    }
}

void app_main()
{
    // creating a oneshot software timer
    handle_timer = xTimerCreate("Timer", pdMS_TO_TICKS(2000), pdFALSE, NULL, Timer_Callback);
    xTaskCreate(T1, "T1", 1024, NULL, 5, NULL);
    xTaskCreate(T2, "T2", 1024, NULL, 6, NULL);
    xTaskCreate(T3, "T3", 2048, NULL, 7, NULL);
    
    int i = 0;
    while(1)
    {
        printf("%d000 ms\n\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        i++;        
    }             
}