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
//#include <asf.h>


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <timer.h>
#include "io.h"
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "ADC_H.h"
#include "ADC_C.c"
#include "Nokia_5110.c" //change back to .h for lab computers
#include "scheduler.h"

/*-------------------------------------------------Defines & Global Variables------------------------------------------------------*/
#define left_val 300
#define right_val 700
#define button ~PINA & 0x08

signed int direction = 0; //direction flags
unsigned char shot = 0;
unsigned char enemiesPos[8];
/*-------------------------------------------------ENUMS & SM Declarations---------------------------------------------------------*/
enum Joystick_States {center, left, right} Joystick_State;
void Joystick_Tick();

enum Shoot_States {wait, shoot} Shoot_state;
void Shoot_Tick();
/*---------------------------------------------------------------------------------------------------------------------------------*/

void DrawPlatform(/*signed int d*/) {
	signed char i = 0;
	unsigned char j = 0;
// 	for (i = 0; i < 3 && j < 3; ++i) {
// 		nokia_lcd_set_pixel(get_block_start_x() + d + i, get_block_y() + j, 1);
// 		if (i == 2) {
// 			i = -1;
// 			++j;
// 		}
// 	}
	for (i = 0, j = 0; i < 9 && j < 2; ++i) {
		nokia_lcd_set_pixel(get_rect_start_x() /*+ d*/ + i, get_rect_y() + j, 1);
		if (i == 8) {
			i = -1;
			++j;
		}
	}
}

void ClearBullet() {
	unsigned char i, j;
	for (i = 0; (i < 3) && (j < 3); ++i) {
		nokia_lcd_set_pixel(get_block_start_x(), get_block_y(), 0);
		if (i == 2) {
			i = -1;
			++j;
		}
	}
}

void DrawBullet(unsigned char count) {
	signed char i , j;
// 	if (!fire) {
// 		for (i = 0; i < 3 && j < 3; ++i) {
// 			nokia_lcd_set_pixel(get_block_start_x() + i, get_block_y() + j, 1);
// 			if (i == 2) {
// 				i = -1;
// 				++j;
// 			}
// 		}
// 	}
// 	else {
		//nokia_lcd_set_cursor(10,10);
// 	for (unsigned char k = 0; k < 38; ++k) {
// 		nokia_lcd_set_block_start(get_block_start_x(), get_block_y() - k);
// 		for (i = 0, j = 0; (i < 3) && (j < 3); ++i) {
// 			PORTB = 0x05;
// 			nokia_lcd_set_pixel(get_block_start_x() + i, get_block_y() + j, 1);
// 			if (i == 2) {
// 				i = -1;
// 				++j;
// 			}
// 		}
// 	}
	
// 	for (unsigned char k = 0; k < 38; ++k) {
// 		nokia_lcd_clear();
// 		nokia_lcd_set_cursor(get_block_start_x(), get_block_y - 1);
// 		for (i = 0, j = 0; (i < 3) && (j < 3); ++i) {
// 			PORTB = 0x05;
// 			nokia_lcd_set_pixel(get_block_start_x() + i, get_block_y() + j, 1);
// 			if (i == 2) {
// 				i = -1;
// 				++j;
// 			}
// 		}
// 	}
	//}
// 	nokia_lcd_set_pixel(41, 44, 1);
// 	nokia_lcd_set_pixel(41, 45, 1);
	nokia_lcd_set_pixel(get_rect_start_x() + 4, 44 - count, 1);
	nokia_lcd_set_pixel(get_rect_start_x() + 4, 45 - count, 1);
	if (count > 0) {
		nokia_lcd_set_pixel(get_rect_start_x() + 4, 46 - count, 0);
	}
	nokia_lcd_render();
}

void DrawEnemies() {
	//nokia_lcd_set_cursor(1,2);
	signed char i = 0;
	signed char j = 0;
// 	for (unsigned char a = 0; a < 5; ++a) {
// 		nokia_lcd_set_cursor(10*a + 4, 2);
		for (j = 0; i < 2 && j < 4; ++ j) {
			nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
			if (j == 3) {
				j = -1;
				++i;
			}
		}
		for (i = -1, j = 1; i < 3 && j < 3; ++j) {
			nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
			if (j == 2) {
				j = 0;
				i += 3;
			}
		}
	//}
}

