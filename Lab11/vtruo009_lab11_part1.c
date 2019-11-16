/*	Author: Van Truong
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <asf.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <bit.h>
#include <timer.h>
#include <keypad.h>

/*--------------------------------------SCHEDULER----------------------------------------------------*/
typedef struct _task {
	int state;
	unsigned long period;
	unsigned long elapsedTime;
	int (*TickFnct)(int);
} _task;

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

enum Keypad_States {determineKey} Keypad_state;
	
int KeypadTick(int state) {
	unsigned char x;
	x = GetKeypadKey();
	switch(Keypad_state) { //determine which state we're in, but we only have one state because tick function is always getting the keypad input
		case determineKey:
			switch(x) { //determine which key is pressed
				case '\0': PORTB = 0x1F; break; // All 5 LEDs on when nothing is pressed
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
			}
			state = determineKey;
			break;
	}
	return state;
}
int main(void)
{
	DDRC = 0xF0; PORTC = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	//_task struct declared in scheduler.h
	static _task task1; //only one SM
	_task *tasks[] = {&task1}; //task array with one task
	const unsigned short numTasks = sizeof(tasks)/sizeof(_task*); //number of arrays divided by number of tasks?
	
	task1.state = determineKey;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFnct = &KeypadTick;
	
	TimerSet(50);
	TimerOn();
	unsigned short i;
    /* Replace with your application code */
    while (1) 
    {
		for (i = 0; i < numTasks; ++i) {
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFnct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 50;
		}
		while(!TimerFlag);
		TimerFlag = 0;
    }
	return 0;
}


