#include "stm32f10x.h"                  // Device header
#include "DELAY.h"  
#include "OLED.h"
#include "Encoder.h"

int16_t Num;

int main(void)
{
	OLED_Init();
	Encoder_Init();
	
	OLED_ShowString(1, 1, "Num:");

	while(1)
	{
		Num += Encoder_Get();
		// 把显示的列坐标往后移到第5列，避开 "Num:" 字符串
		OLED_ShowSignedNum(1, 5, Num, 5); 
	}

}
