/*
AIM: Press user button-> LED On-> D4 HIGH
           not pressed->LED Off->D4 low
User button->PC13
LED->PA5
D4->PB5

All GPIO's Connected to AHB1 bus
*/
#include "stm32f4xx.h"                  // Device header
void d4_init(void);
void button_init(void);
void led_init(void);
void process(void);
int main(void){
	button_init();
	led_init();
	d4_init();
	while(1){
		process();
	}
}
void button_init(void){
	RCC->AHB1ENR |= 0x4;
	GPIOC->MODER |= 0x0;            //input mode
}
void led_init(void){
	RCC->AHB1ENR |= 0x1;
	GPIOA->MODER |= 0x400;         //Output mode
}
void d4_init(void){
	RCC->AHB1ENR |=0x2;
	GPIOB->MODER |=0x400;           //Output mode
}
void process(void){
	if((GPIOC->IDR & 0x2000)){
		 GPIOA->BSRR |= 0x200000;     //LED off
		 GPIOB->ODR  &=~0x20;         //Pin High
	   
	}
	else{
		GPIOA->BSRR |=0x20;           //LED ON
		GPIOB->ODR  |=0x20;           //Pin HIGH
	}
}

