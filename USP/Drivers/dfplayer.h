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
#define SYSTEM_VOICE_FOLDER 0X03
#define FAVOR_FOLDER        0X02
#define CD_FOLDER           0X01

/*-----------MP3-CMD-------------------*/
// #define SINGLE_CYCLE    0x08
#define FOLDER_CIRCLE   0x17    //循环播放指定文件夹歌曲
#define SELECT_FOLDER   0x0f    //选择指定文件夹的歌曲播放 如01文件夹下的001.mp3
#define STOP_PLAY       0x0e
#define CONTINUE_PLAY   0x0d
#define END_PLAY        0x16

#define PLAY_MODE_SET   0x19    //播放模式设置
#define SINGLE          0X01    //只播放一次
#define SINGLE_CIRCLE   0X00    //单曲循环

#define VOLUMESET       0X06    // 0~30 音量控制，初始为30
#define STATU_UPDATE    0X42    //状态查询 00：停止 02：暂停 01：正在播放

#define NEED_ACK 0x01
#define NO_ACK 0X00
/*----------ACK----------*/
#define ERROR_MSG       0X40
#define STATUS_MSG      0x42
#define MP3RUNNING         0X01
#define MP3STOP            0X02
#define MP3END             0X00
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
int StopPlay();
int EndPlay();
int ContinuePlay();
int UpdateStatus();
#endif
