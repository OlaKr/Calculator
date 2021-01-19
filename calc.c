#include "MKL05Z4.h"
#include "calc.h"
#include "buttons.h"
#include "lcd1602.h"
#include "buzzer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char temp[20]={"\0"};
int counter = 0;
char sep[2];
int s = 0;

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
		//ParseString(temp, sep);
		getResult(temp, temp, s);
		
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
			s++;
	}
	else{
			temp[counter] = arg;
			LCD1602_SetCursor(0, 0);
			LCD1602_Print(temp);
			counter++;
	}
		

		
	
}



void getResult(char* str, char* str2, int size) {

    char c2[20];
    strcpy(c2, str2);

    int liczby[20];
    char dzialania[20] = { "\0" };

    char* pch;
    pch = strtok(str, "+-*/");

    int counter1 = 0;
    while (pch != NULL)
    {
        int a = atoi(pch);
        liczby[counter1] = a;
        counter1 = counter1 + 1;
        //printf("%s\n", pch);
        pch = strtok(NULL, "+-*/");
    }

   
    char* pch2;
    pch2 = strtok(c2, "0123456789");
    int counter2 = 0;
    while (pch2 != NULL)
    {
        dzialania[counter2] = *(pch2);
        counter2++;
        //printf("%s\n", pch2);
        pch2 = strtok(NULL, "0123456789");
    }

			char* p;
			int i;
			p = dzialania;

			int result = liczby[0];
			for (i = 0; i < size; i++) {
					char tmp = *p;
					switch (tmp) {

					case '+':
							result = result + liczby[i + 1];
							break;
					case '-':
							result = result - liczby[i + 1];
							break;
					case '/':
							result = result / liczby[i + 1];
							break;
					case '*':
							result = result * liczby[i + 1];
							break;
					}
					p++;
			}
			char sm[20]={"\0"};
			inttostring(sm,result);
			LCD1602_Print(sm);
		

   
		
   // printf("%d", result); 

}