#include "stm32f10x.h"                  // Device header
#include "DELAY.h"  
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructer.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructer);

}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1 )==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1 )==0);
		Delay_ms(20);
		KeyNum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11 )==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11 )==0);
		Delay_ms(20);
		KeyNum=2;
	}
	return KeyNum;
}


