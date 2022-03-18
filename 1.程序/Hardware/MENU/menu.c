/**
  *************************************************************************************************************************
  * @file    menu.c
  * @author  amkl
  * @version V2.0
  * @date    2022-03-17
  * @brief   菜单实现文件
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
***/

#include "menu.h"
#include "myconfig.h"

unsigned char volatile nowMenuIndex = 0;
extern int temperature;
volatile unsigned char menuEvent;
SYSTEM SYSTEM_Para;


/*
参考文章
https://blog.csdn.net/embedded_guzi/article/details/35835755
https://blog.csdn.net/calmuse/article/details/79346742
*/
Key_index_struct Key_table[MENU_NUM]=
{
    //当前字符索引号，按下向下需要跳转的索引号 ，按下进入需要跳转的索引号 ,返回上一界面
    {home,		       home,	         temp_set,	       home , 		 (*mainWindow)},		        //一级界面第一行
    {temp_set,		   level_set,	     hightemp_set,	   home , 		 (*menu_temp_set)},		      //二级界面第一行
		{level_set,		   model_set,	     chooselevel_set,	 home , 		 (*menu_level_set)},		    //二级界面第二行
		{model_set,		   temp_set,	     choosemodel_set,	 home , 		 (*menu_model_set)},		    //二级界面第三行
		{hightemp_set,	 lowtemp_set,    hightemp_set,     temp_set ,	 (*menu_hightemp_set)},		  //三级界面第一行
		{lowtemp_set,		 hightemp_set, 	 lowtemp_set, 		 temp_set ,	 (*menu_lowtemp_set)},		  //三级界面第二行
		{chooselevel_set,chooselevel_set,chooselevel_set,  level_set , (*menu_chooselevel_set)},  //三级界面第三行
		{choosemodel_set,choosemodel_set,choosemodel_set,  model_set , (*menu_choosemodel_set)},  //三级界面第四行
};

void OLED_display(void)
	{
	switch(menuEvent){
		case KEY_down: //向下
			nowMenuIndex=Key_table[nowMenuIndex].down_index; 
			break;
		case KEY_enter://进入
			nowMenuIndex=Key_table[nowMenuIndex].enter_index;
			break;
		case KEY_esc://返回
			nowMenuIndex=Key_table[nowMenuIndex].esc_index;
			break;
		case NUM_down:
			break;
		case NUM_up:
			break;
		default: ;break;
	}
	Key_table[nowMenuIndex].operate();
}

//菜单事件处理函数：更新菜单界面、数据处理
void menuEventHandle(void)
{
	OLED_display();
	if(menuEvent==NUM_up)
	{	
		if(nowMenuIndex==hightemp_set)
		{
			(SYSTEM_Para.HIGH_TEMP>=60)?(SYSTEM_Para.HIGH_TEMP=60):(SYSTEM_Para.HIGH_TEMP++);
			menu_hightemp_set();
		}
		else if(nowMenuIndex==lowtemp_set)
		{
			(SYSTEM_Para.LOW_TEMP>=25)?(SYSTEM_Para.LOW_TEMP=25):(SYSTEM_Para.LOW_TEMP++);
			menu_lowtemp_set();
		}
		else if(nowMenuIndex==chooselevel_set)
		{	
			(SYSTEM_Para.LEVEL>=3)?(SYSTEM_Para.LEVEL=3):(SYSTEM_Para.LEVEL++);
			menu_chooselevel_set();
		}
		else if(nowMenuIndex==choosemodel_set)
		{	
			SYSTEM_Para.MODEL=(SYSTEM_Para.MODEL+1)%3;
    	menu_choosemodel_set();
		}
	}
	if(menuEvent==NUM_down)
	{
		if(nowMenuIndex==hightemp_set)
		{
			(SYSTEM_Para.HIGH_TEMP<=30)?(SYSTEM_Para.HIGH_TEMP=30):(SYSTEM_Para.HIGH_TEMP--);
			menu_hightemp_set();
		}
		else if(nowMenuIndex==lowtemp_set)
		{
			(SYSTEM_Para.LOW_TEMP<=10)?(SYSTEM_Para.LOW_TEMP=10):(SYSTEM_Para.LOW_TEMP--);
			menu_lowtemp_set();
		}
			else if(nowMenuIndex==chooselevel_set)
		{	
			(SYSTEM_Para.LEVEL<=0)?(SYSTEM_Para.LEVEL=0):(SYSTEM_Para.LEVEL--);
			menu_chooselevel_set();
		}
		else if(nowMenuIndex==choosemodel_set)
		{	
			SYSTEM_Para.MODEL=(SYSTEM_Para.MODEL+1)%3;
    	menu_choosemodel_set();
		}
	}
	menuEvent = KEY_NULL;
}

