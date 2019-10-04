/*	Author: vtruo009
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #2  Exercise #2
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
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	//unsigned char led = 0x00;
	unsigned char cntavail = 0x00;
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	if (tmpA == 0x00) { // all empty
		cntavail = 0x04;
	}
	else if (tmpA == 0x0F) { // all full
		cntavail = 0x00;
	}
	else if (tmpA == 0x01 || tmpA == 0x02 || tmpA == 0x04 || tmpA == 0x08) { //0001 0010 0100 1000
		cntavail = 0x03;
	}
	else if (tmpA == 0x03 || tmpA == 0x06 || tmpA == 0x0C || tmpA == 0x09 || tmpA == 0x05 || tmpA == 0x0A) { // 0011 0110 1100 1001 1010 0101
		cntavail = 0x02;
	}
	else if (tmpA = 0x0E || tmpA == 0x07 || tmpA == 0x0D || tmpA == 0x0B) { // 0111 1110 1101 1011
		cntavail = 0x01;
	}
	
	PORTC = cntavail; //already sets PC3..PC0
	if (cntavail == 0x00) {
		PORTC = 0x80;

	}
	/*tmpA = PINA;
	tmpB = PINB;
	tmpC = PINC;
	if ((tmpA + tmpB + tmpC) > 0x4C) {
		led = 0x01;
	}
	else {
		led = 0x00;
	}

	if ((tmpA - tmpC) > 0x50 || (tmpC - tmpA) > 0x50) {
		led = led + 0x02;
 	}*/
    }
    return 1;
}
