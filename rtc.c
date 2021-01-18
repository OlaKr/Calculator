#include "MKL05Z4.h"
#include "rtc.h"

void rtc_init(void)
{
	SIM->SCGC6 |= SIM_SCGC6_RTC_MASK;
	SIM->SOPT1 &= ~SIM_SOPT1_OSC32KSEL_MASK;
	SIM->SOPT1 = SIM_SOPT1_OSC32KSEL(0);
	
	RTC->TSR = 1;
	RTC->IER |= RTC_IER_TSIE_MASK;
	RTC->CR |= RTC_CR_OSCE_MASK|RTC_CR_SC16P_MASK;
	
	int i;
	for(i=0; i<0x800000; i++);
	RTC->SR |= RTC_SR_TCE_MASK;

	NVIC_EnableIRQ(RTC_Seconds_IRQn);
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
