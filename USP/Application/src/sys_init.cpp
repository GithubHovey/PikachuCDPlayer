/*------------------------------------------------------------------------------
 * @file    SYS_INIT.CPP
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/04/29 19:03:48
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 

------------------------------------------------------------------------------*/

#include "Application/include/sys_init.h"
#include "Application/include/sys_internal.h"
/**
* @brief  
* @param  
* @return 
*/
static void TaskInit()
{
	AppInit();
}
/**
* @brief  
* @param  
* @return 
*/
static void DeviceInit()
{
		DFplayerInit();
    DebugMonitorInit();
    RFID_Init();
}
/**
* @brief  
* @param  
* @return 
*/
void SysInit()
{
    DeviceInit();
    TaskInit();
}
