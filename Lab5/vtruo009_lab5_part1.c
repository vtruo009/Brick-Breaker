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
#include <avr/io.h>

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	//board_init();

	/* Insert application code here, after the board has been initialized. */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	while (1) {
		unsigned char tmpA = PINA; //rmb to add ~ when testing with board
		unsigned char fuelMask = 0x40;
		unsigned char tmpC = 0x00;
		
		//bits are flipped on bboard
		if (tmpA == 0x00) {
			tmpC = 0x00;
		}		
		else if ((tmpA & 0x0F) <= 0x02) {
			tmpC = 0x20 | fuelMask;
		}
		else if ((tmpA & 0x0F) <= 0x04) {
			tmpC = 0x30 | fuelMask;
		}
		else if ((tmpA & 0x0F) <= 0x06) {
			tmpC = 0x38;
		}
		else if ((tmpA & 0x0F) <= 0x09) {
			tmpC = 0x3C;
		}
		else if ((tmpA & 0x0F) <= 0x0C) {
			tmpC = 0x3E;
		}
		else if ((tmpA & 0x0F) <= 0x0F) {
			tmpC = 0x3F;
		}
		
		PORTC = tmpC;
	}
}
