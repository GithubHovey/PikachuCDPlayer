#include "Middlewares/CDplayer.h"
#include "adc.h"

int CDplayer::Init()
{
	HAL_ADC_Start_DMA(&hadc1, &volume, 1);
    DFplayerInit();
    RFID_Init();    
    return 0;
}
/**
* @brief  获取音量
* @param  
* @return 
*/
MP3COMMAND CDplayer::GetVolume()
{
    struct MP3COMMAND vcmd;
    vcmd.cmd_type = VOLUMESET;
    if(volume>4000) //高死区
    {
        vcmd.cmd_data = 30;
    }
    else if(volume<=400) //低死区
    {
        vcmd.cmd_data = 0;
    }
    else{
        vcmd.cmd_data = (uint8_t)((volume-400)/120); //每120一级音量
    }
    return vcmd;
}
/**
* @brief  
* @param  
* @return 
*/

MP3COMMAND* CDplayer::UnpackNtagMsg()
{
    
    if(ntagdata[2]==0x30&&ntagdata[3]==0x31)
    {
        /*其余两位均为数字*/
        if((ntagdata[4]-0x30)>=0 && (ntagdata[4]-0x30)<=9 && (ntagdata[5]-0x30)>=0 && (ntagdata[5]-0x30)<=9)
        {
            _ntagcmd.cmd_type = SELECT_FOLDER;
            _ntagcmd.cmd_data = (ntagdata[4]-0x30)*10 + (ntagdata[5]-0x30);
            return &_ntagcmd;
        }
    }
    if(ntagdata[2]==0x6c&&ntagdata[3]==0x69&&ntagdata[4]==0x73&&ntagdata[5]==0x74)
    {
        _ntagcmd.cmd_type = FOLDER_CIRCLE;
        _ntagcmd.cmd_data = 0xff;
        return &_ntagcmd;
    }
    return NULL;
}
/**
* @brief ntag检测函数  
* @param  none
* @return 0：成功 -1：失败
*/
int CDplayer::CDdetect(MP3COMMAND* _mp3cmd)
{
    if(tailkey_is_on())
    {
        MotorCtr(MOTOR_ON);
        if(NtagDetect(ntagdata)==MI_OK)
        { 
            _mp3cmd = UnpackNtagMsg();
            if(_mp3cmd != NULL)
            {
                heartbeat = timeset;
                if((current_CD != _mp3cmd->cmd_data)&&(tailkey_is_on()))
                {
                    current_CD = _mp3cmd->cmd_data;
                    // cmd_list.push(*ntagcmd);
                    return 1;
                }            
            }
        }
    }else{
        heartbeat = 0;
    }


    if(heartbeat<=0)
    {
        MotorCtr(MOTOR_OFF);
        _mp3cmd = &endplaycmd;
        endplaycmd.cmd_type = END_PLAY;
        current_CD = 0;
        //cmd_list.push(endplay);
        return 1;    
    }
    else{
        heartbeat--;
    }
    return 0; 
}

/**
* @brief  解析检测到CD的信息
* @param  
* @return 
*/
// int CDplayer::ReadCDdata()
// {
//     if(ReadNtagMsg(cmd)==0)
//     {
//         cmd_wait_for_handle = 1;
//         //current_CD = cmd[1]; //00:循环歌单 其他：歌曲序号
//         return CD_OK;
//     }else{
//         return CD_ERROR;
//     }
// }
bool CDplayer::tailkey_is_on()
{
    if(1)
    return 1;
    if(0)
    {
        return 0;
    }
}
/**
* @brief  检查当前解析的曲目与当前播放的曲目是否一致
* @param  
* @return 1：
*/
// bool CDplayer::new_cmd_has_been_recived()
// {  
//     bool recived = cmd_wait_for_handle;
//     cmd_wait_for_handle = 0;
//     return recived;
// }
void CDplayer::MotorCtr(uint8_t __switch)
{

}
// int CDplayer::Mp3EndPlay()
// {
//     heartbeat = timeset;
//     cmd_wait_for_handle = 0;
//     return 0;
// }
// bool CDplayer::is_CD_been_switched()
// {
//     if(cmd[1]==current_CD)
//     {
//         return 0;
//     }else{
//         return 1;
//     }
// }
/**
* @brief  
* @param  
* @return 
*/
void CDplayer::MP3ctrl(MP3COMMAND _cmd)
{
    switch(_cmd.cmd_type)
    {
        case VOLUMESET:
            VolumeCtrl(_cmd.cmd_data);
            break;
        case SELECT_FOLDER:
            PlayTargetVoice(_cmd.cmd_data);
            break;
        case FOLDER_CIRCLE:
            PlayFavourList();
            break;
        case END_PLAY:
            EndPlay();
            break;
        case STATU_UPDATE:
            UpdateStatus();
            break;
        case PLAY_MODE_SET:
            break;
        default:
            break;
    }
}
/**
* @brief mp3播放音乐  
* @param  
* @return 
*/
// void CDplayer::Mp3Play()
// {
//     if(cmd[0]==SELECT_FOLDER)
//     {
//         PlayTargetVoice(cmd[1]);
//     }
//     if(cmd[0]==FOLDER_CIRCLE)
//     {   
//         PlayFavourList();
//     }
// }
// void CDplayer::SystemNotify()
// {
//     SystemNotify(0x01);//播放03目录第一首
// }
// void Update()
// {
//     statu = MP3_Unpack();
//     if(statu == -1)
//     {
//         //抛出异常
//     }
// }