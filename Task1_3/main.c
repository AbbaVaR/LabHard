#include "main.h"

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 
	GPIOB->MODER |= 0x00045555;
	GPIOB->MODER&=~( GPIO_MODER_MODER12 | GPIO_MODER_MODER13 |  GPIO_MODER_MODER14 |  GPIO_MODER_MODER15);
	
	uint16_t a[8] = {0, 0, 1, 1, 0, 0, 0, 0} ;
	uint16_t n = 0;
	uint16_t answer = 0;

	unsigned reg[4] = {0x3F, 0x6, 0x5B, 0x4F};
	
	while(1){
		a[1]=((GPIOB->IDR)&0x8000)>>15;
		a[4]=((GPIOB->IDR)&0x4000)>>14;
		a[6]=((GPIOB->IDR)&0x2000)>>13;
		a[7]=((GPIOB->IDR)&0x1000)>>12;
		
		uint32_t j=7;
	
		for (uint16_t i = 0 ; i<8; i++){         //to 10
			n += a[i]* powi (2, j);
			j--;s
		}
		
		for (uint16_t i = 0 ; i<2; i++){         //to 4		
			if(n<4)	break;
			d[i] = n%4;
			n = n/4;
		}
		
		
		GPIOB->BSRR|=reg[answer];
	}
}


uint32_t powi(uint32_t x, uint32_t n)
 {
    if (n==0)
        return 1;
    else if (n==1)
        return x;
    else if (n % 2 == 0 )
        return powi( x * x, n/2);
    else
        return powi( x * x, n /2)*x;
 }
 
