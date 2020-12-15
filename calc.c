#include "MKL05Z4.h"
#include "calc.h"
#include "buttons.h"
#include "lcd1602.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char temp[20]={"\0"};
int counter = 0;
char sep[2];

void calculator(char arg){
	LCD1602_SetCursor(0, 0);
			LCD1602_Print("                ");
	LCD1602_SetCursor(0, 1);
			LCD1602_Print("                ");
	
	if(arg == '='){
			temp[counter] = arg;
			LCD1602_SetCursor(0, 0);
				LCD1602_Print(temp);
			LCD1602_SetCursor(0, 1);
				LCD1602_Print("=");
		ParseString(temp, sep);
		
		
			counter = 0;
			memset(temp,0,sizeof(temp));
	}
	else if (arg == 'C'){
			counter = 0;
			memset(temp,0,sizeof(temp));
	}
	else if(arg == '+' || arg == '-' || arg == '*' || arg == '/'){
			sep[0] = arg;
			temp[counter] = arg;
			LCD1602_SetCursor(0, 0);
			LCD1602_Print(temp);
			counter++;
	}
	else{
			temp[counter] = arg;
			LCD1602_SetCursor(0, 0);
			LCD1602_Print(temp);
			counter++;
	}
		

		
	
}

void ParseString(char* str, char* separator)
{
	char sm[20]={"\0"};
	uint8_t i=0;
	char *ptr;
	ptr=strtok(str,separator);
	int a = atoi(ptr);
	ptr=strtok(NULL,'=');
	int b = atoi(ptr);
	int result;
	if(separator[0] =='+') result = a+b;
	else if(separator[0] =='-') result = a-b;
	else if(separator[0] =='*') result = a*b;
	else if(separator[0] =='/') result = a/b;
	inttostring(sm,result);
	LCD1602_Print(sm);
}