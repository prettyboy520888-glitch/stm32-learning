#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
    /* 1. 变量声明必须放在最顶端 (C89 Requirement) */
    GPIO_InitTypeDef GPIO_InitStructer;
    
    /* 2. 使能时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    /* 3. 配置 GPIO */
    GPIO_InitStructer.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructer.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructer);
    
    /* 4. 初始化默认拉高引脚，确保 LED 处于熄灭状态 */
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

void LED1_ON(void)
{
    /* 使用 ResetBits 输出低电平，点亮 LED */
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void LED1_OFF(void)
{
    /* 使用 SetBits 输出高电平，熄灭 LED */
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void LED2_ON(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

void LED2_OFF(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
}
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}

}

void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}

}