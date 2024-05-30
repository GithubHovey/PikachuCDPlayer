/*------------------------------------------------------------------------------
 * @file    DEBUGMONITOR.CPP
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/05/21 16:06:03
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/
#include "Drivers/debugmonitor.h"
#include "usart.h"
DebugMonitor uppermonitor = {
    .huart = &huart1
};

int ReportData(uint8_t *txdata,uint16_t len)
{
    if(HAL_UART_Transmit_DMA(uppermonitor.huart,txdata,len)!=HAL_OK)
        return -1;
    else
        return 0;
}
void DebugMonitorInit(void)
{
    HAL_UART_Receive_IT(uppermonitor.huart,uppermonitor.rxbuff,1);
    __HAL_UART_ENABLE_IT(uppermonitor.huart,UART_IT_IDLE);
}
void DebugMonitorCallback(void)
{
    if(__HAL_UART_GET_FLAG(uppermonitor.huart,UART_FLAG_IDLE)!=RESET)
	{
		/* clear idle it flag avoid idle interrupt all the time */
        __HAL_UART_CLEAR_IDLEFLAG(uppermonitor.huart);
        /* clear DMA transfer complete flag */
        HAL_UART_DMAStop(uppermonitor.huart);

/*-----------------------user code -----------------*/
       // HAL_UART_Transmit_DMA(uppermonitor.huart,uppermonitor.rxbuff,7);
/*-----------------------user code -----------------*/

        HAL_UART_Receive_DMA(uppermonitor.huart,uppermonitor.rxbuff, uppermonitor.rxbuff_size);
	}

}
/**
* @brief  
* @param  
* @return 
*/
int ReportData2DebugMonitor(uint8_t *pdata,uint16_t len)
{
    if(HAL_UART_Transmit_DMA(uppermonitor.huart,pdata,len)!=HAL_OK)
        return -1;
    else
        return 0;
}
