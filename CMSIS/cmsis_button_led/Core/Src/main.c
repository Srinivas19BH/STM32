#include "stm32f4xx.h"

void delay_ms(uint32_t ms)
{
    SysTick->LOAD = 16000 - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = 5;

    for (uint32_t i = 0; i < ms; i++)
    {
        while ((SysTick->CTRL & (1 << 16)) == 0);
    }

    SysTick->CTRL = 0;
}

void main(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER &= ~(3 << 26);
    GPIOB->MODER |=  (1 << 26);

    // PB12 input
    GPIOB->MODER &= ~(3 << 24);

    while (1)
    {
        if (GPIOB->IDR & (1 << 12))
        {
            GPIOB->ODR |= ~(1 << 13);
        }
        else
        {
            GPIOB->ODR = (1 << 13);
        }

        delay_ms(1000);

        GPIOB->ODR = ~(1 << 13);
    }
}
