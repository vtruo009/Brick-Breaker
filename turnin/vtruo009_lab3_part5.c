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
	//DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	unsigned char inputA = 0x00;
	unsigned char tempB = 0x00;
    while (1) {
	inputA = PINA & 0xFF;
	if(inputA >= 0x46) {
		tempB = 0x02;
	}
	else if((inputA > 0x05) && (inputA < 0x46)) {
		tempB = 0x04;
	}
	else if(inputA <= 0x05) {
		tempB = 0x00;
	}
	PORTC = tempB;
    }
    return 1;
}
