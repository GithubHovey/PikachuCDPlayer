#include "Middlewares/CDplayer.h"
#include "adc.h"
#include "tim.h"
uint16_t _fast = 50;
uint16_t _slow = 30;
int CDplayer::Init()
{
	HAL_ADC_Start_DMA(&hadc1, &volume, 1);
    HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
    DFplayerInit();
    RFID_Init();
    SystemNotify();
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
        vcmd.cmd_data2 = 30;
    }
    else if(volume<=400) //低死区
    {
        vcmd.cmd_data2 = 0;
    }
    else{
        vcmd.cmd_data2 = (uint8_t)((volume-400)/120); //每120一级音量
    }
    return vcmd;
}
/**
* @brief  
* @param  
* @return 
*/

int CDplayer::UnpackNtagMsg(MP3COMMAND& _mp3cmd)
{
    
    /*其余两位均为数字*/
    if((ntagdata[2]-0x30)>=0 && (ntagdata[2]-0x30)<=9 && (ntagdata[3]-0x30)>=0 && (ntagdata[3]-0x30)<=9&& (ntagdata[4]-0x30)>=0 && (ntagdata[4]-0x30)<=9 && (ntagdata[5]-0x30)>=0 && (ntagdata[5]-0x30)<=9)
    {
        _mp3cmd.cmd_type = SELECT_FOLDER;
        _mp3cmd.cmd_data1 = (ntagdata[2]-0x30)*10 + (ntagdata[3]-0x30);
        _mp3cmd.cmd_data2 = (ntagdata[4]-0x30)*10 + (ntagdata[5]-0x30);
        return 1;
    }
    /*CD*/
    if(ntagdata[2]==0x43&&ntagdata[3]==0x44)
    {
        _mp3cmd.cmd_type = FOLDER_CIRCLE;
        _mp3cmd.cmd_data2 = (ntagdata[4]-0x30)*10 + (ntagdata[5]-0x30);
        return 1;
    }
    return 0;
}
/**
* @brief ntag检测函数  
* @param  none
* @return 0：成功 -1：失败
*/
int CDplayer::CDdetect(MP3COMMAND& _mp3cmd)
{

    if(tailkey_is_on())
    {
        if(NtagDetect(ntagdata)==MI_OK)
        {
            if(heartbeat<=timeset-10)//(满心跳不检测)
            {
                if(UnpackNtagMsg(_mp3cmd))
                {
                    heartbeat = timeset;
                    if((current_CD != _mp3cmd.cmd_data2)&&(tailkey_is_on()))
                    {
                        current_CD = _mp3cmd.cmd_data2;
                        // cmd_list.push(*ntagcmd);
                        MotorCtr(_fast);//大启动力矩
                        return 1;
                    }else if((current_CD == _mp3cmd.cmd_data2)&&(tailkey_is_on()))   
                    {
                        MotorCtr(_slow);//缓速降功耗、减噪
                    }         
                }
            } 
        }
        if(heartbeat<=0)
        {
            MotorCtr(_fast);//未识别到CD时，加速电机
        }
    }else{
        heartbeat = 0;
        MotorCtr(MOTOR_OFF);
				//current_CD = 0;
    }

    if(heartbeat<=0)
    { 
        if(current_CD!=0)
        {
            _mp3cmd.cmd_type = END_PLAY;
            current_CD = 0;
            return 1; 
        }
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
    return (HAL_GPIO_ReadPin(TAIL_KEY_GPIO_Port, TAIL_KEY_Pin) == GPIO_PIN_SET) ? 0 : 1;
}
/**
* @brief  检查当前解析的曲目与当前播放的曲目是否一致
* @param  
* @return 1：
*/
void CDplayer::MotorCtr(uint16_t _speed)
{
	speed = _speed;
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,speed);
#if 0
    if(tailkey_is_on()&&heartbeat<=timeset-30&&heartbeat>0)
    speed=_slow;
#endif
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
            VolumeCtrl(_cmd.cmd_data2);
            break;
        case SELECT_FOLDER:
            PlayTargetVoice(_cmd.cmd_data1,_cmd.cmd_data2);
            break;
        case FOLDER_CIRCLE:
            PlayFavourList(_cmd.cmd_data2);
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
void CDplayer::SystemNotify()
{
    VolumeCtrl(0x0a);
    HAL_Delay(20);
    SysNotify(0x01);
    HAL_Delay(20);
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