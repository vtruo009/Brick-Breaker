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
enum LEDs {LED_Init, LED_B0, LED_B0_Hold, LED_B1, LED_B1_Hold, LED_B2, LED_B2_Hold, LED_Decr, LED_Incr} LED;
	
unsigned char score = 5;
unsigned char keeper = 0;

void TickFct_Blink() {
	
	unsigned char A0 = ~PINA & 0x01;
	unsigned char A1 = ~PINA & 0x02;
	
	switch (LED) {
		case LED_Init:
			LED = LED_B0;
			break;
		
		case LED_B0:
			if (A0) {
				LED = LED_Decr;
			}
			else {
				LED = LED_B1;
			}
			break;
		
		case LED_B0_Hold:
			if (A0) {
				LED = LED_B1;
			}
			else {
				LED = LED_B0_Hold;
			}
			break;
		
		case LED_B1:
			if (A0) {
				LED = LED_Incr;
			}
			else {
				LED = LED_B2;
			}
			break;
		
		case LED_B1_Hold:
			if (A0) {
				LED = LED_B2;
			}
			else {
				LED = LED_B1_Hold;
			}
			break;
		
		case LED_B2:
			if (A0) {
				LED = LED_Decr;
			}
			else {
				LED = LED_B0;
			}
			break;
		
		case LED_B2_Hold:
			if (A0) {
				LED = LED_B0;
			}
			else {
				LED = LED_B2_Hold;
			}
			break;
			
		case LED_Incr:
			LED = LED_B1_Hold;
			break;
			
		case LED_Decr:
			if (keeper == 2) {
				LED = LED_B2_Hold;
			}
			else if (keeper == 0) {
				LED = LED_B0_Hold;
			}
			break;
			
		default:
			break;
	}
	
	switch (LED) {
		case LED_Init:
			PORTB = 0x00;
			break;
		
		case LED_B0:
			PORTB = 0x01;
			keeper = 0;
			LCD_Cursor(1);
			LCD_WriteData(score + '0');
			break;
			
		case LED_B0_Hold:
			break;
			
		case LED_B1:
			PORTB = 0x02;
			break;
		
		case LED_B1_Hold:
			break;
		
		case LED_B2:
			PORTB = 0x04;
			keeper = 2;
			break;
		
		case LED_B2_Hold:
			break;
			
		case LED_Incr:
			if (score < 9) {
				++score;
				if (score == 9) {
					LCD_DisplayString(1, "YOU WIN!");
				}
				else {
					LCD_Cursor(1);
					LCD_WriteData(score + '0');
				}
			}
			break;
			
		case LED_Decr:
			if (score > 0) {
				--score;
				LCD_Cursor(1);
				LCD_WriteData(score + '0');
			}
			break;
			
		default:
			break;
	}
}

int main (void)
{
	/* Insert application code here, after the board has been initialized. */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_init();
	
	//set and turn on timer
	TimerSet(300);
	TimerOn();
	
	LED = LED_Init;
	
	while (1) {
		TickFct_Blink();
		while(!TimerFlag);
		TimerFlag = 0;
	}
}
