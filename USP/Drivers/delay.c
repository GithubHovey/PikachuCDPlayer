/*------------------------------------------------------------------------------
 * @file    DELAY.C
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/07/08 16:20:39
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/
#include "Drivers/delay.h"
/**
* @brief  
* @param  
* @return 
*/
void Delayms(unsigned short ms)
{
    HAL_Delay(ms);//HAL_delay会阻塞整个处理器，如果使用了RTOS则慎用。
}