void Joystick_Tick() {
	unsigned short x = ADC;
	switch (Joystick_State) {
		case center:
			if (x > left_val && x < right_val) {
				Joystick_State = center;
			}
			else if (x < left_val) {
				Joystick_State = left;
			}
			else if (x > right_val) {
				Joystick_State = right;
			}
			break;
		case left:
			if (x > left_val && x < right_val) {
				Joystick_State = center;
			}
			else if (x < left_val) {
				Joystick_State = left;
			}
			else if (x > right_val) {
				Joystick_State = right;
			}
			break;
		case right:
			if (x > left_val && x < right_val) {
				Joystick_State = center;
			}
			else if (x < left_val) {
				Joystick_State = left;
			}
			else if (x > right_val) {
				Joystick_State = right;
			}
			break;
	}
	
	switch (Joystick_State) {
		case center:
			direction = 0;
			DrawPlatform();
			break;
		case left:
			--direction;
			if (get_rect_start_x() + direction >= 0) {
				nokia_lcd_set_rect_start(get_rect_start_x() + direction, 46);
				nokia_lcd_clear();
				DrawPlatform(/*direction*/);
			}
			break;
		case right:
			++direction;
			if (get_rect_start_x() + direction <= 75) {
				nokia_lcd_set_rect_start(get_rect_start_x() + direction, 46);
				nokia_lcd_clear();
				DrawPlatform(/*direction*/);
			}
			break;
	}
 	for (unsigned char a = 0; a < 8; ++a) {
		nokia_lcd_set_cursor(10*a + 4, 2);
		enemiesPos[a] = 10*a + 3;
		DrawEnemies();
	 }
	nokia_lcd_render();
}

void Shoot_Tick() {
	unsigned char shot;
	switch (Shoot_state) {
		case wait:
			if (button) {
				Shoot_state = shoot;
			}
			else {
				Shoot_state = wait;
			}
			break;
		case shoot:
			if (button) {
				Shoot_state = shoot;
			}
			else {
				Shoot_state = wait;
			}
			break;
		default:
			Shoot_state = wait;
	}
	
	switch (Shoot_state) {
		case wait:
			//shot = 0;
			DrawBullet(shot);
			break;
		case shoot:
			//shot = 1;
			//DrawBullet(++shot);
			for(unsigned char i = 0; i < 45; ++i) {
				nokia_lcd_set_pixel(get_rect_start_x() + 4, 44 - i, 1);
				nokia_lcd_set_pixel(get_rect_start_x() + 4, 45 - i, 1);
				if (i > 0) { 
					nokia_lcd_set_pixel(get_rect_start_x() + 4, 46 - i, 0);
				}
			}
// 			nokia_lcd_set_pixel(41, 44, 0);
// 			nokia_lcd_set_pixel(41, 45, 0);
		default:
			break;
	}
	nokia_lcd_render();
}

int main (void)
{	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	/* Insert application code here, after the board has been initialized. */
	static _task task1, task2; //only one SM
	_task *tasks[] = {&task1, &task2}; //task array with one task
	const unsigned short numTasks = sizeof(tasks)/sizeof(_task*);
	
	task1.state = center;
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Joystick_Tick;
	
	task2.state = wait;
	task2.period = 300;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Shoot_Tick;
	
// 	for (unsigned char a = 0; a < 5; ++a) {
// 		nokia_lcd_set_cursor(10*a + 4, 2);
//  	DrawEnemies();
// 	}
	
	TimerSet(100);
	TimerOn();
	
	ADC_init();
	nokia_lcd_init();
	
	unsigned char i;
	while(1) {
		for (i = 0; i < numTasks; ++i) {
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 100;
		}
// 		int i, j;
// 		for (i = 0; i < 30; ++i){
// 			for (j = 0; j < 3000; ++j);
// 		}
		while(!TimerFlag);
		TimerFlag = 0;
		//while(1) {continue;}
	}
}
