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

/*enum states {SMStart, NPressed, Locked, Unlocked} state;

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

}*/

//part 1
/*enum LED_States {LED_SMStart, LED_OFFRelease, LED_ONPress, LED_ONRelease, LED_OFFPress} LED_State;

void TickFct_Latch() {
	unsigned char tmpA = PINA & 0x01 // isolate bit 0;
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
				LED_State = LED_OFFPress;
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
}*/

//part 2
/*enum ID_States {ID_SMStart, ID_Wait, ID_PA0Pressed, ID_PA1Pressed, ID_Reset} ID_State;

void TickFct_Latch() {
	unsigned char A0 = PINA & 0x01; //isolate PA0
	unsigned char A1 = PINA & 0x02; //isolate PA1
	unsigned char result = 0x07;
	switch (ID_State) {
		case ID_SMStart:
			ID_State = ID_Wait;
			break;

		case ID_Wait:
			if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			else if ((A0 && !A1) && (result < 9)) {
				ID_State = ID_PA0Pressed;
			}
			else if ((!A0 && A1) && (result > 0)) {
				ID_State = ID_PA1Pressed;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			break;

		case ID_PA0Pressed:
			if (A0 && !A1) {
				ID_State = ID_PA0Pressed;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			else if (!A0 && A1) {
				ID_State = ID_PA1Pressed;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			break;

		case ID_PA1Pressed:
			if (!A0 && A1) {
				ID_State = ID_PA1Pressed;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			else if (A0 && !A1) {
				ID_State = ID_PA0Pressed;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			break;

		case ID_Reset:
			if (A0 && A1) {
				ID_State = ID_Reset;
			}
			else if (A0 && !A1) {
				ID_State = ID_PA0Pressed;
			}
			else if (!A0 && A1) {
				ID_State = ID_PA1Pressed;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}

		default:
			ID_State = ID_SMStart;
	}

	switch (ID_State) {
		case ID_Wait:
			break;

		case ID_PA0Pressed:
			++result;
			break;

		case ID_PA1Pressed:
			--result;
			break;

		case ID_Reset:
			result = 0x00;
			break;
		default:
			break;
	}
	PORTB = result;	
}*/

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    //LED_State = LED_SMStart;
	//ID_State = ID_SMStart;
	//state = SMStart;

    while (1) {
	TickFct_Latch();
    }
    return 1;
}
