/*
 * distance.cpp
 *
 *  Created on: 17 Oct 2017
 *      Author: christo
 */

#include "distance.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

cDistance::cDistance()
{
	//trigger as output and disable
	TRIG_DDR |= _BV(TRIG_PIN_NUM);
	TRIG_PORT &= ~(_BV(TRIG_PIN_NUM));

	//echo as input
	ECHO_DDR &= ~(_BV(ECHO_PIN_NUM));

	//interrupt
	PCMSK1 |= (1 << PCINT10);
	PCICR |= (1 << PCIE1);

	printf("distance init()\n");
}

cDistance::~cDistance() {
	// TODO Auto-generated destructor stub
}


void cDistance::sample()
{
	TRIG_PORT |= _BV(TRIG_PIN_NUM);
	_delay_us(10);
	TRIG_PORT &= ~(_BV(TRIG_PIN_NUM));

	return;
}

void cDistance::setSample(uint16_t sample)
{
	uint8_t tmp = (uint8_t)(sample/145);

	if (tmp > 255)
		return;

	lastSample = tmp;
}

uint8_t cDistance::getSample()
{
	return lastSample;
}

ISR(PCINT1_vect)
{
	if((ECHO_PIN & _BV(ECHO_PIN_NUM)) == 0)
	{
		Distance.setSample(TCNT1);
		//disable the  timer
		TCCR1B &= ~(0x03);

	}else
	{
		//enable the  timer
		TCNT1 = 0;
		TCCR1B |= 0x03 ;
	}
}

cDistance Distance = cDistance();
