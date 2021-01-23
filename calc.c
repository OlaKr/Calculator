#include "MKL05Z4.h"
#include "calc.h"
#include "buttons.h"
#include "lcd1602.h"
#include "buzzer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char temp[20]={"\0"};
char number[10]={"\0"};
uint8_t reset = 0;
int counter = 0;
char sep[2];
int s = 0;
uint8_t FLAG = 0;
char last_arg = '+';
int result = 0;

void calculator(char arg){
	LCD1602_SetCursor(0, 0);
			LCD1602_Print("Kalkulator");
	LCD1602_SetCursor(0, 1);
			LCD1602_Print("                ");
	
	if(arg == '='){
			temp[counter] = arg;
			LCD1602_SetCursor(0,1);
			LCD1602_Print(temp);
			LCD1602_SetCursor(10,1);
			
			int a = atoi(number);
			if(last_arg == '+'){
				result = result + a;
			}
			
			else if(last_arg == '-'){
				result = result - a;
			}
			
			else if(last_arg == '/'){
				//dzielenie przez 0
				if(a == 0){
					LCD1602_SetCursor(0,1);
					LCD1602_Print("niedozw. ");
					FLAG = 1;
					counter = 0;
					memset(temp,0,sizeof(temp));
					memset(number,0,sizeof(number));
					last_arg = '+';
					reset=0;
					result = 0;
				}
				
				else{
				 result = result / a;
				}
				
			}
			else if(last_arg == '*'){
				result = result * a;
			}
			
			else if(last_arg == '^'){
				result = pow(result,a);
			}
			
			else if(last_arg == 's'){
				result = sqrt(a);
			}
			
			char sm[20]={"\0"};
			LCD1602_SetCursor(12, 1);
			
			tostring(sm, result);
			
			LCD1602_Print(sm);
		
			counter = 0;
			memset(temp,0,sizeof(temp));
			memset(number,0,sizeof(number));
			last_arg = '+';
			reset=0;
			result = 0;
	}
	
	else if (arg == 'C'){
			counter = 0;
			memset(temp,0,sizeof(temp));
			memset(number,0,sizeof(number));
			last_arg = '+';
			reset=0;
			result = 0;
		
	}
	
	else if(arg == '+' || arg == '-' || arg == '*' || arg == '/' || arg == '^' || arg == 's'){

			int a = atoi(number);
			if(last_arg == '+'){
				result = result + a;
			}
			
			else if(last_arg == '-'){
				result = result - a;
			}
			
			else if(last_arg == '/'){
				//dzielenie przez 0
				if(a == 0){
					FLAG = 1;
					LCD1602_SetCursor(0,1);
					LCD1602_Print("niedozw. ");
					counter = 0;
					memset(temp,0,sizeof(temp));
					memset(number,0,sizeof(number));
					last_arg = '+';
					reset=0;
					result = 0;
				}
				
				else{
				 result = result / a;
				}
			}
			
			else if(last_arg == '*'){
				result = result * a;
			}
				
			memset(number,0,sizeof(number));
			
			last_arg = arg;
			temp[counter] = arg;
			LCD1602_SetCursor(0, 1);
			LCD1602_Print(temp);
			counter++;
			reset=0;
			s++;
	}
	
	else{
			
				temp[counter] = arg;
				number[reset] = arg;
				LCD1602_SetCursor(0, 1);
				LCD1602_Print(temp);
				counter++;
				reset++;
			
	}	
}


 void tostring(char str[], int num)
 {
     int i, rem, len = 0, n;
     uint8_t a=0;
     if(num<0){
       n=-num;
       a=1;
		}
     else{
       n=num;
       a=0;
		}
   while (n != 0){
       len++;
       n /= 10;
    }
   if(a==1){
        num=-1*num;
        str[0]='-';
		}

    for (i = 0; i < len; i++){
        rem = num % 10;
        num = num / 10;
        if(a==1){
            str[len - (i)] = rem + '0';
        }
        else{
           str[len - (i + 1)] = rem + '0';
        }   
     }
       if(a==1){
           str[len+1] = '\0';
       }
       else{
           str[len] = '\0';
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

			LCD1602_SetCursor(12, 0);
			LCD1602_Print(sm);


}
