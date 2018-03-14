#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "Keypad.h"

char KEYPAD_LABELS[16] = {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

Keypad::Keypad(volatile uint8_t *Out, volatile uint8_t *In, volatile uint8_t *CNTRL)
{
	portOut = Out;
	portIn = In;
	portCNTRL = CNTRL;
	*portCNTRL = 0b11110000;
	*portOut = 0b11111111;
}

char Keypad::readChar(uint8_t *valid)
{
	while(true)
	{
		for(uint8_t i = 0; i<sizeof(valid); i++)
		{
			*portOut = ~(0b00010000 << (valid[i] / 4));
			_delay_ms(1);
			if((*portIn & (0b00000001 << (valid[i] % 4))) == 0)
			{
				_delay_ms(5);
				return KEYPAD_LABELS[valid[i]];
			}
		}
	}
}

char* Keypad::readStr(uint8_t valid[], char endChar, char backChar)
{
	char inChar = ' ';
	char str[20];
	uint8_t index = 0;
	while(inChar != endChar)
	{
		inChar = readChar(valid);
		if(inChar == backChar)
		{
			index--;
			str[index] = ' ';
		}
		else if(inChar != endChar)
		{
			str[index] = inChar;
			index++;
		}
	}
	char *outChar = (char*)malloc(sizeof(char)*(index+1));
	for(uint8_t i = 0; i < index; i++)
	{
		outChar[i] = str[i];
	}
	return outChar;
}



