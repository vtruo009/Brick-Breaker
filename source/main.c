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
//----------End ENUMS and SM declarations----------------------------

//FIX LAB NUMBER ON PART 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main(void) {
	DDRC = 0xF0; PORTC = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	//DDRD = 0xFF; PORTD = 0x00;
	unsigned char x;
	while (1) {
		x = GetKeypadKey();
		
	}

	return 1;
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




