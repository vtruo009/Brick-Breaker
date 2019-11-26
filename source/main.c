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



/*void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}*/

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

	
	TimerSet(300);
	TimerOn();
	
	while(1) {
		
		/*unsigned short x = ADC_read(1);
		unsigned char tmp = (char)x;
		PORTB = tmp;
		nokia_lcd_set_cursor(10,10);
		nokia_lcd_write_char(tmp, 2);*/

		nokia_lcd_set_cursor(20, 20);
		nokia_lcd_set_pixel(21, 20,1);
		nokia_lcd_set_pixel(22, 20, 1);
		nokia_lcd_set_pixel(23, 20,1);
		nokia_lcd_set_pixel(21, 21,1);
		nokia_lcd_set_pixel(22, 21, 1);
		nokia_lcd_set_pixel(23, 21,1);
		nokia_lcd_set_pixel(21, 22,1);
		nokia_lcd_set_pixel(22, 22, 1);
		nokia_lcd_set_pixel(23, 22,1);
		nokia_lcd_render();

		while(1) {continue;}
		
	}
}

