#include "main.h"

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 |
								GPIO_MODER_MODER3_0 | GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 |
								GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0 | GPIO_MODER_MODER9_0;
	GPIOB->MODER&=~( GPIO_MODER_MODER12 | GPIO_MODER_MODER13 |  GPIO_MODER_MODER14 |  GPIO_MODER_MODER15);
	
	uint16_t a[8] = {0, 0, 1, 1, 0, 0, 0, 0} ;
	uint16_t n;
	uint16_t out[4];

	unsigned reg[4] = {0x0000003F, 0x00000006, 0x0000005B, 0x0000004F};
	
	while(1){
		n=0;
		a[1]=((GPIOB->IDR)&0x8000)>>15;
		a[4]=((GPIOB->IDR)&0x4000)>>14;
		a[6]=((GPIOB->IDR)&0x2000)>>13;
		a[7]=((GPIOB->IDR)&0x1000)>>12;
		
		uint32_t j=7;
	
		for (uint16_t i = 0 ; i<8; i++){         //to 10
			n += a[i]* powi (2, j);
			j--;
		}
		
		for (uint16_t i = 0 ; i<2; i++){         //to 4		
			if(n<4) {
				out[i] = n;	
				break;
			}
			out[i] = n%4;
			n = n/4;
		}
		
		for (uint16_t i =0; i<4; i++){
			GPIOB->BSRR|=reg[out[i]];
			delay(200000);
			GPIOB->BSRR|=0xffff0000;			
			delay(50000);
		}
		GPIOB->BSRR|=0x80;
		delay(500000);
		GPIOB->BSRR|=0xffff0000;	
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
 
void delay(uint32_t count)
{
	volatile uint32_t i;
	for (i =0;i<count;i++);
}
