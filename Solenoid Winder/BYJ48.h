/*
 * BYJ48.h
 */

#ifndef BYJ48_H_INCLUDED
#define BYJ48_H_INCLUDED

enum direction {BACKWARD, FORWARD};

class BYJ48
{
	private:
	volatile uint8_t *portOut;
	volatile uint8_t *portIn;
	volatile uint8_t *portCNTRL;
	
	public:
	BYJ48(volatile uint8_t*, volatile uint8_t*, volatile uint8_t*);
	void init();
	void step(direction);
};

#endif