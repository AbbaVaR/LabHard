#include "main.h"
int main(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 
								| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER7_0 
								| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER5_0 
								| GPIO_MODER_MODER4_0	|  GPIO_MODER_MODER3_0 
								| GPIO_MODER_MODER8_0;
	GPIOB->MODER&=~ GPIO_MODER_MODER15;
	
	unsigned  regOn[8] = {0x101, 0x002, 0x004, 0x080, 0x040, 0x020, 0x010, 0x008};  
	unsigned  regOff[8] = {0x1fe, 0x1fd, 0x1fb, 0x17f, 0x1bf, 0x1df, 0x1ef, 0x0f7};
	
	if(1){
		for (uint32_t i = 0; i<9; i++){
			alllamp(regOn[i]);
		}
		for (uint32_t j = 0; j<9; j++){
			alllamp(regOff[j]);
		}
	}
}

void delay(uint32_t count)
{
	volatile uint32_t i;
	for (i =0;i<count;i++);
}

void alllamp(unsigned reg){
		GPIOB->ODR |= reg;
		delay(100000);
}
