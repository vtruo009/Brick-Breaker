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
#include <asf.h>


#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <stdio.h>
#include <timer.h>
#include "io.c"
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
//#include "LCD_16x2_C_file.c"
#include <ADC_C.c>

#include "Nokia_5110.c"



/*void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC);
}*/

int main (void)
{	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	/* Insert application code here, after the board has been initialized. */
	//ADC_Init();
	nokia_lcd_init();
	nokia_lcd_clear();

	
	TimerSet(300);
	TimerOn();
	
	while(1) {
		nokia_lcd_render();
		nokia_lcd_set_cursor(21,427);
		nokia_lcd_write_char('a', 3);
// 		unsigned short x = ADC;
// 		unsigned char tmp = (char)x;
// 		x = (char)(x >> 4);
// 		PORTB = tmp;
// 		PORTD = x;
		
		
		/*unsigned short x = ADC_Read(1);
		unsigned char tmp = (char)x;
		LCD_Cursor(1);
		LCD_WriteData(tmp + '0');*/
// 		unsigned short x = ADC;
// 		x = x-512;
// 		unsigned char tmp = (char)x;
// 		if (tmp == 0) {
// 			PORTB = 0x01;
// 		}
// 		else {
// 			PORTB = 0x02;
// 		}
		while(1) {continue;}
		
	}
}

