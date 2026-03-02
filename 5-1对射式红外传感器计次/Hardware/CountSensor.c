#include "stm32f10x.h"                  // Device header
#include "DELAY.h"  
uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_Init_InitStructure;
	EXTI_Init_InitStructure.EXTI_Line = EXTI_Line14 ;
	EXTI_Init_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Init_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel= EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		// 1. 延时一小段时间，避开信号抖动期 (假设你有 Delay_ms 函数)
		Delay_ms(10); 
		
		// 2. 再次读取引脚电平，确认是否真的稳定在高电平
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == Bit_SET)
		{
			CountSensor_Count++;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}