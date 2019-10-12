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
enum ID_States {ID_SMStart, ID_PA0Pressed, ID_PA1Pressed, ID_Reset, ID_Wait} ID_State;

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
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
//	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    ID_State = ID_SMStart;

    while (1) {
	TickFct_Latch();
    }
    return 1;
}