void mainWindow(void)
{
	OLED_ShowString(0,0,"      MAIN      ",16);
	OLED_ShowString(0,16,"TEMP:   . C",16);
	
	switch(SYSTEM_Para.LEVEL)
	{
		case 0:OLED_ShowString(0,32,"LEVEL:OFF      ",16);break;//关闭
		case 1:OLED_ShowString(0,32,"LEVEL:ONEGEAR  ",16);break;//一档
		case 2:OLED_ShowString(0,32,"LEVEL:TWOGEAR  ",16);break;//二档
		case 3:OLED_ShowString(0,32,"LEVEL:THREEGEAR",16);break;//三档
		default:break;
	}
	switch(SYSTEM_Para.MODEL)
	{
		case 0:OLED_ShowString(0,48,"MODEL:MANUAL   ",16);break;//手动
		case 1:OLED_ShowString(0,48,"MODEL:AUTO     ",16);break;//自动
		case 2:OLED_ShowString(0,48,"MODEL:VOICE    ",16);break;//语音
		default:break;
	}
	
	if(temperature<0)
	{
		OLED_ShowChar(40,16,'-',16);	           //显示负号
		temperature=-temperature;		           //转为正数
	}
	else OLED_ShowChar(40,16,' ',16);             //去掉负号
	OLED_ShowNum(40+8,16,temperature/10,2,16);   //显示整数
	OLED_ShowNum(40+8+24,16,temperature%10,1,16);//显示小数部分	
	
	OLED_Refresh(); 
}


void menu_temp_set(void)
{
	OLED_ShowString(0,0,"    SET_PARA    ",16);
	OLED_ShowString(0,16,">>Temp         ",16);
	OLED_ShowString(0,32,"  LEVEL        ",16);
	OLED_ShowString(0,48,"  MODEL        ",16);
	
	OLED_Refresh(); 
}

void menu_level_set(void)
{
	OLED_ShowString(0,0,"    SET_PARA    ",16);
	OLED_ShowString(0,16,"  Temp         ",16);
	OLED_ShowString(0,32,">>LEVEL        ",16);
	OLED_ShowString(0,48,"  MODEL        ",16);
	
	OLED_Refresh(); 
}

void menu_model_set(void)
{
	OLED_ShowString(0,0,"    SET_PARA    ",16);
	OLED_ShowString(0,16,"  Temp         ",16);
	OLED_ShowString(0,32,"  LEVEL        ",16);
	OLED_ShowString(0,48,">>MODEL        ",16);
	
	OLED_Refresh(); 
}



void menu_hightemp_set(void)
{
	OLED_ShowString(0,0,"    SET_TEMP    ",16);
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,32,">>HighTemp:   C",16);
	OLED_ShowString(0,48,"  LowTemp :   C",16);	
	OLED_ShowNum(92,32,SYSTEM_Para.HIGH_TEMP,2,16);
  OLED_ShowNum(92,48,SYSTEM_Para.LOW_TEMP,2,16);   //显示整数
	OLED_Refresh(); 
}

void menu_lowtemp_set(void)
{
	OLED_ShowString(0,0,"    SET_TEMP    ",16);
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,32,"  HighTemp:   C",16);
	OLED_ShowString(0,48,">>LowTemp :   C",16);
	OLED_ShowNum(92,32,SYSTEM_Para.HIGH_TEMP,2,16);
  OLED_ShowNum(92,48,SYSTEM_Para.LOW_TEMP,2,16);   //显示整数
	OLED_Refresh(); 
}

void menu_chooselevel_set(void)
{
	OLED_ShowString(0,0,"    SET_LEVEL     ",16);
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,48,"               ",16);
	switch(SYSTEM_Para.LEVEL)
	{
		case 0:OLED_ShowString(0,32,"LEVEL:OFF      ",16);break;//关闭
		case 1:OLED_ShowString(0,32,"LEVEL:ONEGEAR  ",16);break;//一档
		case 2:OLED_ShowString(0,32,"LEVEL:TWOGEAR  ",16);break;//二档
		case 3:OLED_ShowString(0,32,"LEVEL:THREEGEAR",16);break;//三档
		default:break;
	}	
	OLED_Refresh(); 
}

void menu_choosemodel_set(void)
{
	OLED_ShowString(0,0,"    SET_MODEL     ",16);
	switch(SYSTEM_Para.MODEL)
	{
		case 0:OLED_ShowString(0,32,"MODEL:MANUAL   ",16);break;//手动
		case 1:OLED_ShowString(0,32,"MODEL:AUTO     ",16);break;//自动
		case 2:OLED_ShowString(0,32,"MODEL:VOICE    ",16);break;//语音
		default:break;
	}	
	OLED_ShowString(0,16,"               ",16);
	OLED_ShowString(0,48,"               ",16);
	OLED_Refresh(); 
}


