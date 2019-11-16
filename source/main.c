/*	Author: Van Truong
 *  	Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#include <keypad.h>
#include <bit.h>
#include <timer.h>
#include <stdio.h>
#endif

//--------Task scheduler data structure--------------------------
typedef struct _task {
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
} _task;
//--------End task scheduler data structure----------------------

unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a % b;
		if( c == 0 ) { return b; }
		a = b;
		b = c;
	}
	return 0;
}

enum Keypad_States {determineOutput} keypad_state;

int KeypadTick(int state) {
	unsigned char x;
	x = GetKeypadKey();
	switch (keypad_state) {
		case determineOutput:
			switch(x) {
				case '\0': PORTB = 0x1F; break; // All 5 LEDs on
				case '1': PORTB = 0x01; break; // hex equivalent
				case '2': PORTB = 0x02; break;
				case '3': PORTB = 0x03; break;
				case '4': PORTB = 0x04; break;
				case '5': PORTB = 0x05; break;
				case '6': PORTB = 0x06; break;
				case '7': PORTB = 0x07; break;
				case '8': PORTB = 0x08; break;
				case '9': PORTB = 0x09; break;
				case 'A': PORTB = 0x0A; break;
				case 'B': PORTB = 0x0B; break;
				case 'C': PORTB = 0x0C; break;
				case 'D': PORTB = 0x0D; break;
				case '*': PORTB = 0x0E; break;
				case '0': PORTB = 0x00; break;
				case '#': PORTB = 0x0F; break;
				default: PORTB = 0x1B; break;
			}
		state = determineOutput;
		break;
	}
	return state;
}

int main(void) {
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	static _task task1; 
	_task *tasks[] = {&task1};
	unsigned char numTasks = sizeof(tasks)/sizeof(_task*);
	
	//task 1
	task1.state = determineOutput;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &KeypadTick;

	TimerSet(50);
	TimerOn();

	unsigned short i;
	
    while(1) {
	    // Scheduler code
	for(i = 0; i < numTasks; ++i) {
		if (tasks[i]->elapsedTime == tasks[i]->period) {
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 50;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
	
	return 0;
}












