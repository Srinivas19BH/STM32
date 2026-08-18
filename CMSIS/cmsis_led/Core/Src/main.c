#include "stm32f4xx.h"
void main(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= 0XFFFFF3FF;
	GPIOA->MODER |=0X01<<10;
	GPIOA->ODR |=0X01<<5;

}
//this code is for pa5 not for pb13
