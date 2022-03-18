#include "gpio.h" 




void Infrared_GPIO_Config(void)
{		
 GPIO_InitTypeDef GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;  
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOA,&GPIO_InitStructure);
}

void BUZZER_GPIO_Config(void)
{		
 GPIO_InitTypeDef GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_Out_PP;  
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOB,&GPIO_InitStructure);
}


void Voice_GPIO_Config(void)
{		
 GPIO_InitTypeDef GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
 GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;  
 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 GPIO_Init(GPIOA,&GPIO_InitStructure);

}



