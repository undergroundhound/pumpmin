/*
 * main.c
 *
 *  Created on: 17 Oct 2017
 *      Author: christo
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "terminal.h"
#include "button.h"
#include "distance.h"

cButton Button = cButton();
cDistance Distance = cDistance();
void button(bool state, uint8_t counts)
{
	printf("btn!\n");
}

int main ( void )
{

	sei();
	printf("main()\n");

	Button.setCB(&button);

	uint8_t div = 0;
	while(1)
	{
		if (++div > 50)
		{
			div = 0;
			printf("dist: %d\n", Distance.sample());
		}
		Button.run();
		Terminal.run();
		_delay_ms(100);
	}
	return 0;
}
