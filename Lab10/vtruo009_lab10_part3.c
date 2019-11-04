/*	Author: Van Truong
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #10  Exercise #3
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

//TASK STRUCT SETUP
typedef struct task {
	int state; //current state of the task
	unsigned long period; //rate at which the task should tick
	unsigned long elapsedTime; //time since task's previous tick
	int (*TickFct)(int); //function to call for task's tick
} task;

task tasks[3];

const unsigned char tasksNum = 3;
const unsigned long tasksPeriodGCD = 2, periodBL = 1000, periodTL = 300, periodSpeaker = 2;
unsigned char B = 0x00, B3 = 0x00/*, B4 = 0x00*/;

enum BL_States {BL_SMStart, ON};
int BlinkLED(int state);

enum TL_States {TL_SMStart, LED0, LED1, LED2};
int ThreeLEDs(int state);

enum Speaker_States {S_SMStart, SpeakerOFF, SpeakerON};
int Speaker(int state);

void Combine();

//TIMER SETUP
volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	//AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B; //bit3 = 0: CTC mode (clear timer on compare)
	//bit2...bit0 = 11: prescaler /64
	//00001011: 0x0B
	//So 8MHz clock or 8,000,000 /64 = 125,000 ticks/s

	//AVR putput compare register OCR1A
	OCR1A = 125; //timer interrupt will be generated when TCNT == OCR1A
	TIMSK1 = 0x02; //bit1: OCIE1A -- enables compare match interrupt
	
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
	//TimerFlag = 1;
	unsigned char i;
	for (i = 0; i < tasksNum; ++i) {
		if (tasks[i].elapsedTime >= tasks[i].period) {
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
			tasks[i].elapsedTime = 0;
		}
		tasks[i].elapsedTime += tasksPeriodGCD;
	}
	//PORTB = 0xFF;
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

int main (void)
{
	/* Insert application code here, after the board has been initialized. */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	//set task variables
	unsigned char i = 0;
	tasks[i].state = BL_SMStart;
	tasks[i].period = periodBL;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &BlinkLED;
	++i;
	tasks[i].state = TL_SMStart;
	tasks[i].period = periodTL;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &ThreeLEDs;
	++i;
	tasks[i].state = S_SMStart;
	tasks[i].period = periodSpeaker;
	tasks[i].elapsedTime = tasks[i].period;
	tasks[i].TickFct = &Speaker;
	
	TimerSet(tasksPeriodGCD);
	TimerOn();
	
	while (1) {
// 		while(!TimerFlag);
// 		TimerFlag = 0;
		Combine();
	}
	return 0;
}

//Blink LED SM
int BlinkLED(int state) {
	switch (state) {
		case BL_SMStart:
			state = ON;
			break;
		case ON:
			state = BL_SMStart;
			break;
		default:
			state = BL_SMStart;
			break;
	}
	
	switch (state) {
		case BL_SMStart:
			B3 = 0x00;
			break;
		case ON:
			B3 = 0x08;
			break;
		default:
			break;
	}
	return state;
}

int ThreeLEDs(int state) {
	switch (state) {
		case TL_SMStart:
			state = LED0;
			break;
		case LED0:
			state = LED1;
			break;
		case LED1:
			state = LED2;
			break;
		case LED2:
			state = LED0;
			break;
		default:
			state = TL_SMStart;
			break;
	}
	
	switch (state) {
		case TL_SMStart:
			break;
		case LED0:
			B = 0x01;
			break;
		case LED1:
			B = 0x02;
			break;
		case LED2:
			B = 0x04;
			break;
		default:
			break;
	}
	return state;
}

int Speaker(int state) {
	unsigned char A2 = ~PINA & 0x04;
	switch (state) {
		case S_SMStart:
			state = SpeakerOFF;
			break;
		case SpeakerOFF:
			if (A2) {
				state = SpeakerON;
			}
			else {
				state = SpeakerOFF;
			}
			break;
		case SpeakerON:
			if (!A2) {
				state = SpeakerOFF;
			}
			else {
				state = SpeakerON;
			}
			break;
		default:
			state = S_SMStart;
	}
	
	switch (state) {
		case S_SMStart:
			break;
		case SpeakerOFF:
			PORTB = 0x00;
			break;
		case SpeakerON:
			PORTB = 0x10;
			break;
		default:
			break;
	}
	return state;
}

void Combine() {
	PORTB = B | B3;
	//PORTB = 0x01;
}

/*some notes/mistakes made:
1. tasksNum is greater than actual # of tasks
2. does not matter whether we have state variable
*/