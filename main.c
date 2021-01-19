#include "MKL05Z4.h"
#include "buttons.h"
#include "calc.h"
#include "lcd1602.h"
#include "pit.h"
#include "i2c.h"
#include "rtc.h"
#include "buzzer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {false, true} bool;


bool irqTimer=0;
uint32_t sec=0;
uint32_t sec_;
uint32_t min_;
uint32_t sec__;
void RTC_Seconds_IRQHandler()
{
	sec++;
}


void PIT_IRQHandler(){
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
    {
	if(irqTimer==0)
		irqTimer=1;
	PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
    }
	NVIC_ClearPendingIRQ(PIT_IRQn);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
}

void delay_ms( int n) {
	volatile int ik;
	volatile int ikk;
	for( ik = 0 ; ik < n; ik++)
	for(ikk = 0; ikk < 3500; ikk++) {}
}


int main(void) {
	
	//buzzer
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[13] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<13);
	
	//dioda
	PORTB->PCR[2] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<2);
	//PTB->PDOR&=~(1<<13); //off
	PTB->PDOR|=(1<<2); //on
	delay_ms(1000);
	//PTB->PDOR&=~(1<<2); //off
	
	buzzer();
	delay_ms(1000);
	buzzer();
	
	LCD1602_Init(); /* initialize LCD */
	LCD1602_Backlight(TRUE);
	rtc_init();
	buttons_init();
	PIT_Init();
	char tempMIN[20]={"\0"};
	char tempSEC[20]={"\0"};
	
	while (1) 
		{
			if(irqTimer)
			{
				if (FLAG == 1){
					buzzer();
					FLAG = 0;
				} 
				
				mode_change();
				
			
				if(MODE_FLAG == 1){ //rtc
					LCD1602_SetCursor(0,1);
					
					sec_ = 300-sec;
					min_ = sec_/60;
					sec__ = sec_%60;
					
					LCD1602_Print("Zostalo: ");
					sprintf(tempMIN, "%i", min_);
					LCD1602_Print(tempMIN);
					LCD1602_Print(":");
					sprintf(tempSEC, "%i", sec__);
					LCD1602_Print(tempSEC);
				
				}
				else{ //kalkulator
						for (int i = 1; i < 5; i++)
						{
								choose_row(i);
							if(print_button(i) != 0)
								calculator(print_button(i));
							
						}
				}
				
			
				
				
				//if( ( PTB->PDIR & (1<<BUTTON_MODE) ) == 0 ){ /* Test if buttón pressed */
					//	PTB->PDOR|=(1<<2); //on
						//while( ( PTB->PDIR & (1<<BUTTON_MODE) ) == 0 ) /* Wait fór release */
							//delay_ms(100); /* Debóuncing */
				//}	
				
				//rtc
				//LCD1602_SetCursor(0,0);
				//sprintf(temp, "%i", sec);
				//LCD1602_Print(temp);
			//	rtc_reset();
				
				
				irqTimer=0;
			}
			
	//	__wfi(); // Save energy and wait for interrupt
	}
}
