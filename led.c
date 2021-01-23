#include "MKL05Z4.h"
#include "led.h"
#include "buzzer.h"




void led_init(void){
	//dioda
	PORTB->PCR[0] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<0);
	PTB->PDOR|=(1<<0); //on
	
	PORTB->PCR[10] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<10);
	PTB->PDOR|=(1<<10); //on
	
	PORTB->PCR[11] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<11);
	PTB->PDOR|=(1<<11); //on
	
	PORTB->PCR[9] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<9);
	PTB->PDOR|=(1<<9); //on
	
	PORTB->PCR[8] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<8);
	PTB->PDOR|=(1<<8); //on

}

void turn_off(void){ //gaszenie diod
	
	//zgaszenie pierwszej
	LCD1602_SetCursor(0,1);
	LCD1602_Print("5 sekund!        ");
	delay_ms(800);
	buzzer();
	PTB->PDOR&=~(1<<0); //off
	LCD1602_SetCursor(0,1);
	
	LCD1602_Print("4 sekundy!        ");
	delay_ms(800);
	buzzer();
	PTB->PDOR&=~(1<<10); //off
	LCD1602_SetCursor(0,1);
	
	LCD1602_Print("3 sekundy!        ");
	delay_ms(800);
	buzzer();
	PTB->PDOR&=~(1<<11); //off
	LCD1602_SetCursor(0,1);
	
	LCD1602_Print("2 sekundy!        ");
	delay_ms(800);
	buzzer();
	PTB->PDOR&=~(1<<9); //off
	LCD1602_SetCursor(0,1);
	
	LCD1602_Print("1 sekunda!        ");
	delay_ms(800);
	buzzer();
	PTB->PDOR&=~(1<<8); //off
	buzzer();
	buzzer();
	buzzer();
}
