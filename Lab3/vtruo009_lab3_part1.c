/*	Author: vtruo009
 *  Partner(s) Name: An Pho
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	unsigned char tmpA = PINA;
	unsigned char tmpB = PINB;
/*	unsigned char tmpC = 0x00;

	if ((tmpA == 0x01) || (tmpA == 0x02)) {
		tmpC = 0x60;
	}
	else if ((tmpA == 0x03) || (tmpA == 0x04)) {
		tmpC = 0x70;
	}
	else if ((tmpA == 0x05) || (tmpA == 0x06)) {
		tmpC = 0x34;
	}
	else if ((tmpA == 0x07) || (tmpA == 0x08) || (tmpA == 0x09)) {
		tmpC = 0x3C;
	}
	else if ((tmpA == 0x0A) || (tmpA == 0x0B) || (tmpA == 0x0C)) {
		tmpC = 0x3E;
	}
	else if ((tmpA == 0x0D) || (tmpA == 0x0E) || (tmpA == 0x0F)) {
		tmpC = 0x3F;
	}

	PORTC = tmpC;*/
	unsigned char count = 0x00;
	unsigned char i = 0x00;
	tmpA = PINA;
	tmpB = PINB;
	for (i; i < 0x08; ++i) {
		if ((tmpA >> i) & 0x01 == 0x01) {
			++count;
		}
		if ((tmpB >> i) & 0x01) {
 			++count;
 		}
	}
	PORTC = count;





    }
    return 1;
}
