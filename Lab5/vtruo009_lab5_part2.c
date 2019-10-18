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
#include <asf.h>

//void TickFct_Latch(void);

/*enum C_States {C_SMStart, C_initial, C_reset, C_decrement, C_increment, C_wait, C_wait1} C_state;

void TickFct_Latch() {
	PINA = ~PINA;
	switch (C_state) {
		case C_SMStart:
			C_state = C_initial;
			break;
		
		case C_initial:
			if((PINA & 0x03) == 0x03) {
				C_state = C_reset;
			}
			else if (((PINA & 0x03) == 0x02)) {
				C_state = C_decrement;
			}
			else if ((PINA & 0x03) == 0x01) {
				C_state = C_increment;
			}
			else {
				C_state = C_initial;
			}
			break;
			
		case C_decrement:
			C_state = C_wait;
			break;
			
		case C_wait:
			if ((PINA & 0x03) == 0x02) {
				C_state = C_decrement;
			}
			else if ((PINA & 0x03) == 0x01) {
				C_state = C_increment;
			}
			else if ((PINA & 0x03) == 0x03) {
				C_state = C_reset;
			}
			else {
				C_state = C_wait;
			}
			break;
			
		case C_increment:
			C_state = C_wait1;
			break;
			
		case C_wait1:
			if ((PINA & 0x03) == 0x01) {
				C_state = C_increment;
			}
			else if ((PINA & 0x03) == 0x03) {
				C_state = C_reset;
			}
			else if ((PINA & 0x03) == 0x02) {
				C_state = C_decrement;
			}
			else {
				C_state = C_wait1;
			}
			break;
			
		case C_reset:
			if ((PINA & 0x03) == 0x02) {
				C_state = C_decrement;
			}
			else if ((PINA & 0x03) == 0x01) {
				C_state = C_increment;
			}
			else if ((PINA & 0x03) == 0x03) {
					C_state = C_reset;
			}
			else {
				C_state = C_initial;
			}
			break;
			
		default:
			C_state = C_initial;
			break;
	}
	
	switch(C_state) {
		case C_SMStart:
			break;
			
		case C_initial:
			PORTC = 0x00;
			break;
			
		case C_decrement:
			if (PORTC > 0x00) {
				PORTC = PORTC - 1;
			}
			else {
				PORTC = PORTC;
			}
			break;
			
		case C_wait:
			break;
			
		case C_increment:
			if (PORTC < 0x09) {
				PORTC = PORTC + 1;
			}
			else {
				PORTC = PORTC;
			}
			break;
			
		case C_wait1:
			break;
			
		case C_reset:
			PORTC = 0x00;
			break;
			
		default:
			break;
	}

}*/

void TickFct_Latch(void);

enum ID_States {ID_SMStart, ID_Init, ID_Wait, ID_Incr, ID_HoldIncr, ID_Decr, ID_HoldDecr, ID_Reset, ID_HoldReset} ID_State;

void TickFct_Latch() {
	unsigned char A0 = ~PINA & 0x01; //isolate A0
	unsigned char A1 = ~PINA & 0x02; //isolate A1
	//unsigned char PORTC = 0x00;
	
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
		case ID_Init:
			PORTC = 0x00;
			break;
		
		case ID_Wait: 
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

