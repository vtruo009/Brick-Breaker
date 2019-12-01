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
#include <timer.h>
#include "io.h"
#include <avr/interrupt.h>
#include <util/delay.h>
//#include "ADC_H.h"
#include "ADC_C.c"
#include "Nokia_5110.c" //change back to .h for lab computers

/*-------------------------------------------------Defines & Global Variables------------------------------------------------------*/
#define left_val 300
#define right_val 700
#define button ~PINA & 0x08;

signed int direction = 0; //direction flags
/*-------------------------------------------------ENUMS & SM Declarations---------------------------------------------------------*/
enum Joystick_States {center, left, right} Joystick_State;
void Joystick_Tick();
/*---------------------------------------------------------------------------------------------------------------------------------*/

void DrawPlatform(signed int d) {
// 	if ((get_rect_start_x() + d) > 75) {
// 		nokia_lcd_set_rect_start(75, 46);
// 	}
// 	else if ((get_rect_start_x() + d) < 0) {
// 		nokia_lcd_set_rect_start(0, 46);
// 	}

	signed char i = 0;
	unsigned char j = 0;
// 	for (i = 0; i < 3 && j < 3; ++i) {
// 		nokia_lcd_set_pixel(get_block_start_x() + d + i, get_block_y() + j, 1);
// 		if (i == 2) {
// 			i = -1;
// 			++j;
// 		}
// 	}
	//nokia_lcd_set_cursor(37 + d, 46);
	//nokia_lcd_set_cursor(get_rect_start_x(), get_rect_start_y());
	for (i = 0, j = 0; i < 9 && j < 2; ++i) {
		nokia_lcd_set_pixel(get_rect_start_x() + d + i, get_rect_y() + j, 1);
		if (i == 8) {
			i = -1;
			++j;
		}
	}
	
	nokia_lcd_set_rect_start(get_rect_start_x() + d, 46);
	//nokia_lcd_set_block_start(get_block_start_x() + d, 43);
}

void DeleteLeftColumns(signed int d) {
	//nokia_lcd_set_cursor(40, 43);
	signed int i = 0;
// 	for (signed int j = 0;  (i < d) && (j < 3); ++j) {
// 		//nokia_lcd_set_pixel(get_x() + i, get_y() + j, 0);
// 		nokia_lcd_set_pixel(get_block_start_x() + i, get_block_y() + j, 0);
// 		if (j == 2) {
// 			j = -1;
// 			++i;
// 		}
// 	}
	//nokia_lcd_set_cursor(37,46);
	i = 0;
	for (signed int j = 0; (i < d) && (j < 2); ++j) {
		//nokia_lcd_set_pixel(get_x() + i, get_y() + j, 0);
		nokia_lcd_set_pixel(get_rect_start_x() + i, get_rect_y() + j, 0);
		if (j == 1) {
			j = -1;
			++i;
		}
	}
	//set new cursors
// 	nokia_lcd_set_block_start(40+d,43);
// 	nokia_lcd_set_block_end(42+d, 43);
// 	nokia_lcd_set_rect_start(37+d,46);
// 	nokia_lcd_set_rect_end(45+d, 46);
}

void DeleteRightColumns(signed int d)  {
	//nokia_lcd_set_cursor(42,43);																																																						
	signed int i = 0;
// 	for (signed int j = 0; (i > d) && (j < 3); ++j) {
// 		nokia_lcd_set_pixel(get_block_end_x() + i, get_block_y() + j, 0);
// 		if (j == 2) {
// 			j = -1;
// 			--i;
// 		}
// 	}
	//nokia_lcd_set_cursor(45,46);
	i = 0;
	for (signed int j = 0; (i > d) && (j < 2); ++j) {
		nokia_lcd_set_pixel(get_rect_end_x() + i, get_rect_y() + j, 0);
		if (j == 1) {
			j = -1;
			--i;
		}
	}
	//set new cursors
// 	nokia_lcd_set_block_start(40+d,43);
// 	nokia_lcd_set_block_end(42+d, 43);
// 	nokia_lcd_set_rect_start(37+d,46);
// 	nokia_lcd_set_rect_end(45+d, 46);
// 	nokia_lcd_set_block_start(get_block_start_x() + d,43);
// 	nokia_lcd_set_block_end(get_block_end_x() + d, 43);
// 	nokia_lcd_set_rect_start(get_rect_start_x() + d,46);
// 	nokia_lcd_set_rect_end(get_rect_end_x()+d, 46);
}

void DrawEnemies() {
	nokia_lcd_set_cursor(1,2);
	signed char i = 0;
	signed char j = 0;
	for (i = 0;i < 4 && j < 2; ++i) {
		nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
		if (i == 3) {
			i = -1;
			++j;
		}
	}
	for (i = 1, j = -1; i < 3 && j < 3; ++i) {
		nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
		if (i == 2) {
			i = 0;
			j += 3;
		}
	}
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
			break;
		case left:
			//direction -= 1;
			--direction;
			if ((direction + get_rect_start_x()) >= 0) {
				
				nokia_lcd_clear();
				DrawPlatform(direction);
			}
			break;
		case right:
			//direction += 1;
			++direction;
			if (get_rect_start_x() < 75) {
				nokia_lcd_clear();
				DrawPlatform(direction);
			}
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
	
	ADC_init();
	nokia_lcd_init();
	DrawPlatform(direction);
	DrawEnemies();
	
// 	TimerSet(300);
// 	TimerOn();
	
	while(1) {
		
		Joystick_Tick();
		
		int i, j;
		for (i = 0; i < 60; ++i){
			for (j = 0; j < 3000; ++j);
		}
// 		while(!TimerFlag);
// 		TimerFlag = 0;
		//while(1) {continue;}
		
	}
}
