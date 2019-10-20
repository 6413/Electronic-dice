#include <avr/io.h>
#include <util/delay.h>
#define BUTTON !(PINB &(1<<PB4))
#define NUMBERS 6
void delay_ms_my(unsigned int delay) {
	for (unsigned int i = delay; 0 < i; i--) {
		_delay_ms(1);
	}
}

void OpenLed(unsigned char LedNum) {
	unsigned char array[] = { 0x11, 0x18, 0x19, 0x1C, 0x1D, 0x1E };
	PORTB = array[LedNum];
}

void StartSpin(unsigned char LedNum, unsigned char rand) {
	unsigned int delay = 100;
	unsigned int ind = 0;
	while (BUTTON) {
		OpenLed(LedNum);
		delay_ms_my(delay);
		LedNum++;
		if (LedNum == NUMBERS) {
			LedNum -= NUMBERS;
		}
	}
	while (delay < 300) {
		OpenLed(LedNum);
		delay_ms_my(delay);
		LedNum++;
		if (LedNum == NUMBERS) {
			LedNum -= NUMBERS;
			delay += 100;
		}
	}
	while (LedNum != rand) {
		OpenLed(LedNum);
		delay_ms_my(delay);
		LedNum++;
	}
	delay = 0;
	while (delay < 6) {
		delay_ms_my(100);
		OpenLed(LedNum);
		delay_ms_my(100);
		PORTB = 0x10;
		rand++;
		if (rand == 6) {
			rand == 0;
		}
		delay++;
		if (delay == 6) {
			ind = 1;
		}
	}
	OpenLed(LedNum);
}

MainLoop(unsigned char LedNum) {
	while (1) {
		if (LedNum == NUMBERS)
		LedNum -= NUMBERS;
		if (BUTTON)
		StartSpin(LedNum);
	}
}

int main(void) {
	DDRB = 0x2F;
	PORTB = 0x10;
	MainLoop(0);
}