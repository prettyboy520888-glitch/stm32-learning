#include "stm32f10x.h"                  // Device header
#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
    /* 1. 变量声明必须放在最顶端 (C89 Requirement) */
    GPIO_InitTypeDef GPIO_InitStructer;
    
    /* 2. 使能时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    /* 3. 配置 GPIO */
    GPIO_InitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructer.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructer);
    
    
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_ON(void)
{
    /* 使用 ResetBits 输出低电平，点亮 LED */
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
    /* 使用 SetBits 输出高电平，熄灭 LED */
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12)==0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}

}
