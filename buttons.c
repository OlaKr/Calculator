#include "MKL05Z4.h"
#include "buttons.h"
#include "lcd1602.h"
		
char tab[16] = {'1','2','3','+','4','5','6','-','7','8','9','*','C','0','=','/'};
uint8_t MODE_FLAG = 0;		


void buttons_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	PORTA->PCR[COLUMNE4] |= PORT_PCR_MUX(1);  // set pin mux as gpio
	PORTA->PCR[COLUMNE3] |= PORT_PCR_MUX(1);
	PORTA->PCR[COLUMNE2] |= PORT_PCR_MUX(1);
	PORTA->PCR[COLUMNE1] |= PORT_PCR_MUX(1);

	PORTA->PCR[ROW4] |= PORT_PCR_MUX(1);  // set pin mux as gpio
	PORTA->PCR[ROW3] |= PORT_PCR_MUX(1);
	PORTA->PCR[ROW2] |= PORT_PCR_MUX(1);
	PORTA->PCR[ROW1] |= PORT_PCR_MUX(1);

	PTA->PDDR |= (1 << ROW4); // set pin as output
	PTA->PDDR |= (1 << ROW3);
	PTA->PDDR |= (1 << ROW2);
	PTA->PDDR |= (1 << ROW1);

	PORTA->PCR[COLUMNE4] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;  // enable pull-up resistor
	PORTA->PCR[COLUMNE3] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[COLUMNE2] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[COLUMNE1] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	
	PORTB->PCR[1] |= PORT_PCR_MUX(1); /* Set Pin 8 MUX as GPIO */
	PORTB->PCR[BUTTON_MODE] |= PORT_PCR_MUX(1); /* Set Pin 1 MUX as GPIO */
	// Enable pull-up resitór ón Pin 1
	PORTB->PCR[BUTTON_MODE] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	PORTB->PCR[6] |= PORT_PCR_MUX(1); /* Set Pin 9 MUX as GPIO */
	PORTB->PCR[BUTTON_POWER] |= PORT_PCR_MUX(1); /* Set Pin 2 MUX as GPIO */
	PORTB->PCR[BUTTON_POWER] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	PORTB->PCR[7] |= PORT_PCR_MUX(1); /* Set Pin 10 MUX as GPIO */
	PORTB->PCR[BUTTON_SQRT] |= PORT_PCR_MUX(1); /* Set Pin 3 MUX as GPIO */
	PORTB->PCR[BUTTON_SQRT] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
}

void choose_row(int option)
{
	switch (option)
	{
	case 1:
		PTA->PDOR &= ~(1 << ROW1); //0
		PTA->PSOR |= (1 << ROW2);
		PTA->PSOR |= (1 << ROW3);
		PTA->PSOR |= (1 << ROW4);
		break;
	case 2:
		PTA->PSOR |= (1 << ROW1);
		PTA->PDOR &= ~(1 << ROW2);
		PTA->PSOR |= (1 << ROW3);
		PTA->PSOR |= (1 << ROW4);
		break;
	case 3:
		PTA->PSOR |= (1 << ROW1);
		PTA->PSOR |= (1 << ROW2);
		PTA->PDOR &= ~(1 << ROW3);
		PTA->PSOR |= (1 << ROW4);
		break;
	case 4:
		PTA->PSOR |= (1 << ROW1);
		PTA->PSOR |= (1 << ROW2);
		PTA->PSOR |= (1 << ROW3);
		PTA->PDOR &= ~(1 << ROW4);
		break;
	}
}

char print_button(int row)
{
	int button;
	char result[5];
	
	if ((PTA->PDIR & (1 << COLUMNE1)) == 0)
	{
		
		button = (row - 1) * 4;
		return tab[button];
		
		while ((PTA->PDIR & (1 << COLUMNE1)) == 0);
	}
	
	else if ((PTA->PDIR & (1 << COLUMNE2)) == 0)
	{
		button = (row - 1) * 4 + 1;
		return tab[button];
		while ((PTA->PDIR & (1 << COLUMNE2)) == 0);
	}
	
	else if ((PTA->PDIR & (1 << COLUMNE3)) == 0)
	{
		button = (row - 1) * 4 + 2;
		return tab[button];
		while ((PTA->PDIR & (1 << COLUMNE3)) == 0);
	}
	
	else if ((PTA->PDIR & (1 << COLUMNE4)) == 0)
	{
		button = (row - 1) * 4 + 3;
		return tab[button];
		while ((PTA->PDIR & (1 << COLUMNE4)) == 0);
	}
	
	else if( ( PTB->PDIR & (1<<BUTTON_POWER) ) ==0 )
		{ /* Test if buttón pressed */
			return '^';
			while( ( PTB->PDIR & (1<<BUTTON_POWER) ) == 0 ) /* Wait fór release */
			delay_ms(100); /* Debóuncing */
		}
	
	else if( ( PTB->PDIR & (1<<BUTTON_SQRT) ) ==0 )
		{ /* Test if buttón pressed */
			return 's';
			while( ( PTB->PDIR & (1<<BUTTON_SQRT) ) == 0 ) /* Wait fór release */
			delay_ms(100); /* Debóuncing */
		}	
	
	
	return 0;
}

void mode_change(void){

	if( ( PTB->PDIR & (1<<BUTTON_MODE) ) == 0 )	{

		if(MODE_FLAG == 1) { //1->0
			PTB->PDOR|=(1<<2); //on
			MODE_FLAG =0;
			//PTB->PDOR&=~(1<<2); //off
			LCD1602_SetCursor(0,0);
			LCD1602_Print("Kalkulator");
			LCD1602_SetCursor(0,1);
			LCD1602_Print("                 ");
		}
		
		else if(MODE_FLAG == 0){
			PTB->PDOR&=~(1<<2); //off
			MODE_FLAG = 1;
			//PTB->PDOR|=(1<<2); //on
			LCD1602_SetCursor(0,0);
			LCD1602_Print("Zegar      ");
			LCD1602_SetCursor(0,1);
			LCD1602_Print("                   ");
		}
		
		while( ( PTB->PDIR & (1<<BUTTON_MODE) ) == 0 ) /* Wait fór release */
			delay_ms(100); /* Debóuncing */
	}
}

void inttostring(char* str, int number) {
	
	int mod, len, num;

	len = 0;
	num = number;

	while (num > 0) {
		num /= 10;
		len++;
	}

	for (int i = 0; i < len; i++) {
		mod = number % 10;
		number /= 10;
		str[len - (i + 1)] = mod + 0x30; //0x30=0 ASCII
	}

	str[len] = '\0';

	if (str[0] == '\0') {
		str[0] = '0';
		str[1] = '\0';
	}
}



