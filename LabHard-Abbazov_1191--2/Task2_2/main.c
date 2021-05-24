#include "main.h"	//Заголовчоный файл с описанием подключаемых библиотечных модулей

int main(void)
{
	InitUSART1();																								//Инициализация USART1 лаборатоного стенда
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;													//Включение тактирования порта B: RCC_AHBENR_GPIOBEN=0x00040000																																			
	GPIOB->MODER |= GPIO_MODER_MODER0_0 | GPIO_MODER_MODER1_0 	//Переключение линий 0-8 порта B в режим "Output"
								| GPIO_MODER_MODER2_0 | GPIO_MODER_MODER7_0 
								| GPIO_MODER_MODER6_0 | GPIO_MODER_MODER5_0 
								| GPIO_MODER_MODER4_0	| GPIO_MODER_MODER3_0 
								| GPIO_MODER_MODER8_0;
	//Объявление переменных
	unsigned reg[8] = {0x1, 0x2, 0x4, 0x80, 0x40, 0x20, 0x10, 0x8};  																											//Регистры для запуска светодиодов
	unsigned input [9][9] = {{0x31,0}, {0x32,1}, {0x33,2}, {0x34,3}, {0x35,4}, {0x36,5}, {0x37,6}, {0x38,7}, {0x30,8}};		//Двумерный массив (Вхлдящее число в hex и его соответсявие в данной программе)
	uint16_t check[8] = {0,0,0,0,0,0,0,0};											//Масиив состояний светодиодов (0 - выключен, 1 - включён)
	unsigned elem = 0;																					//Номер нажатаой клавиши
	uint8_t d;																									//Данные из USART 
	GPIOB->BSRR |= 0x100;																				//Включение линии 8 порта B
	
	while(1){
		//Получение данных из USART
		while ((USART1->ISR & USART_ISR_RXNE) == 0) { } 					//Чтение регистра состояния ISR и анализ флага RXNE (выставляется в 1, когда новый пакет данных получен приёмником Rx и скопирован в RDR)
		d = (uint8_t)USART1->RDR;																	//Копирование данных из USART (регистр RDR) в програмную переменную.
		// Чтение регистра RDR приводит к сбросу флага RXNE = 0
		
		for (uint16_t i = 0; i < 9; i++){
			if (d == input[i][0]){
				elem = input[i][1];
			}
		}
		
		if (d == 0x39){
			for (uint16_t i=0; i<8; i++){
				msg((uint8_t)input[i][0],check[i]);
			}
			continue;
		}
		
		if (elem == 8){
			for (int16_t i = 0; i<8; i++){
				GPIOB->BSRR = reg[i] << 16;
				check[i] = 0;
			}
			for (uint16_t i=0; i<8; i++){
				msg((uint8_t)input[i][0],check[i]);
			}
			continue;
		}
		
		if (check[elem] == 0){
			GPIOB->BSRR |= reg[elem];
			check[elem] = 1;
			msg(d, check[elem]);
			continue;
		}
		else{
			GPIOB->BSRR |= reg[elem]<<16;
			check[elem] = 0;
			msg(d, check[elem]);
		  continue;
		}
		
	}
}

void msg (uint8_t number, unsigned flag){
	uint8_t textDiod [5] = {0x44, 0x69, 0x6F, 0x64,0x20};
	uint8_t textOn[5] = {0x20, 0x6f, 0x6e, 0x0D, 0x0A};
	uint8_t textOff[6] = {0x20, 0x6f, 0x66,0x66, 0x0D, 0x0A};

		for (uint16_t i=0; i<5; i++){
			while ((USART1->ISR & USART_ISR_TXE) == 0) { }
			USART1->TDR = textDiod[i];
		}
		while ((USART1->ISR & USART_ISR_TXE) == 0) { }
		USART1->TDR = number;
		
		if (flag == 1){
			for (uint16_t i=0; i<5; i++){
			while ((USART1->ISR & USART_ISR_TXE) == 0) { }
			USART1->TDR = textOn[i];
			}
		}
		else {
			for (uint16_t i=0; i<6; i++){
			while ((USART1->ISR & USART_ISR_TXE) == 0) { }
			USART1->TDR = textOff[i];		
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
