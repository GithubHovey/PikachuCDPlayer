/*------------------------------------------------------------------------------
 * @file    DEBUGMONITOR.H
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/05/21 16:06:42
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion  ------------------------------------*/
#ifndef __DEBUGMONITOR_H
#define __DEBUGMONITOR_H

/* Files includes  -----------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/
#define TIMEOUT_VAR 100
#define RX_BUFFSIZE 128
// typedef uint32_t (*usart_call_back)(uint8_t *buf, uint16_t len);
/* Variables -----------------------------------------------------------------*/
typedef struct
{
    UART_HandleTypeDef *huart;
    // usart_call_back callback_func;
    uint8_t rxbuff[RX_BUFFSIZE];
    uint16_t rxbuff_size;
}DebugMonitor;

void DebugMonitorInit(void);
int ReportData(uint8_t *txdata,uint16_t len);
void DebugMonitorCallback(void);
int ReportData2DebugMonitor(uint8_t *pdata,uint16_t len);


#endif
