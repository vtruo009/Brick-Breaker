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

enum states {SMStart, NPressed, Locked, Unlocked} state;

void TickFct_Latch() {
	unsigned char X = PINA & 0x01; //isolate PA0
	unsigned char Y = PINA & 0x02; //isolate PA1
	unsigned char P = PINA & 0x04; //isolate PA2
	unsigned char P7 = PINA & 0x80; //isolate PA7
	unsigned char door = 0x00;
	unsigned char tmpC = 0x00;
	switch(state) {
		case SMStart:
			state = Locked;
			break;

		case Locked:
			if (P && !X && !Y && !P7) { //check if # is pressed. y: cont. to state NPressed to get Y
				state = NPressed;
			}
			else {	//# is not pressed, door remains locked
				state = Locked;
			}

			case NPressed: //check for Y
				if (Y) {
					state = Unlocked;
				}
				else {
					state = Locked;
				}
				break;

		case Unlocked:
			if (P7) {
				state = Locked;
			}
			else {
				state = Unlocked;
			}
			break;

		default:
			state = Locked;
	}

	switch (state) {
		case SMStart:
			tmpC = SMStart;
			break;

		case Locked:
			door = 0x00;
			tmpC = Locked;
			break;
			case NPressed:
				tmpC = NPressed;
			break;

		case Unlocked:
			door = 0x01;
			tmpC = Unlocked;
			break;

		default:
			break;
	}
	PORTC = tmpC;
	PORTB = door;

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    state = SMStart;

    while (1) {
	TickFct_Latch();
    }
    return 1;
}
