#include "MKL05Z4.h"
#include "buttons.h"
#include "calc.h"
#include "lcd1602.h"
#include "pit.h"
#include "i2c.h"
#include "rtc.h"
#include "buzzer.h"
#include "led.h"
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
	volatile int i1;
	volatile int i2;
	for( i1 = 0 ; i1 < n; i1++)
	for(i2 = 0; i2 < 3500; i2++) {}
}


int main(void) {

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	//buzzer
	PORTB->PCR[13] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<13);
	
	//dioda glowna
	PORTB->PCR[2] |= PORT_PCR_MUX(1); /* MUX cónfig. Set Pin 8 óf PORT B as GPIO */
	PTB->PDDR |= (1<<2);
	PTB->PDOR|=(1<<2); //on
	delay_ms(1000);

	
	led_init();
	
	LCD1602_Init(); /* initialize LCD */
	LCD1602_Backlight(TRUE);
	LCD1602_SetCursor(0,0);
	LCD1602_Print("Kalkulator");
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
				
						
					if (sec == 295)
					turn_off();
					
					if(sec >= 300){
						LCD1602_SetCursor(0,0);
						LCD1602_Print("Zegar");
						LCD1602_SetCursor(0,1);
						LCD1602_Print("KONIEC CZASU!!!!!      ");
						
					}
					
					else{
						LCD1602_Print("Zostalo: ");
						sprintf(tempMIN, "%i", min_);
						LCD1602_Print(tempMIN);
						LCD1602_Print(":");
						
						if (sec__ <10){
						LCD1602_Print("0");
						}
						
						sprintf(tempSEC, "%i", sec__);
						LCD1602_Print(tempSEC);
					}
					
				}
				else{ //kalkulator
					
						for (int i = 1; i < 5; i++)
						{
							choose_row(i);
							if(print_button(i) != 0)
								calculator(print_button(i));
							
						}
				}	
				irqTimer=0;
			}	
	}
}
