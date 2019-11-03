/*	Author: Van Truong
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

double Notes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
int i = 0;
volatile unsigned char TimerFlag = 0; //TimerISR() sets this to 1. C programmers should clear to 0
enum States {SMStart, OFF, WAIT, UP, DOWN, HOLD} state;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	//AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B; //bit3 = 0: CTC mode (clear timer on compare)
					//bit2...bit0 = 11: prescaler /64
					//00001011: 0x0B
					//So 8MHz clock or 8,000,000 /64 = 125,000 ticks/s

	//AVR putput compare register OCR1A
	OCR1A = 125;
	TIMSK1 = 0x02;
	
	//initiate AVR counter
	TCNT1 = 0;
	
	_avr_timer_cntcurr = _avr_timer_M; // TimerISR will be called every _avr_timer_cntcurr milliseconds
	
	//enable global interrupts
	SREG |= 0x80; //0x90: 10000000
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

//set TimerISR() to tick every M ms
void TimerSet (unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void set_PWM(double frequency) {
	static double current_frequency; //keeps track of currently set frequency
	
	//will only update the registers when the frequency changes, otherwise allows music play uninterrupted
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } //resumes/continues timer/counter
	
		//prevents OCR3A from overflowing, using prescaler 64
		//.954 is smallest frequency that will not result in overflow	
		if  (frequency < 0.954) { OCR3A = 0xFFFF; }
			
		//prevents OCR3A from underflowing, using prescaler 64
		//31250 is largest frequency that will not result in underflow
		else if (frequency > 31250)  { OCR3A = 0x0000; }
			
		//set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }
			
		TCNT3 = 0; //resets counter
		current_frequency = frequency; //updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0); //COM3A0 toggle PB3 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
			//WGM32: when counter TCNT3 matches OCR3A, reset counter
			//CS31 & CS30: set a prescaler of 64;
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void Scale() {
	unsigned char A0 = ~PINA & 0x01; //ON/OFF
	unsigned char A1 = ~PINA & 0x02; //UP
	unsigned char A2 = ~PINA & 0x04; //DOWN
	
	switch (state) {
		case SMStart:
			state = OFF;
			break;
			
		case OFF:
			if (A0) {
				state = WAIT;
			}
			else {
				state = OFF;
			}
			break;
			
		case WAIT:
			if (A0) {
				state = OFF;
			}
			else if (A1) {
				state = UP;
			}
			else if (A2) {
				state = DOWN;
			}
			else {
				state = WAIT;
			}
			break;
			
		case UP:
			if (A0) {
				state = OFF;
			}
			else if (A1) {
				state = HOLD;
			}
			else {
				state = WAIT;
			}
			break;
			
		case DOWN:
			if (A0) {
				state = OFF;
			}
			else if (A2) {
				state = HOLD;
			}
			else {
				state = WAIT;
			}
			break;
			
		case HOLD:
			if (A1 || A2) {
				state = HOLD;
			}
			else {
				state = WAIT;
			}
			break;
	}
	
	switch (state) {
		case SMStart:
			break;
		
		case OFF:
			set_PWM(0);
			break;
			
		case WAIT:
			set_PWM(Notes[i]);
			break;
		
		case UP:
			if (i < 7) {
				++i;
				set_PWM(Notes[i]);
			}
			break;
			
		case DOWN:
			if (i > 0) {
				--i;
				set_PWM(Notes[i]);
			}
			break;
			
		case HOLD:
			break;
		
		default:
			break;
	}
}

int main(void)
{	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(100);
	TimerOn();
	PWM_on();
	
	state = SMStart;
	
	while (1)
	{
		Scale();
		while (!TimerFlag);
		TimerFlag = 0;			
	}
}
