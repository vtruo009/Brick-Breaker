/*	Author: vtruo009
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #2  Exercise #1
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
	unsigned char tmpB = 0x00;
	unsigned char tmpA = 0x00;

    /* Insert your solution below */
    while (1) {
	tmpB = PINA & 0x01; //PA0
	tmpA = PINA & 0x02; //PA1
	if (tmpB == 0x01 && tmpA == 0x00) {
		PORTB = 0x01;
	}
	else {
		PORTB = 0x00;
	}
    }
    return 1;
}
