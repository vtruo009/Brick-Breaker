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
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned char tmpA = 0x00;
	unsigned char count = 0x00;
	unsigned char i = 0x00;
	//unsigned char tmpC = 0x00;
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	for (i; i < 0x08; ++i) {
		if ((tmpA >> i) & 0x01) {
			++count;
		}
	}
	PORTC = count;
    }
    return 1;
}
