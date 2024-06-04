/*------------------------------------------------------------------------------
 * @file    SYS_INTERNAL.H
 * @author  Hovey https://space.bilibili.com/33582262?spm_id_from=333.1007.0.0
 * @date    2024/04/30 18:07:44
 * @brief   
 * -----------------------------------------------------------------------------
 * @attention 
 
------------------------------------------------------------------------------*/

/* Define to prevent recursive inclusion  ------------------------------------*/
#ifndef __SYS_INTERNAL_H
#define __SYS_INTERNAL_H

/* Files includes  -----------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "Middlewares/CDplayer.h"

/* Defines -------------------------------------------------------------------*/
/* Task Config Definitions ---------------------------------------------------------*/
#define Tiny_Stack_Size       64
#define Small_Stack_Size      128
#define Normal_Stack_Size     256
#define Large_Stack_Size      512
#define Huge_Stack_Size       1024
	
#define PriorityVeryLow       1
#define PriorityLow           2
#define PriorityBelowNormal   3
#define PriorityNormal        4
#define PriorityAboveNormal   5
#define PriorityHigh          6
#define PrioritySuperHigh     7
#define PriorityRealtime      8

/* Variables -----------------------------------------------------------------*/


/* Functions ----------------------------------------------------------------*/
void AppInit();
#endif
