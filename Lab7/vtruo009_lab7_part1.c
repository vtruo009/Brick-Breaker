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
#include <avr/io.h>
#include <avr/interrupt.h>

#include "io.h"
#include "io.c"

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
unsigned int i = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum ID_States {ID_SMStart, ID_Wait, ID_Init, ID_Incr, ID_HoldIncr, ID_Decr, ID_HoldDecr, ID_Reset, ID_HoldReset} ID_State;

unsigned char score = 0;

void TickFct_Latch() {
	unsigned char A0 = ~PINA & 0x01; //isolate A0 //rmb to add ~ when testing with board
	unsigned char A1 = ~PINA & 0x02; //isolate A1
	
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
			i = 0; 
			break;
		
		case ID_Init:
			score = 0;
			LCD_Cursor(1); //need to add so number will stay in place
			LCD_WriteData(score + '0');
			i = 0;
			break;

		case ID_Incr:
			if (score < 9) {
				++score;
				LCD_Cursor(1);
				LCD_WriteData(score + '0');
				i = 0;
			}
			break;
		
		case ID_HoldIncr:
			if (!(i < 10)) {
				if (score < 9) {
					++score;
					LCD_Cursor(1);
					LCD_WriteData(score + '0');
				}
				i = 0;
			}
			break;
		
		case ID_Decr:
			if (score > 0) {
				--score;
				LCD_Cursor(1);
				LCD_WriteData(score + '0');
				i = 0;
			}
			break;
		
		case ID_HoldDecr:
			if (!(i < 10)) {
				if (score > 0) {
					--score;
					LCD_Cursor(1);
					LCD_WriteData(score + '0');
				}
				i = 0;
			}
			break;
		
		case ID_Reset:
			score = 0;
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			i = 0;
			break;
		
		case ID_HoldReset:
			i = 0;
			break;
		
		default:
			break;
	}
	++i;
}

int main (void)
{
	/* Insert application code here, after the board has been initialized. */
	DDRA = 0x00; PORTA = 0xFF;
	//DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_init();
	
	//set and turn on timer
	TimerSet(100);
	TimerOn();
	
	ID_State = ID_SMStart;
	
	while (1) {
		TickFct_Latch();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
