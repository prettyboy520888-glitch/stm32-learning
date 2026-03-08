#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    /* 1. 变量声明必须放在最顶端 (严格遵循 C89 规范) */
    GPIO_InitTypeDef GPIO_InitStructer;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    
    /* 2. 使能时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    /* 3. 配置 GPIO (PA1 对应 TIM2_CH2) */
    GPIO_InitStructer.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructer.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructer.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructer);
    
    /* 4. 配置定时器时基 */
    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // 72MHz / 72 / 20000 = 50Hz (周期 20ms，符合标准舵机要求)
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1; 
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    /* 5. 配置输出比较通道 2 */
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 修正了带 N 的互补通道极性错误
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0; // 初始占空比设为0比较安全
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    
    /* 6. 使能定时器 */
    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2, Compare); // 修正为通道 2
}
