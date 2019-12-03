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
#include "io.c"
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "ADC_H.h"
#include "ADC_C.c"
#include "Nokia_5110.c" //change back to .h for lab computers
#include "scheduler.h"

/*-------------------------------------------------Defines & Global Variables------------------------------------------------------*/
#define left_val 300
#define right_val 700
//#define button ~PINA & 0x08

signed int direction = 0; //direction flags
unsigned char fired = 0; //reset after draw bullet
unsigned char start_game = 0;
unsigned char bulletCount = 0;
unsigned char bulletIndex = 0;
unsigned char reset = 0;
unsigned char enemiesPos[8];
unsigned int bulletPos[15];

static _task task1, task2, task3, task4/*, task5, task6*/; //only one SM
_task *tasks[] = {&task1, &task2, &task3, &task4, /*&task5, &task6*/}; //task array with one task
const unsigned short numTasks = sizeof(tasks)/sizeof(_task*);
/*-------------------------------------------------ENUMS & SM Declarations---------------------------------------------------------*/
enum Menu_States {wait_selection, up, down, start_pressed, instruction_pressed} Menu_state;
void Menu_Tick();

enum Joystick_States {center, left, right};
int Joystick_Tick(int state);

enum Button_States {wait, fire_pressed, reset_pressed};
int Button_Tick(int state);

enum Bullet_States {hold, draw};
int Bullet_Tick(int state);

enum Enemies_States {draw_enemies};
int Enemies_Tick(int state);

void DrawEnemies(); //declaration
/*---------------------------------------------------------------------------------------------------------------------------------*/
void DisplayMenu() {
	nokia_lcd_set_cursor(0,0);
	nokia_lcd_write_char('S',2);
	nokia_lcd_write_char('P',2);
	nokia_lcd_write_char('A',2);
	nokia_lcd_write_char('C',2);
	nokia_lcd_write_char('E',2);
	
	nokia_lcd_set_cursor(8,15);
	nokia_lcd_write_char('S',2);
	nokia_lcd_write_char('H',2);
	nokia_lcd_write_char('O',2);
	nokia_lcd_write_char('O',2);
	nokia_lcd_write_char('T',2);
	nokia_lcd_write_char('E',2);
	nokia_lcd_write_char('R',2);
	
	nokia_lcd_set_cursor(10, 35);
	nokia_lcd_write_string("easy", 1);
	nokia_lcd_set_cursor(40, 35);
	nokia_lcd_write_string("medium",1);

}

void DrawPlatform() {
	signed char i = 0;
	unsigned char j = 0;
	for (i = 0, j = 0; i < 9 && j < 2; ++i) {
		nokia_lcd_set_pixel(get_rect_start_x() /*+ d*/ + i, get_rect_y() + j, 1);
		if (i == 8) {
			i = -1;
			++j;
		}
	}
}

void DrawBullet() {
	nokia_lcd_set_pixel(get_rect_start_x() + 4, 44, 1);
	nokia_lcd_set_pixel(get_rect_start_x() + 4, 45, 1);
}

void DrawEnemies() {
	signed char i = 0;
	signed char j = 0;
// 	for (unsigned char a = 0; a < 5; ++a) {
// 		nokia_lcd_set_cursor(10*a + 4, 2);
		for (j = 0; i < 3 && j < 4; ++j) { //2 & 4
			nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
			if (j == 3) {
				j = -1;
				++i;
			}
		}
		for (i = -1, j = 1; i < 4 && j < 3; ++j) { //3 & 3
			nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
			if (j == 2) {
				j = 0;
				i += 4; //3
			}
		}
	//}
}

void InitializeGame() {
	nokia_lcd_set_cursor(0,0);
	nokia_lcd_set_rect_start(37,46);
	nokia_lcd_set_block_start(40,43);
	direction = 0; //direction flags
	fired = 0; //reset after draw bullet
	start_game = 0;
	bulletCount = 0;
	bulletIndex = 0;
	enemiesPos[8] = -1;
	bulletPos[15] = -1;
	
	task1.state = center;
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Joystick_Tick;
	
	task2.state = wait;
	task2.period = 50;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Button_Tick;
	
 	task3.state = hold;
	task3.period = 75;
	task3.elapsedTime = task3.period;
	task3.TickFct = &Bullet_Tick;
 	
	task4.state = draw_enemies;
	task4.period = 100;
	task4.elapsedTime = task4.period;
	task4.TickFct = &Enemies_Tick;
}

void Menu_Tick() {
	unsigned char button = ~PINA & 0x08;
	unsigned char joystick = ADC;
	switch (Menu_state) {
		case wait_selection:
			if (joystick > left_val && joystick < right_val){
				Menu_state = wait_selection;
			}
			else if (joystick < left_val) {
				Menu_state = left;
				PORTB = 0x01;
			}
			else if (joystick > right_val) {
				Menu_state = right;
			}
			break;
		case start_pressed:
			break;
		case instruction_pressed:
			break;
	}
	
	switch (Menu_state) {
		case wait_selection:
			DisplayMenu();
			nokia_lcd_set_rect_start(15, 46);
			DrawPlatform();
			break;
		case left:
			PORTB = 0x02;
			DisplayMenu();
			nokia_lcd_set_rect_start(15, 46);
			break;
		case right:
			PORTB = 0x03;
			DisplayMenu();
			nokia_lcd_set_rect_start(45, 46);
			DrawPlatform();
		case start_pressed:
			start_game = 1;
			break;
		case instruction_pressed:
			break;
	}
}

