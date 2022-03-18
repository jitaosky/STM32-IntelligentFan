#ifndef __bsp_key_H
#define	__bsp_key_H

#include "stm32f10x.h"

#define KEY1  	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键1
#define KEY2 	 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//读取按键2
#define KEY3  	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//读取按键3
#define KEY4 	 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键4
#define KEY5 	 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//读取按键5

#define KEY1_PRES	  1	//KEY1按下
#define KEY2_PRES   2	//KEY2按下
#define KEY3_PRES   3	//KEY3按下
#define KEY4_PRES 	4	//KEY4按下
#define KEY5_PRES 	5	//KEY5按下

#define KEY1_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY1_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY1_GPIO_PIN		    GPIO_Pin_0			        /* 连接到SCL时钟线的GPIO */

#define KEY2_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY2_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY2_GPIO_PIN		    GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */

#define KEY3_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY3_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY3_GPIO_PIN		    GPIO_Pin_2			        /* 连接到SCL时钟线的GPIO */

#define KEY4_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY4_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY4_GPIO_PIN		    GPIO_Pin_3			        /* 连接到SCL时钟线的GPIO */

#define KEY5_GPIO_PORT    	GPIOA			              /* GPIO端口 */
#define KEY5_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define KEY5_GPIO_PIN		    GPIO_Pin_4			        /* 连接到SCL时钟线的GPIO */



u8 KEY_Scan(u8);  	//按键扫描函数	
void KEY_GPIO_Config(void);
void delay(uint32_t count);

#endif /* __bsp_key_H */

