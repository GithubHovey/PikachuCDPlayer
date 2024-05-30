/*------------------------------------------------------------------------------
 * @file    DFPLAYER.H
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/05/20 11:39:36
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion  ------------------------------------*/
#ifndef __DFPLAYER_H
#define __DFPLAYER_H

/* Files includes  -----------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/
#define SINGLE_CYCLE 0x08
#define FOLDER_ CYCLE 0x17
#define SELECT_FOLDER 0x0f

#define NEED_ACK 0x01
#define NO_ACK 0X00
typedef struct
{
    UART_HandleTypeDef *huart;
    // usart_call_back callback_func;
    uint8_t rxbuff[10];
    uint16_t rxbuff_size;
}DFplayer;

/* Variables -----------------------------------------------------------------*/


/* Functions ----------------------------------------------------------------*/
//int SendCMD(uint8_t cmd,uint8_t data1,uint8_t data2,uint8_t return_flag);
void DFplayerInit(void);
int PlayFavourList(void);
int PlayTargetVoice(uint8_t id);
int VolumeCtrl(uint8_t var);
int DFplayerCallback(void);
#endif
