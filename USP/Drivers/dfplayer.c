/*------------------------------------------------------------------------------
 * @file    DFPLAYER.C
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/05/20 11:58:09
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/
#include "Drivers/dfplayer.h"
#include "usart.h"
uint8_t rx_data[10];
DFplayer mp3 = {
    .huart = &huart2,
    .rxbuff_size = 10
};
// uint8_t cmd[2];
/**
* @brief  
* @param  
* @return 
*/
static int SendCMD(uint8_t cmd,uint8_t data1,uint8_t data2,uint8_t return_flag)
{
    uint8_t tx_msg[10];
    uint16_t check_sum = 0;
    tx_msg[0] = 0x7e;
    tx_msg[1] = 0xff;
    tx_msg[2] = 0x06;
    tx_msg[3] = cmd;
    tx_msg[4] = return_flag;
    tx_msg[5] = data1;
    tx_msg[6] = data2;
    check_sum = 0x10000 - (tx_msg[1]+tx_msg[2]+tx_msg[3]+tx_msg[4]+tx_msg[5]+tx_msg[6]);
    tx_msg[7] = (check_sum >> 8) & 0xFF;
    tx_msg[8] = check_sum & 0xFF;
    tx_msg[9] = 0xef;
	if(HAL_UART_Transmit_DMA(mp3.huart,tx_msg,10) != HAL_OK)
        return -1;
	return 0;
}
void DFplayerInit(void)
{
    HAL_UART_Receive_IT(mp3.huart,mp3.rxbuff,1);
    __HAL_UART_ENABLE_IT(mp3.huart,UART_IT_IDLE);
}
/**
* @brief  
* @param  
* @return 
*/
int UpdateStatus()
{  
    SendCMD(STATU_UPDATE,0x00,0x00,NO_ACK);
    return 0;
}
/**
* @brief  
* @param  
* @return 
*/
int SystemNotify(uint8_t notify)
{
    SendCMD(SELECT_FOLDER,SYSTEM_VOICE_FOLDER,notify,NO_ACK);
    SendCMD(PLAY_MODE_SET,0x00,SINGLE,NO_ACK);
    return 0;
}
/**
* @brief  
* @param  
* @return 
*/
int PlayFavourList(void)
{
    SendCMD(FOLDER_CIRCLE,0x00,FAVOR_FOLDER,NO_ACK);
	return 0;
}
int StopPlay()
{
    SendCMD(STOP_PLAY,0x00,0x00,NO_ACK);
    return 0;
}
int EndPlay()
{
    SendCMD(END_PLAY,0x00,0x00,NO_ACK);
    return 0;
}
int ContinuePlay()
{
    SendCMD(CONTINUE_PLAY,0x00,0x00,NO_ACK);
    return 0;
}
/**
* @brief  
* @param  
* @return 
*/
int PlayTargetVoice(uint8_t id)
{    
	SendCMD(SELECT_FOLDER,CD_FOLDER,id,NO_ACK);
  SendCMD(PLAY_MODE_SET,0x00,SINGLE,NO_ACK);
  return 0;
}

/**
* @brief  
* @param  
* @return 
*/
int VolumeCtrl(uint8_t var)
{
    SendCMD(VOLUMESET,0x00,var,NO_ACK);
	return 0;
}
/**
* @brief  
* @param  
* @return 
*/
int DFplayerCallback()
{
    if(__HAL_UART_GET_FLAG(mp3.huart,UART_FLAG_IDLE)!=RESET)
	{
		/* clear idle it flag avoid idle interrupt all the time */
        __HAL_UART_CLEAR_IDLEFLAG(mp3.huart);
        /* clear DMA transfer complete flag */
        HAL_UART_DMAStop(mp3.huart);

/*-----------------------user code -----------------*/
       // HAL_UART_Transmit_DMA(uppermonitor.huart,uppermonitor.rxbuff,7);
/*-----------------------user code -----------------*/

        HAL_UART_Receive_DMA(mp3.huart,mp3.rxbuff, mp3.rxbuff_size);
	}else{
        return -1;
    }
    return 0;
}
/**
* @brief  
* @param  
* @return 
*/
int MP3_Unpack()
{
    uint16_t check_sum = 0;
    if((mp3.rxbuff[0] != 0x7e) || (mp3.rxbuff[1] != 0xff) || (mp3.rxbuff[9] != 0xef))
    {
        return -1;
    }
    check_sum = 0x10000 - (mp3.rxbuff[1]+mp3.rxbuff[2]+mp3.rxbuff[3]+mp3.rxbuff[4]+mp3.rxbuff[5]+mp3.rxbuff[6]);
    if((mp3.rxbuff[7] != ((check_sum >> 8) & 0xFF)) || (mp3.rxbuff[8] != (check_sum & 0xFF)))
    {
        return -1;
    }
    switch(mp3.rxbuff[3])
    {
        case ERROR_MSG:
            break;
        case STATUS_MSG:
            switch(mp3.rxbuff[5])
            {
                case MP3RUNNING:
                    break;
                case MP3STOP:
                    break;
                case MP3END:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return 0;
}

