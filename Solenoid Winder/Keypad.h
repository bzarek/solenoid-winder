/*
 * Keypad.h
 */

#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

class Keypad
{
	private:
	volatile uint8_t *portOut;
	volatile uint8_t *portIn;
	volatile uint8_t *portCNTRL;
	
	public:
	Keypad(volatile uint8_t*, volatile uint8_t*, volatile uint8_t*);
	char readChar(uint8_t[]);
	char* readStr(uint8_t[], char, char);
	
};

#endif