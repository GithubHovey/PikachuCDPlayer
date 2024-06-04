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
CDplayer pikachu_player(0,0x10,100);
TaskHandle_t debug_handle;
TaskHandle_t ntag_handle;
TaskHandle_t volume_handle;
TaskHandle_t mp3_handle;
TaskHandle_t pikachu_handle;
void TaskDebug(void *arg);
void TaskNtagDetect(void *arg);
void TaskVolumeCtrl(void *arg);
void TaskMp3(void *arg);
void TaskCDplayer(void *arg);
/**
* @brief  
* @param  
* @return 
*/
void AppInit()
{
	xTaskCreate(TaskDebug,"App.debug",Normal_Stack_Size, NULL, PriorityNormal,&debug_handle);
    xTaskCreate(TaskNtagDetect,"App.ntagdetect",Normal_Stack_Size, NULL, PriorityNormal,&ntag_handle);
    xTaskCreate(TaskVolumeCtrl,"App.volumecontrol",Small_Stack_Size, NULL, PriorityNormal,&volume_handle);
    xTaskCreate(TaskMp3,"App.mp3",Normal_Stack_Size, NULL, PriorityNormal,&mp3_handle);
    xTaskCreate(TaskCDplayer,"App.pikachuCDplay",Normal_Stack_Size, NULL, PriorityNormal,&pikachu_handle);
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
void TaskCDplayer(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
    //PlayTargetVoice(0x01);
    for(;;){
        /* wait for next circle */
        vTaskDelayUntil(&xLastWakeTime_t, 10);
        switch (pikachu_player.statu)
        {
        case INITED:
            if(pikachu_player.tailkey_is_on() && pikachu_player.new_cmd_has_been_recived())
            {
                pikachu_player.Mp3Play();
                pikachu_player.MotorCtr(1);
            }
            break;
        case PLAYING:
            if(!pikachu_player.tailkey_is_on())//开关断开则结束播放
            {
                pikachu_player.Mp3EndPlay();
                break;
            }else
            {
                
                if(pikachu_player.new_cmd_has_been_recived())
                {
                    pikachu_player.heartbeat = pikachu_player.timeset;
                    if(pikachu_player.is_CD_been_switched())
                    {
                        pikachu_player.Mp3Play();
                    }
                }
                pikachu_player.heartbeat--;    
            }
            /* code */
            break;
        case STOP:
            if(!pikachu_player.tailkey_is_on())//开关断开则结束播放
            {
                pikachu_player.Mp3EndPlay();
                break;
            }
            break;
        
        default:
            break;
        }

    } 
}