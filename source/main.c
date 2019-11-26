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
#include "ADC_H.h"
#include "Nokia_5110.h"

void DrawBall() {
	nokia_lcd_set_cursor(43, 40);
	unsigned char i = 0;
	unsigned char j = 0;
	for (i = 0; i < 3 && j < 3; ++i) {
		nokia_lcd_set_pixel(get_x() + i, get_y() + j, 1);
		if (i == 2) {
			i = 0;
			++j;
		}
	}

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
	nokia_lcd_clear();
	DrawBall();
	nokia_lcd_render();
	
	while(1) {
		
		/*unsigned short x = ADC_read(1);
		unsigned char tmp = (char)x;
		PORTB = tmp;
		nokia_lcd_set_cursor(10,10);
		nokia_lcd_write_char(tmp, 2);*/

		

		//while(1) {continue;}
		
	}
}
