/*
 * Solenoid Winder.cpp
 *
 * Created: 1/13/2018 5:22:14 PM
 * Author : bzarek
 */ 

# define F_CPU 1000000UL	//this sets the clock speed for delay functions in <util/delay.h>

#include <avr/io.h>
#include <util/delay.h>
//#include "BYJ48.h"
#include "HD44780_4bit.h"
#include "Keypad.h"

uint8_t ALL_KEYS[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

static void init()
{
	TCCR0A = 0b00000101;	//timer setup: CLK/1024 in normal operation mode
	TIMSK0 = 0b00000001;	//timer overflow interrupt enable ON
}

int main(void)
{
	init();
	
	//Initialize LCD Screen for Port D
	HD44780_4bit LCD1 = HD44780_4bit(&PORTD, &PIND, &DDRD);
	LCD1.setMode(0b01001010);
	LCD1.clear();
	
	//Initialize Keypad for Port C
	Keypad keypad1 = Keypad(&PORTC, &PINC, &DDRC);
	
	//Read keypad input and display to screen
	
    while (1) 
    {
		uint8_t testVect[] = {0,1,2,3,4,5};
		char input = keypad1.readChar(testVect);
		LCD1.writeChar(input);
		_delay_ms(500);
    }
}

