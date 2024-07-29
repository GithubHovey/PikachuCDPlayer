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
TaskHandle_t ntag_handle;
TaskHandle_t volume_handle;
TaskHandle_t mp3_handle;
QueueHandle_t MP3_TxPort;

// TaskHandle_t pikachu_handle;
void TaskDebug(void *arg);
void TaskNtagDetect(void *arg);
void TaskVolumeCtrl(void *arg);
void TaskMp3(void *arg);
// void TaskCDplayer(void *arg);
/**
* @brief  
* @param  
* @return 
*/
void AppInit()
{
		// xTaskCreate(TaskDebug,"App.debug",Normal_Stack_Size, NULL, PriorityNormal,&debug_handle);
		MP3_TxPort = xQueueCreate(4, sizeof(MP3COMMAND));
		xTaskCreate(TaskMp3,"App.mp3",Small_Stack_Size, NULL, PriorityHigh,&mp3_handle);
		xTaskCreate(TaskNtagDetect,"App.ntagdetect",Small_Stack_Size, NULL, PriorityNormal,&ntag_handle);
		xTaskCreate(TaskVolumeCtrl,"App.volumecontrol",Small_Stack_Size, NULL, PriorityNormal,&volume_handle);		   
    //xTaskCreate(TaskCDplayer,"App.pikachuCDplay",Normal_Stack_Size, NULL, PriorityNormal,&pikachu_handle);
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
    static MP3COMMAND MP3TxMsg;
    for(;;){
        /* wait for next circle */
        vTaskDelayUntil(&xLastWakeTime_t, 15);          
        if(pikachu_player.CDdetect(MP3TxMsg))
        {
            xQueueSend(MP3_TxPort,&MP3TxMsg,0); 
						xQueueSend(MP3_TxPort,&MP3TxMsg,0);
						xQueueSend(MP3_TxPort,&MP3TxMsg,0);//连发三条，降低tf卡读取失败的概率
        }
    } 
}
void TaskMp3(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
    static MP3COMMAND MP3Msg;
    //PlayTargetVoice(0x01);
    for(;;){
        /* wait for next circle */
        if(xQueueReceive(MP3_TxPort,&MP3Msg,portMAX_DELAY) == pdPASS)
        {
            pikachu_player.MP3ctrl(MP3Msg); //解包发送
            vTaskDelay(50);
        }
    } 
}
void TaskVolumeCtrl(void *arg)
{
    /* Pre-Load for task */
    TickType_t xLastWakeTime_t;
    xLastWakeTime_t = xTaskGetTickCount();
    static MP3COMMAND MP3TxMsg;
    for(;;){
        /* wait for next circle */	
        vTaskDelayUntil(&xLastWakeTime_t, 300);
        MP3TxMsg = 	pikachu_player.GetVolume();		
        xQueueSend(MP3_TxPort,&MP3TxMsg,0); 
       // ReportData2DebugMonitor(tx_data,9);

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
		//VolumeCtrl(0x06);
    for(;;){
        /* wait for next circle */
        //test motor:
        //test mp3:
        //test adc:
        // HAL_GPIO_WritePin(MOTOR_POWER_CTL_GPIO_Port,MOTOR_POWER_CTL_Pin,GPIO_PIN_SET);
		//PlayTargetVoice(0x01);
        vTaskDelayUntil(&xLastWakeTime_t, 1000);
       // ReportData2DebugMonitor(tx_data,9);

    }
}


// void TaskCDplayer(void *arg)
// {
//     /* Pre-Load for task */
//     TickType_t xLastWakeTime_t;
//     xLastWakeTime_t = xTaskGetTickCount();
//     for (;;)
//     {
//     }
    
//     /*
//     for(;;){
//         vTaskDelayUntil(&xLastWakeTime_t, 10);
//         switch (pikachu_player.statu)
//         {
//         case INITED:
//             if(pikachu_player.tailkey_is_on() && pikachu_player.new_cmd_has_been_recived())
//             {
//                 pikachu_player.Mp3Play();
//                 pikachu_player.MotorCtr(1);
//             }
//             break;
//         case PLAYING:
//             if(!pikachu_player.tailkey_is_on())//开关断开则结束播放
//             {
//                 pikachu_player.Mp3EndPlay();
//                 break;
//             }else
//             {
                
//                 if(pikachu_player.new_cmd_has_been_recived())
//                 {
//                     pikachu_player.heartbeat = pikachu_player.timeset;
//                     if(pikachu_player.is_CD_been_switched())
//                     {
//                         pikachu_player.Mp3Play();
//                     }
//                 }
//                 pikachu_player.heartbeat--;    
//             }
//             break;
//         case STOP:
//             if(!pikachu_player.tailkey_is_on())//开关断开则结束播放
//             {
//                 pikachu_player.Mp3EndPlay();
//                 break;
//             }
//             break;
        
//         default:
//             break;
//         }

//     } 
//     */
// }