#include "MKL05Z4.h"
#include "rtc.h"

void rtc_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
	SIM->SOPT1 = SIM_SOPT1_OSC32KSEL(0);
	
	
	/*
	if (RTC_SR_TAF_MASK & RTC_SR_TIF_MASK){
		RTC->TSR = 0x00000000;
	}
	*/
	
	RTC->CR |= RTC_CR_OSCE_MASK|RTC_CR_SC16P_MASK;
	
	int i;
	for(i=0; i<0x600000; i++);
	RTC->SR |= RTC_SR_TCE_MASK;

}

void rtc_reset(void)
{
	
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
	RTC->CR = RTC_CR_SWR_MASK;
	RTC->CR &= ~RTC_CR_SWR_MASK;
	
	
}

uint32_t rtc_update(void)
{
	
	return RTC->TSR;
	
}
