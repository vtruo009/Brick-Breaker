/*	Author: vtruo009
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #3  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
/*	unsigned char tmpA = PINA;
	unsigned char fuelMask = 0x40;
	unsigned char seatbeltLight = 0x80;
	unsigned char tmpC = 0x00;

	if ((tmpA & 0x0F) <= 0x02) {
		tmpC = 0x20 | fuelMask;
	}
	else if ((tmpA & 0x0F) <= 0x04) {
		tmpC = 0x30 | fuelMask;
	}
	else if ((tmpA & 0x0F) <= 0x06) {
		tmpC = 0x38;
	}
	else if ((tmpA & 0x0F) <= 0x09) {
		tmpC = 0x3C;
	}
	else if ((tmpA & 0x0F) <= 0x0C) {
		tmpC = 0x3E;
	}
	else if ((tmpA & 0x0F) <= 0x0F) {
		tmpC = 0x3F;
	}
	
	if ((tmpA & 0x70) == 0x30) {
		tmpC = tmpC | seatbeltLight;
	}

	PORTC = tmpC;*/

	unsigned char tmpA = PINA;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;

	tmpB = (tmpA >> 4) & 0xFF;
	PORTB = tmpB;

	tmpC = (tmpA << 4) & 0xFF;
	PORTC = tmpC;

    }
    return 1;
}
