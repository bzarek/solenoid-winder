#ifndef HD44780_4BIT_H_INCLUDED
#define HD44780_4BIT_H_INCLUDED

class HD44780_4bit
{
	private:
	volatile uint8_t *portOut;
	volatile uint8_t *portIn;
	volatile uint8_t *portCNTRL;
	
	public:
	HD44780_4bit(volatile uint8_t*, volatile uint8_t*, volatile uint8_t*);
	void toggleEnable();
	bool isBusy();
	void enter4BitMode();
	void sendInstruction(uint8_t);
	void writeChar(char);
	void clear();
	void move(uint8_t);
	void print(char*, uint8_t);
	void print(char*);
	void setMode(uint8_t);
};

#endif