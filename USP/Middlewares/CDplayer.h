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
//#define MOTOR_FAST 50
// MOTOR_SLOW 40
#define MOTOR_OFF 0


struct MP3COMMAND
{
  uint8_t cmd_type;
  uint8_t cmd_data1;
  uint8_t cmd_data2;
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
    MP3COMMAND mp3cmd;
    MP3COMMAND endplaycmd;
    MP3COMMAND GetVolume();
    // bool tail_key;
    // uint8_t cmd[2];
    uint8_t ntagdata[16];
		uint8_t current_CD;
    uint16_t heartbeat;
    uint16_t timeset;
		uint16_t speed;
		uint8_t test;
    
    // bool cmd_wait_for_handle;
    // void Mp3Play();
    // int ReadCDdata();
    // bool new_cmd_has_been_recived();
    // int Mp3EndPlay();

    int Init();
    int CDdetect(MP3COMMAND& _mp3cmd);
    bool tailkey_is_on();    
    void MotorCtr(uint16_t _speed);  
    // bool is_CD_been_switched();
    void Update();
    void SystemNotify();
    void MP3ctrl(MP3COMMAND _cmd);
    void ErrorHandler(uint8_t err_code);
    int UnpackNtagMsg(MP3COMMAND& _mp3cmd);
    
};

#endif