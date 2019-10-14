/*	Author: vtruo009
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum LED_States {LED_SMStart, LED_OFFRelease, LED_ONRelease, LED_OFFPress, LED_ONPress} LED_State;

void TickFct_Latch() {
	unsigned char tmpA = PINA;
	unsigned char tmpB = 0x01;
	switch (LED_State) {
		case LED_SMStart:
			LED_State = LED_OFFRelease;
			break;
		case LED_OFFRelease:
			if (tmpA) {
				LED_State = LED_ONPress;
			}
			else if (!tmpA) {
				LED_State = LED_OFFRelease;
			}
			break;
		
		case LED_ONPress:
			if (tmpA) {
				LED_State = LED_ONPress;
			}
			else if (!tmpA) {
				LED_State = LED_ONRelease;
			}
			break;
		
		case LED_ONRelease:
			if (tmpA) {
				LED_State = LED_ONPress;
			}
			else if (!tmpA) {
				LED_State = LED_ONRelease;
			}
			break;

		case LED_OFFPress:
			if (tmpA) {
				LED_State = LED_OFFPress;
			}
			else if (!tmpA) {
				LED_State = LED_OFFRelease;
			}
			break;

		default:
			LED_State = LED_SMStart;
			break;
	}

	switch (LED_State) {
		case LED_SMStart:
			break;

		case LED_OFFRelease:
			tmpB = 0x01;
			break;
		
		case LED_ONPress:
			tmpB = 0x02;
			break;
		
		case LED_ONRelease:
			tmpB = 0x02;
			break;

		case LED_OFFPress:
			tmpB = 0x01;
			break;
		
		default:
			break;
	}
	PORTB = tmpB;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
//	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    LED_State = LED_SMStart;

    while (1) {
	TickFct_Latch();
    }
    return 1;
}
