/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void TickFct_Latch(void);

enum ID_States {ID_SMStart, ID_Wait, ID_Init, ID_Incr, ID_HoldIncr, ID_Decr, ID_HoldDecr, ID_Reset, ID_HoldReset} ID_State;

void TickFct_Latch() {
	unsigned char A0 = PINA & 0x01; //isolate A0 //rmb to add ~ when testing with board
	unsigned char A1 = PINA & 0x02; //isolate A1
	
	switch(ID_State) { //transitions
		case ID_SMStart:
			ID_State = ID_Init;
			break;
		
		case ID_Wait:
			if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			else if (A0 && !A1) {
				ID_State = ID_Incr;
			}
			else if (!A0 && A1) {
				ID_State = ID_Decr;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			break;
		
		case ID_Init:
			if (A0 && !A1) {
				ID_State = ID_Incr;
			}
			else if (!A0 && A1) {
				ID_State = ID_Decr;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Init;
			}
			break;
		
		case ID_Incr:
			if (A0 && !A1) {
				ID_State = ID_HoldIncr;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			break;
		
		case ID_HoldIncr:
			if (A0 && !A1) {
				ID_State = ID_HoldIncr;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			break;
		
		case ID_Decr:
			if (!A0 && A1) {
				ID_State = ID_HoldDecr;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			break;
		
		case ID_HoldDecr:
			if (!A0 && A1) {
				ID_State = ID_HoldDecr;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			else if (A0 && A1) {
				ID_State = ID_Reset;
			}
			break;
		
		case ID_Reset:
			if (A0 && A1) {
				ID_State = ID_HoldReset;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
		
			case ID_HoldReset:
			if (A0 && A1) {
				ID_State = ID_HoldReset;
			}
			else if (!A0 && !A1) {
				ID_State = ID_Wait;
			}
			break;
	}
	
	switch (ID_State) {
		case ID_Wait: 
			break;
		
		case ID_Init:
			PORTC = 0x00;
			break;

		case ID_Incr:
			if (PORTC < 9) {
				PORTC = PORTC + 0x01;
			}
			break;
		
		case ID_HoldIncr:
			break;
		
		case ID_Decr:
			if (PORTC > 0) {
				PORTC = PORTC - 0x01;
			}
			break;
		
		case ID_HoldDecr:
			break;
		
		case ID_Reset:
			PORTC = 0x00;
			break;
		
		case ID_HoldReset:
			break;
		
		default:
			break;
	}
	
	//PORTC = result;
}
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	//board_init();
	/* Insert application code here, after the board has been initialized. */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	ID_State = ID_SMStart;
	
	while (1) {
		TickFct_Latch();
		//PORTC = 0x0F;
	}
	
	return 1;
}

