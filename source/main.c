/*	Author: vtruo009
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	//ADEN: setting this bit enables analog-to-digital conversion
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	ADC_init();

    /* Insert your solution below */
    while (1) {
	unsigned short tmp = ADC;
	unsigned char PB = (char)tmp;
	unsigned char PD = (char)(tmp >> 4);
	PORTB = PB;
	PORTD = PD;
    }
    return 1;
}
