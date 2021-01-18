#include "MKL05Z4.h"
#include "buttons.h"
#include "calc.h"
#include "lcd1602.h"
#include "pit.h"
#include "i2c.h"
#include "rtc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {false, true} bool;


bool irqTimer=0;
uint32_t sec=0;

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

int main(void) {

	LCD1602_Init(); /* initialize LCD */
	LCD1602_Backlight(TRUE);
	rtc_init();
	buttons_init();
	PIT_Init();
	char temp[20]={"\0"};
	while (1) 
		{
			if(irqTimer)
			{
				for (int i = 1; i < 5; i++)
				{
			//			choose_row(i);
			//		if(print_button(i) != 0)
			//			calculator(print_button(i));
					
				}
				LCD1602_SetCursor(0,0);
				sprintf(temp, "%i", sec);
	LCD1602_Print(temp);
				irqTimer=0;
			}
			
	//	__wfi(); // Save energy and wait for interrupt
	}
}
