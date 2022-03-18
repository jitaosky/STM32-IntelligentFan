#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"


#define People_testing 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)

#define voice_ONEGEAR				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define voice_TWOGEAR 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)
#define voice_THREEGEAR 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)
#define voice_ShutDOWN 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)

#define Buzzer_ON 					GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define Buzzer_OFF					GPIO_ResetBits(GPIOB,GPIO_Pin_0)

void Infrared_GPIO_Config(void);
void Voice_GPIO_Config(void);
void BUZZER_GPIO_Config(void);

#endif /*__GPIO_H*/
