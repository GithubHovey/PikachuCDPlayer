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

#define CD_OK     0
#define CD_ERROR  -1
#define MOTOR_ON 1
#define MOTOR_OFF 0
struct MP3COMMAND
{
  uint8_t cmd_type;
  uint8_t cmd_data;
};

class CDplayer
{
private:
    /* data */
public:
    CDplayer(uint8_t __volume,uint16_t __timeset):       //A初始化列表
      volume(__volume),
      timeset(__timeset)
    {
    }
    ~CDplayer(){} 
    uint32_t volume;
    // uint8_t statu;
    MP3COMMAND _ntagcmd;
    MP3COMMAND endplaycmd;
    MP3COMMAND GetVolume();
    // bool tail_key;
    // uint8_t cmd[2];
    uint8_t ntagdata[16];
    uint16_t heartbeat;
    uint16_t timeset;
    uint8_t current_CD;
    // bool cmd_wait_for_handle;
    // void Mp3Play();
    // int ReadCDdata();
    // bool new_cmd_has_been_recived();
    // int Mp3EndPlay();

    int Init();
    int CDdetect(MP3COMMAND* _mp3cmd);
    bool tailkey_is_on();    
    void MotorCtr(uint8_t __switch);    
    // bool is_CD_been_switched();
    void Update();
    void SystemNotify();
    void MP3ctrl(MP3COMMAND _cmd);
    void ErrorHandler(uint8_t err_code);
    MP3COMMAND* UnpackNtagMsg();
    
};

#endif