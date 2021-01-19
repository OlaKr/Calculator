#ifndef calc_h
#include <stdint.h>

void calculator(char arg);
void ParseString(char* str, char* separator);
void getResult(char* str, char* str2, int size);
void power(char* str, char* str2, int size);
extern uint8_t FLAG;

#endif