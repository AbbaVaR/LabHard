#include "main.h"	//Заголовчоный файл с описанием подключаемых библиотечных модулей

int main(void)
{
	InitUSART1();
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;																						//Включение тактирования порта B: RCC_AHBENR_GPIOBEN=0x00040000																																			
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 										//Переключение линий 0-8 порта B в режим "Output"
								| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER7_0 
								| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER5_0 
								| GPIO_MODER_MODER4_0	|  GPIO_MODER_MODER3_0 
								| GPIO_MODER_MODER8_0;
	unsigned reg[8] = {0x101, 0x102, 0x104, 0x180, 0x140, 0x120, 0x110, 0x108};  //Регистры для запуска светодиодов
	unsigned input [8][8] = {{0x31,0}, {0x32,1}, {0x33,2}, {0x34,3}, {0x35,4}, {0x36,5}, {0x37,6}, {0x38,7}};
	uint16_t check[8] = {0,0,0,0,0,0,0,0};
	unsigned elem =0;
	while(1){
		while ((USART1->ISR & USART_ISR_RXNE) == 0) { }
		uint8_t d = (uint8_t)USART1->RDR;

		while ((USART1->ISR & USART_ISR_TXE) == 0) { }
		USART1->TDR = d;
		
		for (uint16_t i = 0; i < 9; i++){
			if (d == input[i][0]){
				elem = input[i][1];
			}
		}
	
			if (check[elem] == 0){
				GPIOB->BSRR |= reg[elem];
				check[elem] = 1;
				d = 0x0;
			}
			else{
				GPIOB->BSRR |= reg[elem]<<16;
				check[elem] = 0;
				d = 0x0;
			}			
	}
}

void InitUSART1(){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= 0x00280000;
	GPIOA->AFR[1] |= 0x00000110;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;
	USART1->CR1 &= ~USART_CR1_UE;
	USART1->BRR=69;
	USART1->CR1 = USART_CR1_TE | USART_CR1_RE;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	USART1->CR1 |= USART_CR1_UE;
}
