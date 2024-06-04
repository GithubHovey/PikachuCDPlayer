/*------------------------------------------------------------------------------
 * @file    DFPLAYER.H
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/06/3 11:39:36
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion  ------------------------------------*/
#ifndef __CDPLAYER_H
#define __CDPLAYER_H
extern "C"
{
#include "Drivers/drivers.h" 
}
#define INITED  0
#define PLAYING 1
#define STOP    2
class CDplayer
{
private:
    /* data */
public:
    CDplayer(uint8_t __statu,uint8_t __volume,uint16_t __timeset):       //A初始化列表
      statu(__statu),
      volume(__volume),
      timeset(__timeset)
    {
    }
    uint8_t statu;
    uint8_t volume;
    bool tail_key;
    uint8_t cmd[2];
    uint16_t heartbeat;
    uint16_t timeset;
    int Init();
    int CDdetect();
    int Mp3Play();
    int CmdHandle();
    int VolumeCtr();
    bool tailkey_is_on();
    bool new_cmd_has_been_recived();
    void MotorCtr(uint8_t __switch);
    int Mp3EndPlay();
    bool is_CD_been_switched();
    //~CDplayer();
};

#endif