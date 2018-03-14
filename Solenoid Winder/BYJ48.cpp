#include <avr/io.h>
#include "BYJ48.h"
	
BYJ48::BYJ48(volatile uint8_t *Out, volatile uint8_t *In, volatile uint8_t *CNTRL)
{
	portOut = Out;
	portIn = In;
	portCNTRL = CNTRL;
}

void BYJ48::init()
{
	*portOut = 0b00000001;			//starting output
	*portCNTRL = 0b00001111;		//enable 4 LSBs as outputs
}

void BYJ48::step(direction dir)
{
	uint8_t current = *portIn;
	if(dir == FORWARD)
	{
		if(current >= 0b00001000)
		{
			*portOut = 0b00000001;
		}
		else
		{
			*portOut = current << 1;
		}
	}
	else
	{
		if(current == 0b00000001)
		{
			*portOut = 0b00001000;
		}
		else
		{
			*portOut = current >> 1;
		}
	}
}