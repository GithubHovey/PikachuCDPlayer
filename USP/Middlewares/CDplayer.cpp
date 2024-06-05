#include "Middlewares/CDplayer.h"
int CDplayer::Init()
{
    return 0;
}
/**
* @brief ntag检测函数  
* @param  none
* @return 0：成功 -1：失败
*/
int CDplayer::CDdetect()
{
    if(NtagDetect()!=MI_OK)
    {
        return -1;
    }else
    {
        return 0;
    }
}
/**
* @brief mp3播放音乐  
* @param  
* @return 
*/
void CDplayer::Mp3Play()
{
    if(cmd[0]=0x0f)
    {
        PlayTargetVoice(cmd[1]);
    }
    if(cmd[0]=0x17)
    {   
        PlayFavourList();
    }
}
/**
* @brief  解析检测到CD的信息
* @param  
* @return 
*/
int CDplayer::ReadCDdata()
{
    if(ReadNtagMsg(cmd)==0);
    {
        cmd_wait_for_handle = 1;
        //current_CD = cmd[1]; //00:循环歌单 其他：歌曲序号
        return CD_OK;
    }else{
        return CD_ERROR;
    }
}
void CDplayer::VolumeCtr(uint8_t _var)
{
    VolumeCtrl(_var);
    return 0;
}
bool CDplayer::tailkey_is_on()
{
    if(1)
    return 1;
    if(0)
    {
        cmd_wait_for_handle = 0;
        return 0;
    }
}
/**
* @brief  检查当前解析的曲目与当前播放的曲目是否一致
* @param  
* @return 1：
*/
bool CDplayer::new_cmd_has_been_recived()
{  
    bool recived = cmd_wait_for_handle;
    cmd_wait_for_handle = 0;
    return recived;
}
void CDplayer::MotorCtr(uint8_t __switch)
{

}
int CDplayer::Mp3EndPlay()
{
    heartbeat = timeset;
    cmd_wait_for_handle = 0;
    return 0;
}
bool CDplayer::is_CD_been_switched()
{
    if(cmd[1]==current_CD)
    {
        return 0;
    }else{
        return 1;
    }
}
void CDplayer::SystemNotify()
{
    SystemNotify(0x01);//播放03目录第一首
}
void Update()
{
    statu = MP3_Unpack();
    if(statu == -1)
    {
        //抛出异常
    }
}