/*	Author: Van Truong
 *  	Partner(s) Name: An Pho
 *	Lab Section: 023
 *	Assignment: Lab #11  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#include "keypad.h"
#endif

//--------Task scheduler data structure--------------------------
typedef struct _task {
	unsigned char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
} task;
//--------End task scheduler data structure----------------------

//--------Shared variables-------------------------------------------
unsigned char led0_output = 0x00;
unsigned char led1_output = 0x00;
unsigned char pause = 0;
//--------End shared variables----------------------------------------

//-----------ENUMS and SM declarations-------------------------------
enum pauseButtonSM_States { pauseButton_wait, pauseBUtton_press, pauseButton_release };
int pauseButtonSMTick(int state);

enum toggleLED0_States { toggleLED0_wait, toggleLED0_blink };
int toggleLED0SMTick(int state);

enum toggleLED1_States { toggleLED1_wait, toggleLED1_blink };
int toggleLED1SMTick(int state);

enum display_States { display_display };
int displaySMTick(int state);
//----------End ENUMS and SM declarations----------------------------

//FIX LAB NUMBER ON PART 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main(void) {
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	unsigned long systemPeriod = 500;
	static task task1; 
	static task task2;
	task *tasks[] = {&task1, &task2};
	unsigned char numTasks = sizeof(tasks)/sizeof(task*);
	
	//task 1
	task1.state = IndexInit;
	task1.period = systemPeriod;
	task1.elapsedTime = task1.period;
	task1.TickFct = &IndexTick;
	
	//task 2
	task2.state = OUTPUT;
	task2.period = systemPeriod;
	task2.elapsedTime = task2.period;
	task2.TickFct = &LCDTick;
	
	TimerSet(systemPeriod);
	TimerOn();
	LCD_init();
	LCD_ClearScreen();
	unsigned char i;
    while(1) {
	    // Scheduler code
	    for ( i = 0; i < numTasks; i++ ) {
		    // Task is ready to tick
		    if ( tasks[i]->elapsedTime >= tasks[i]->period ) {
			    // Setting next state for task
			    tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			    // Reset the elapsed time for next tick.
			    tasks[i]->elapsedTime = 0;
		    }
		    tasks[i]->elapsedTime += systemPeriod;
	    }
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
	
	return 0;
}

int pauseButtonSMTick(int state) {
	unsigned char press = ~PINA & 0x01;

	switch (state) {
		case pauseButton_wait:
			state = press == 0x01? pauseButton_press: pauseButton_wait;
			break;
		case pauseButton_press:
			state = pauseButton_release;
			break;
		case pauseButton_release:
			state = press == 0x00? pauseButton_wait: pauseButton_press;
			break;
		default:
			state = pauseButton_wait;
			break;
	}

	switch (state) {
		case pauseButton_wait:
			break;
		case pauseButton_press:
			pause = (pause == 0) ? 1 : 0;
			break;
		case pauseButton_release:
			break;
	}
	return state;
}

int toggleLED0SMTick(int state) {
	switch(state) {
		case toggleLED0_wait:
			state = !pause? toggleLED0_blink: toggleLED0_wait;
			break;
		case toggleLED0_blink: state = pause? toggleLED0_wait: toggleLED0_blink;
			break;
		default:
			state = toggleLED0_wait;
			break;

	switch(state) {
		case toggleLED0_wait:
			break;
		case toggleLED0_blink:
			led0_output = (led0_output == 0x00) ? 0x01 : 0x00;
			break;
	}

	return state;
}

int toggleLED1SMTick(int state) {
	switch (state) {
		case toggleLED1_wait:
			state = !pause? toggledLED1_blink: toggleLED1_wait;
			break;
		case toggledLED1_blink:
			state = pause? toggleLED1_wait: toggledLED1_blink;
			break;
		default:
			state = toggleLED1_wait;
			break;
	}
	
	switch (state) {
		case toggleLED1_wait:
			break;
		case toggleLED1_blink:
			led1_output = (led1_output == 0x00_ ? 0x01 : 0x00;
			break;
	}
	
	return state;
}

int displaySMTick(int state) {
	usnigned char output;

	switch (state) {
		case display_display:
			state = display_display;
			break;
		default:
			state = display_display;
			break;
	}

	switch (state) {
		case display_display:
			output = led0_output | led1_output << 1;
			break;
	}

	PORTB = output;
	return state;
}















