/*
 * alarm.cpp
 *
 *  Created on: 21 Oct 2017
 *      Author: christo
 */

#include "alarm.h"

#define LED_PORT	    PORTB
#define LED_DDR		    DDRB
#define LED_PIN		    PINB
#define LED_PIN_NR	    PB4

#define LED_DBG_PORT	PORTB
#define LED_DBG_DDR	    DDRB
#define LED_DBG_PIN	    PINB
#define LED_DBG_PIN_NR	PB5

#define LED_DUTY_C      1

cAlarm::cAlarm()
{
    //set led ddr pin
    LED_DDR |= _BV(LED_PIN_NR);
    LED_DBG_DDR |= _BV(LED_DBG_PIN_NR);

    //disable led
    LED_PORT |= _BV(LED_PIN_NR);
    LED_DBG_PORT &= ~_BV(LED_DBG_PIN_NR);

    //    LED_PORT &= ~_BV(LED_PIN_NR);
    //    LED_DBG_PORT |= _BV(LED_DBG_PIN_NR);

    mDbgActive = false;
    mLedActive = false;
}

cAlarm::~cAlarm()
{
    // TODO Auto-generated destructor stub
}

void cAlarm::setDbg(uint8_t state)
{
    if (state == 1)
    {
        mDbgActive = true;
        return;
    }
    else if (state == 2)
    {
        LED_DBG_PORT |= _BV(LED_DBG_PIN_NR);
        mDbgActive = false;
        return;
    }

    LED_DBG_PORT &= ~_BV(LED_DBG_PIN_NR);
    mDbgActive = false;
}

void cAlarm::setLed(uint8_t state)
{
    if (state == 1)
    {
        mLedActive = true;
        return;
    }

    LED_PORT |= _BV(LED_PIN_NR);
    mLedActive = false;
}

void cAlarm::run()
{
    static uint8_t led_dutyC = 0;
    if (led_dutyC++ > LED_DUTY_C)
    {
        led_dutyC = 0;

        if (mLedActive)
            LED_PIN |= _BV(LED_PIN_NR);

        if (mDbgActive)
            LED_DBG_PIN |= _BV(LED_DBG_PIN_NR);
    }
}
