#ifndef buttons_h
#define buttons_h
#include <stdint.h>

#define ROW1 5
#define ROW2 6
#define ROW3 7
#define ROW4 8

#define COLUMNE1 9
#define COLUMNE2 10
#define COLUMNE3 11
#define COLUMNE4 12


#define BUTTON_MODE 1
#define BUTTON_POWER 6
#define BUTTON_SQRT 7

void buttons_init(void);
void choose_row(int option);
char print_button(int row);
void inttostring(char* str, int number);
void mode_change(void);
extern uint8_t MODE_FLAG;

#endif

