/*	Author: Van Truong
 *  Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #11  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//#include <asf.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <bit.h>
#include <timer.h>
#include <keypad.h>
#include <scheduler.h>
#include <io.c>

/*unsigned char k = 0;*/

/*enum Cursor_States {indexStart, incr} Cursor_State;

// int MoveCursor(int state) {
// 	switch (state) {
// 		case indexStart:
// 			state = incr;
// 			break;
// 		case incr:
// 			if (k <= 51) {
// 				state = incr;
// 			}
// 			else {
// 				state = indexStart;
// 			}
// 			break;
// 	}
// 	
// 	switch (state) {
// 		case indexStart:
// 			k = 0;
// 			break;
// 		case incr:
// 			++k;
// 			break;
// 		default:
// 			k = 0;
// 			break;
// 	}
// 	return state;	
// }
*/
enum Keypad_States {determineKey} Keypad_state;
static unsigned char letter = '\0';

int KeypadTick(int state) {
	switch(Keypad_state) { //determine which state we're in, but we only have one state because tick function is always getting the keypad input
		case determineKey:
			letter = GetKeypadKey();
			state = determineKey;
			break;
	}
	return state;
}

enum LCD_States {display} LCD_State;
int Display(int state) {
	switch (state) {
		case display:
			LCD_Cursor(0);
			if (letter != '\0') {
				LCD_Cursor(1);
				LCD_WriteData(letter);
			}
			state = display;
			break;
	}
	return state;
}

int main(void)
{
	DDRC = 0xF0; PORTC = 0x0F;
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	//_task struct declared in scheduler.h
	static _task task1, task2; //only one SM
	_task *tasks[] = {&task1, &task2}; //task array with one task
	const unsigned short numTasks = sizeof(tasks)/sizeof(_task*); //number of arrays divided by number of tasks?
	
	task1.state = determineKey;
	task1.period = 500;
	task1.elapsedTime = task1.period;
	task1.TickFct = &KeypadTick;
	
	task2.state = display;
	task2.period = 500;
	task2.elapsedTime = task1.period;
	task2.TickFct = &Display;
	
	TimerSet(500);
	TimerOn();
	
	LCD_init();
	LCD_ClearScreen();
	
	unsigned char i;
    /* Replace with your application code */
    while (1) 
    {
		for (i = 0; i < numTasks; ++i) {
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 500;
		}
		while(!TimerFlag);
		TimerFlag = 0;
    }
	return 0;
}





