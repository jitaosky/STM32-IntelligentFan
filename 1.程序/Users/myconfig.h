/**
  *************************************************************************************************************************
  * @file    myconfig.h
  * @author  LiuHongMing
  * @version V1.0
  * @date    2022-01-15
  * @brief   蓝桥嵌入式开发板外设引脚，配置参数,头文件
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __MYCONFIG_H
#define	__MYCONFIG_H

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "tim.h"
#include "bsp_pwm.h"
#include "bsp_ds18b20.h"
#include "bsp_key.h" 
#include "menu.h"
#include "gpio.h" 
#include "stdio.h"
/* 定义 -----------------------------------------------------------------------------------------------------------------*/
#define TIMERCOUNT  (2)//定义软件定时个数
#define TIMERINDEX1 (0)//事件1    
#define TIMERINDEX2 (1)//事件2
 

#define TIMEISUP		(1)//时间到
#define TIMEISNOTUP	(0)//时间没到

#define VOICE		(2)//语音
#define AUTO		(1)//自动
#define MANUAL	(0)//手动

#define ONEGEAR    (1)//挡位
#define TWOGEAR    (2)
#define THREEGEAR  (3)
#define ShutDOWN   (0)

typedef struct
{
  uint8_t HIGH_TEMP;
  uint8_t LOW_TEMP;
	uint8_t LEVEL;
	uint8_t MODEL;
}SYSTEM;

/* 提供给其他C文件调用的函数 --------------------------------------------------------------------------------------------*/
unsigned char xDelay(unsigned char xIndex,unsigned char xTime);
void Key_Proc(void);
void Pwm_Proc(void);
void DS18B20_Proc(void);
void Control_Proc(void);
void Buzzer_Alarm(void);
void SystemPara_Init(void);
void FANMANUAL_PROC(void);
void FANAUTO_PROC(void);
void FANVOICE_PROC(void);
#endif /* __MYCONFIG_H */

/*****************************************************END OF FILE*********************************************************/	