int Joystick_Tick(int state) {
	unsigned short x = ADC;
	if (x > left_val && x < right_val) {
		state = center;
	}
	else if (x < left_val) {
		state = left;
	}
	else if (x > right_val) {
		state = right;
	}
	
	switch (state) {
		case center:
			direction = 0;
			DrawPlatform();
			break;
		case left:
			--direction;
			if (get_rect_start_x() + direction >= 0) {
				nokia_lcd_set_rect_start(get_rect_start_x() + direction, 46);
				nokia_lcd_clear();
				DrawPlatform();
			}
			break;
		case right:
			++direction;
			if (get_rect_start_x() + direction <= 75) {
				nokia_lcd_set_rect_start(get_rect_start_x() + direction, 46);
				nokia_lcd_clear();
				DrawPlatform();
			}
			break;
	}
// 	unsigned char a;
//  	for (a = 0; a < 8; ++a) {
// 		nokia_lcd_set_cursor(10*a + 4, 2);
// 		enemiesPos[a] = 10*a + 3;
// 		DrawEnemies();
// 	 }
	DrawBullet();
	return state;
}

int Button_Tick(int state) {
	unsigned char fire_button = ~PINA & 0x08;
	unsigned char reset_button = ~PINC & 0x01;
	switch (state) {
		case wait:
			if (fire_button) {
				state = fire_pressed;
			}
			else if (reset_button) {
				state = reset_pressed;
			}
			break;
		case fire_pressed:
			if (!fire_button) {
				state = wait;
			}
			break;
		case reset_pressed:
			if (!reset_button) {
				state = wait;
			}
			break;
		default:
			state = wait;
	}
	
	switch (state) {
		case wait:
			break;
		case fire_pressed:
			fired = 1;
			break;
		case reset_pressed:
			nokia_lcd_clear();
			InitializeGame();
			break;
	}
	return state;
}

int Bullet_Tick(int state) {
	switch (state) {
		case hold:
			if (fired) {
				state = draw;
			}
			break;
		case draw:
			if (!fired) {
				state = hold;
			}
			break;
	}
	switch (state) {
		case hold:
			break;
		case draw:
			if (!reset && fired) {
				nokia_lcd_set_pixel(get_rect_start_x() + 4, 44 - bulletCount, 1);
				nokia_lcd_set_pixel(get_rect_start_x() + 4, 45 - bulletCount, 1);
				bulletPos[bulletIndex] = get_rect_start_x + 4;
				++bulletIndex;
				if (bulletCount > 0) {
					nokia_lcd_set_pixel(get_rect_start_x() + 4, 46 - bulletCount, 0);
				}
				++bulletCount;
				if (bulletCount > 47) {
					bulletCount = 0;
					fired = 0;
					state = hold;
				}
			}
	}
	return state;
}

int Enemies_Tick(int state) {
	for (unsigned char a = 0; a < 8; ++a) {
		nokia_lcd_set_cursor(10*a + 5, 10);
		enemiesPos[a] = get_x() - 1;
		DrawEnemies();
	}
}

void Score_Tick() {
	nokia_lcd_set_cursor(0,0);
	nokia_lcd_write_string("SCORE: ", 1);
}

int main (void)
{	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0x00; PORTC = 0xFF;
	
	/* Insert application code here, after the board has been initialized. */
	static _task task1, task2, task3, task4; //only one SM
	_task *tasks[] = {&task1, &task2, &task3, &task4}; //task array with one task
	const unsigned short numTasks = sizeof(tasks)/sizeof(_task*);
	
	task1.state = center;
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &Joystick_Tick;
	
	task2.state = wait;
	task2.period = 50;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Button_Tick;
	
	task3.state = hold;
	task3.period = 75;
	task3.elapsedTime = task3.period;
	task3.TickFct = &Bullet_Tick;
	
	task4.state = draw_enemies;
	task4.period = 100;
	task4.elapsedTime = task4.period;
	task4.TickFct = &Enemies_Tick;
	
	
	TimerSet(25);
	TimerOn();
	
	ADC_init();
	nokia_lcd_init();

	unsigned char i;
	while(1) {
// 		Menu_Tick();
// 		if (start_game) {
			for (i = 0; i < numTasks; ++i) {
				if (tasks[i]->elapsedTime == tasks[i]->period) {
					tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
					tasks[i]->elapsedTime = 0;
				}
				tasks[i]->elapsedTime += 25;
			}
//		}
// 		int i, j;
// 		for (i = 0; i < 30; ++i){
// 			for (j = 0; j < 3000; ++j);
// 		}
		nokia_lcd_render();
		while(!TimerFlag);
		TimerFlag = 0;
		//while(1) {continue;}
	}
}
