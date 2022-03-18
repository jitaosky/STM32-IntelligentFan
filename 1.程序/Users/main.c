/**
  *************************************************************************************************************************
  * @file    main.c
  * @author  AMINGKL
  * @version V1.0
  * @date    2022-03-17
  * @brief   基于stm32-多功能风扇
  *************************************************************************************************************************
  * @attention
	硬件连接
  L298N:
	AIN1-PB13
	AIN1-PB14
	ENA-PA6
	
	OLED:
	SCL:PB6
	CLK:PB7
	
	按键:
	KEY1—PA0
	KEY2-PA1
	KEY3—PA2
	KEY4-PA3
	KEY5—PA4
	
	DS18B20:
	DATA-PB12
	
	红外
	infrared-PA5
	
	语音模块
	ONEGEAR-PA8
	TWOGEAR-PA9
	THREEGEAR-PA10
	ShutDOWN-PA11
	
  蜂鸣器
  PB0	
  *************************************************************************************************************************
  */
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"
/* 函数定义 -----------------------------------------------------------------------------------------------------------------*/
void All_Init(void);

 

int main(void)
{	
	All_Init();
	while(1)
	{	
		/*10ms读取一次按键，并进行处理*/
		if(xDelay(TIMERINDEX1,1)  == TIMEISUP)
		{
			Key_Proc();
			menuEventHandle();
		}
		/*1s读取一次温度*/ 		
		if(xDelay(TIMERINDEX2,100)  == TIMEISUP)
		{
			DS18B20_Proc();
			Buzzer_Alarm();
		} 
		Control_Proc();
	}
}


void All_Init(void)
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	
	KEY_GPIO_Config();
	OLED_Init();
	Tim4_Init();
	PWM_TIM3_Init();	
	while(DS18B20_Init())//检测温度传感器
	{
		OLED_ShowString(64,45,"Error",16);//温度传感器不存在
	}
	SystemPara_Init();
	Infrared_GPIO_Config();
	BUZZER_GPIO_Config();
	Voice_GPIO_Config();
	PWM_Ch1_TIM3_Ste(30,ENABLE);
	OLED_Clear();
}


/*****************************************************END OF FILE*********************************************************/	

