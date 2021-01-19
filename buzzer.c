#include "MKL05Z4.h"
#include "buzzer.h"


void buzzer(void){
	
	//PTB->PDOR&=~(1<<13); //off
	PTB->PDOR|=(1<<13); //on
	
	delay_ms(200);
	
	PTB->PDOR&=~(1<<13);

}
