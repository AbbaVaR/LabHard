#include "main.h"
int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER6_0  | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER4_0|  GPIO_MODER_MODER3_0 | GPIO_MODER_MODER8_0;
	GPIOB->MODER&=~ GPIO_MODER_MODER15;
	
	GPIOB->ODR |=0x101; //0
	delay(500000);
	GPIOB->ODR |=0x102; //1
	delay(500000);
	GPIOB->ODR |=0x104; //2
		delay(500000);
	GPIOB->ODR |=0x180; //7
		delay(500000);
	GPIOB->ODR |=0x140; //6
		delay(500000);
	GPIOB->ODR |=0x120; //5
		delay(500000);
	GPIOB->ODR |=0x110; //4
		delay(500000);
	GPIOB->ODR |=0x108; //3
		delay(500000);
	GPIOB->ODR &=0x1fe; //0
		delay(500000);
	GPIOB->ODR &=0x1fd; //1
		delay(500000);
	GPIOB->ODR &=0x1fb; //2
		delay(500000);
	GPIOB->ODR &=0x17f; //7
		delay(500000);
	GPIOB->ODR &=0x1bf; //6
		delay(500000);
	GPIOB->ODR &=0x1df; //5
		delay(500000);
	GPIOB->ODR &=0x1ef; //4
		delay(500000);
	GPIOB->ODR &=0x0f7; //3


}

void delay(uint32_t count)
{
	volatile uint32_t i;
	for (i =0;i<count;i++);
}


