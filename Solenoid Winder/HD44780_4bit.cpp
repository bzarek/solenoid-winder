
/*
 * This file implements commonly used functions for a 16x2 LCD display, assuming the LCD
 * utilizes the HD44780 Display Controller/Driver. 
 *
 * The following methods assume operation in 4 bit mode. This mode requires two cycles to 
 * transfer data to the LCD controller, but utilizes less pins on the microcontroller. 
 * The pinout on the microcontroller is as follows.
 *
 * Pin 7: Register Select (RS): 0 for Instruction, 1 for Data
 * Pin 6: Read/Write (R/W): 0 for write, 1 for read
 * Pin 5: Enable (E): toggle to execute, falling edge trigger
 * Pin 4: --
 * Pin 3: Data Bus Bit 7
 * Pin 2: Data Bus Bit 6
 * Pin 1: Data Bus Bit 5
 * Pin 0: Data Bus Bit 4
 *
 */


#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "HD44780_4bit.h"
	
HD44780_4bit::HD44780_4bit(volatile uint8_t *Out, volatile uint8_t *In, volatile uint8_t *CNTRL)
{
	portOut = Out;
	portIn = In;
	portCNTRL = CNTRL;
	*portOut = 0b00000000;			//starting output
	*portCNTRL = 0b11101111;		//enable pins as outputs
}

void HD44780_4bit::toggleEnable()
{
	*portOut |= 0b00100000;		//set enable high, others unchanged
	*portCNTRL |= 0b00100000;		//set enable pin as output
	_delay_us(1);
	*portOut &= 0b11011111;		//set enable low, others unchanged
	_delay_us(1);
}

void HD44780_4bit::enter4BitMode()
{
	*portOut = 0b00100010;				//command for 4 bit mode
	*portCNTRL = 0b11111111;			//set all pins as outputs
	toggleEnable();
}


void HD44780_4bit::sendInstruction(uint8_t instr)
{
	*portOut = (0b00100000 | ((instr>>4)&(0b00001111)));	//set control bits and MSBs
	*portCNTRL = 0b11111111;									//set all pins as outputs
	toggleEnable();
	*portOut = (0b00100000 | ((instr)&(0b00001111)));		//set control bits and LSBs
	toggleEnable();
	_delay_us(37);		//max instruction time
}

void HD44780_4bit::writeChar(char letter)
{
	*portOut = (0b10100000 | ((letter>>4)&(0b00001111)));	//set control bits and MSBs
	*portCNTRL = 0b11111111;										//set all pins as outputs
	toggleEnable();
	*portOut = (0b10100000 | ((letter)&(0b00001111)));		//set control bits and LSBs
	toggleEnable();
}

void HD44780_4bit::clear()
{
	sendInstruction(0b00000001);
	_delay_ms(5);
}

void HD44780_4bit::move(uint8_t pos)
{
	sendInstruction(0b10000000 | pos);
}

void HD44780_4bit::print(char* str, uint8_t pos)
{
	move(pos);
	for(uint8_t i = 0; i < strlen(str); i++)
	{
		writeChar(str[i]);
	}
}

void HD44780_4bit::print(char* str)
{
	for(uint8_t i = 0; i < strlen(str); i++)
	{
		writeChar(str[i]);
	}
}

void HD44780_4bit::setMode(uint8_t settings)
{
	/*
	 * Sets up the LCD display given the following bit in settings
	 *
	 * MSB
	 * Bit 7: Don't Care
	 * Bit 6: 0 = Display OFF;		1 = Display ON
	 * Bit 5: 0 = Cursor OFF		1 = Cursor ON
	 * Bit 4: 0 = Blinking OFF		1 = Blinking ON
	 * Bit 3: 0 = 1 line display	1 = 2 line display
	 * Bit 2: 0 = 5x8 dot display	1 = 5x10 dot display
	 * Bit 1: 0 = Decrement			1 = Increment
	 * Bit 0: 0 = No shift			1 = Shift display
	 */
	enter4BitMode();
	sendInstruction((settings & 0b00001100) | 0b00100000);
	sendInstruction((settings & 0b00000011) | 0b00000100);
	sendInstruction(((settings>>4) & 0b00000111) | 0b00001000);
}
