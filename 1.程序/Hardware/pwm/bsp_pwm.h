#ifndef  __BSP_PWM_H_
#define  __BSP_PWM_H_

#include "stm32f10x.h"
#include <sys.h>


#define AIN1   PBout(13)
#define AIN2   PBout(14)

void MiniBalance_Motor_Init(void);
void PWM_TIM3_Init(void);
void Machinery_Go(void);
void Machinery_STOP(void);

void PWM_Ch1_TIM3_Ste(u16 Duty_ch1,FunctionalState NewState);


#endif  /* __BSP_PWM_H_ */

