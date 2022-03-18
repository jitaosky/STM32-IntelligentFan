#ifndef _MENU_H_
#define _MENU_H_

#include "stm32f10x.h"

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define KEY_NULL 	0x05				//按键无事件
#define KEY_down 	0x07				//向下按键事件标志
#define KEY_enter 0x08			  //进入按键事件标志
#define KEY_esc		0x09				//返回按键事件标志
#define NUM_up 		0x0B				//数值加按键事件标志
#define NUM_down 	0x0C				//数值减按键事件标志


typedef struct{
	uchar current_index;	//存放当前界面的索引号；
	uchar down_index;		  //存放按下“down（向下）”键时需要跳转到的索引号；
	uchar enter_index;		//存放按下“enter（进入）”键时需要跳转的索引号；
	uchar esc_index;		  //存放按下“esc（退出）”键时需要跳转的索引号；
	void (*operate)();	  //函数指针变量，存放当前索引号下需要执行的函数的入口地址。
}Key_index_struct;

typedef enum// 菜单索引
{
	home,
	temp_set,
	level_set,
	model_set,
	hightemp_set,
	lowtemp_set,
	chooselevel_set,
	choosemodel_set,
	MENU_NUM, // 菜单页总数
}MENU_INDEX_LIST;


void mainWindow(void);//主界面
void menu_temp_set(void);
void menu_level_set(void);
void menu_model_set(void);
void menu_hightemp_set(void);
void menu_lowtemp_set(void);
void menu_chooselevel_set(void);
void menu_choosemodel_set(void);
void menuEventHandle(void);
#endif /*_MENU_H_*/
