#include "stm32f10x.h"     

void LightSensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructer;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructer.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructer.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructer);
}

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);

}
