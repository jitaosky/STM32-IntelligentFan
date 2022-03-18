/**
  *************************************************************************************************************************
  * @file    myconfig.c
  * @author  刘洪明
  * @version V1.0
  * @date    2021-12-28
  * @brief   配置函数
  *************************************************************************************************************************
  * @attention
  *
  * 
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "myconfig.h"

/* 变量定义 -----------------------------------------------------------------------------------------------------------------*/
int temperature;
unsigned char Timers[TIMERCOUNT];
extern volatile uchar menuEvent;
extern SYSTEM SYSTEM_Para;

/**
 * @brief  软件定时器
 * @param  xIndex-事件x，xTime-延时时间
 * @retval 无
 */
unsigned char xDelay(unsigned char xIndex,unsigned char xTime)
{
	unsigned char RetValue=TIMEISNOTUP;

	if(Timers[xIndex]==0)//判断指定软件定时器的计数器是否为 0
	{
		Timers[xIndex]=xTime;//得装计数器的值
		RetValue=TIMEISUP;	 //赋值返回值为：时间到	
	}
	return(RetValue);
}

void SystemPara_Init(void)
{
 	SYSTEM_Para.HIGH_TEMP=35;
	SYSTEM_Para.LOW_TEMP=20;
	SYSTEM_Para.LEVEL=ONEGEAR;
	SYSTEM_Para.MODEL=MANUAL;
}

void DS18B20_Proc(void)
{
	temperature=DS18B20_Get_Temp();//获得温度
}

void Control_Proc(void)
{
	switch(SYSTEM_Para.MODEL)
	{
		case 0:FANMANUAL_PROC();break;//手动
		case 1:FANAUTO_PROC();break;//自动
		case 2:FANVOICE_PROC();break;//语音
		default:break;
	}
}

void FANMANUAL_PROC(void)
{
 	switch(SYSTEM_Para.LEVEL)
	{
		case 0:Machinery_STOP();PWM_Ch1_TIM3_Ste(50,DISABLE);break;//关闭
		case 1:Machinery_Go();PWM_Ch1_TIM3_Ste(30,ENABLE);break;//一档
		case 2:Machinery_Go();PWM_Ch1_TIM3_Ste(60,ENABLE);break;//二档
		case 3:Machinery_Go();PWM_Ch1_TIM3_Ste(90,ENABLE);break;//三档
		default:break;
	}
}



void FANAUTO_PROC(void)
{
  if(People_testing==1)//有人
 {
  Machinery_Go();
	if(temperature<230)
	{
	 PWM_Ch1_TIM3_Ste(30,ENABLE);
	}
	else if((temperature>230)&&(temperature<300))
	{
		PWM_Ch1_TIM3_Ste(60,ENABLE);
	}
	else
	{
		PWM_Ch1_TIM3_Ste(90,ENABLE);
	}
 }
 else if(People_testing==0)//没有人
 {
	Machinery_STOP();PWM_Ch1_TIM3_Ste(50,DISABLE);
 }
}

void FANVOICE_PROC(void)
{
  if(voice_ONEGEAR==1)
	{
	 Machinery_Go();PWM_Ch1_TIM3_Ste(30,ENABLE);
	}
	 else if(voice_TWOGEAR==1)
	{
	 Machinery_Go();PWM_Ch1_TIM3_Ste(60,ENABLE);
	}
   else if(voice_THREEGEAR==1)
	{
	 Machinery_Go();PWM_Ch1_TIM3_Ste(90,ENABLE);
	}
	 else  if(voice_ShutDOWN==1)
	{
	 Machinery_STOP();PWM_Ch1_TIM3_Ste(50,DISABLE);
	}
}

void Buzzer_Alarm(void)
{
  if(temperature>500)
	{
	 Buzzer_ON;
	}
	else
	{
	 Buzzer_OFF;
	}
}

void Key_Proc(void)
{
  switch(KEY_Scan(0))
	{
		case 1: menuEvent=KEY_enter;break;
		case 2: menuEvent=KEY_down;break;
		case 3: menuEvent=KEY_esc;break;
		case 4: menuEvent=NUM_up;break;
		case 5: menuEvent=NUM_down;break;
		default:break;
	}
}

/**
 * @brief  定时器4中断服务函数-10ms中断
 * @param  无
 * @retval 无
 */
void TIM4_IRQHandler(void)
{
	static uint8_t Index;
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) == 1) 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		
		//为每一个软件定时器中的中断次数计数减 1，直到其值为 0
		for(Index=0;Index<TIMERCOUNT;Index++)
		if(Timers[Index]>0)
		Timers[Index]--;
	}
}
