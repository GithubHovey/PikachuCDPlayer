/*------------------------------------------------------------------------------
 * @file    SYS_SERVICE.CPP
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/04/30 17:50:53
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/
#include "Application/include/sys_init.h"
#include "Application/include/sys_internal.h"

TaskHandle_t debug_handle;
TaskHandle_t CD_handle;
TaskHandle_t volume_handle;
TaskHandle_t mp3_handle;
void TaskDebug(void *arg);
void TaskNtagDetect(void *arg);
void TaskVolumeCtrl(void *arg);
void TaskMp3(void *arg);
/**
* @brief  
* @param  
* @return 
*/
void AppInit()
{
	xTaskCreate(TaskDebug,"App.debug",Normal_Stack_Size, NULL, PriorityNormal,&debug_handle);
    xTaskCreate(TaskNtagDetect,"App.debug",Normal_Stack_Size, NULL, PriorityNormal,&CD_handle);
    xTaskCreate(TaskVolumeCtrl,"App.debug",Small_Stack_Size, NULL, PriorityNormal,&volume_handle);
    xTaskCreate(TaskMp3,"App.debug",Normal_Stack_Size, NULL, PriorityNormal,&mp3_handle);
}
/**
* @brief  
* @param  
* @return 
*/
void TaskNtagDetect(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
    for(;;){
        /* wait for next circle */
        vTaskDelayUntil(&xLastWakeTime_t, 10);         
        if(NtagDetect() == MI_OK)
        {
            
        }
    } 
}
/**
* @brief  
* @param  
* @return 
*/
void TaskDebug(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
	uint8_t tx_data[10];
    for(;;){
        /* wait for next circle */
        vTaskDelayUntil(&xLastWakeTime_t, 1000);
       // ReportData2DebugMonitor(tx_data,9);

    }
}
void TaskVolumeCtrl(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
    for(;;){
        /* wait for next circle */
        vTaskDelayUntil(&xLastWakeTime_t, 1000);
       // ReportData2DebugMonitor(tx_data,9);

    } 
}
void TaskMp3(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
    //PlayTargetVoice(0x01);
    for(;;){
        /* wait for next circle */
        vTaskDelayUntil(&xLastWakeTime_t, 1000);
       // ReportData2DebugMonitor(tx_data,9);

    } 
}