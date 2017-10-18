/*
 * main.c
 *
 *  Created on: 17 Oct 2017
 *      Author: christo
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/>
#include <stdio.h>

#include "terminal.h"
#include "button.h"
#include "distance.h"

cButton Button = cButton();

void button(bool state, uint8_t counts)
{
	printf("btn!\n");
}

volatile uint16_t halfMicro = 0;

int main ( void )
{
	sei();
	printf("main()\n");

	Button.setCB(&button);

	uint8_t div = 0;
	while(1)
	{
		if (++div > 5)
		{
			div = 0;
			printf("distance: %dcm\n", Distance.getSample());
		}
		Button.run();
		Terminal.run();
		Distance.sample();
		_delay_ms(100);
	}
	return 0;
}


