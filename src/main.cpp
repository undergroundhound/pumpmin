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
#include "dist_mon.h"
#include "alarm.h"

cAlarm Alarm = cAlarm();
cButton Button = cButton();

cDistMon DistMon = cDistMon(&Alarm);


void button(bool state)
{
    printf("btn! %d\n", state);

    if (state)
    {
        DistMon.dismissAlarm();
        printf("AlarmDismissed!\n");
    }
}

volatile uint16_t halfMicro = 0;

int main ( void )
{
	sei();
	printf("main()\n");

	Button.setCB(&button);

	while(1)
	{
	    Alarm.run();
		Button.run();
		Terminal.run();
		DistMon.run();
		_delay_ms(50);
	}
	return 0;
}


