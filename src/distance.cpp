/*
 * distance.cpp
 *
 *  Created on: 17 Oct 2017
 *      Author: christo
 */

#include "distance.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

cDistance::cDistance()
{
	//trigger as output and disable
	TRIG_DDR |= _BV(TRIG_PIN_NUM);
	TRIG_PORT &= ~(_BV(TRIG_PIN_NUM));


	//echo as input
	ECHO_DDR &= ~(_BV(ECHO_PIN_NUM));

	printf("distance init()\n");

}

cDistance::~cDistance() {
	// TODO Auto-generated destructor stub
}


uint16_t cDistance::sample()
{
	printf("s\n");
	uint16_t count = 0;
	//pulse echo
	TRIG_PORT |= _BV(TRIG_PIN_NUM);
	_delay_us(10);
	TRIG_PORT &= ~(_BV(TRIG_PIN_NUM));

	while((ECHO_PIN & _BV(ECHO_PIN_NUM)) == 0)
	{
		_delay_us(1);
		count++;
	}


	return count++;
}
