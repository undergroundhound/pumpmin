/*
 * dist_mon.cpp
 *
 *  Created on: 21 Oct 2017
 *      Author: christo
 */

#include <stdio.h>
#include <util/delay.h>

#include "dist_mon.h"
#include "distance.h"

#define CAR_TRIGGER_DISTANCE 10
#define CAR_TIME		     5

cDistMon::cDistMon(cAlarm *alarm)
{
    mAlarm = alarm;
    mAlarmDismissed = false;
    // TODO Auto-generated constructor stub
    state = DISTMON_UNKNOWN;
}

cDistMon::~cDistMon()
{
    // TODO Auto-generated destructor stub
}

void cDistMon::dismissAlarm()
{
    mAlarmDismissed = true;
    mAlarm->setDbg(2);
    mAlarm->setLed(0);
}

void cDistMon::run()
{
    static uint8_t alarmCount = 0;
    static uint8_t sampleCount;
    static uint16_t samples;

    static uint8_t lastSample;

    switch (state)
    {
        case DISTMON_SAMPLE:
        {
            if (sampleCount < 16)
            {
                uint8_t sample = Distance.getSample();
			printf("s: %d\n", sample);
                sampleCount++;
                samples += sample;

                Distance.sample();
                return;
            }

            lastSample = samples >> 4;

            sampleCount = 0;
            samples = 0;

            Distance.sample();
            state = DISTMON_CHECK;
        }
            break;
        case DISTMON_CHECK:
        {
            printf("d: %d x 10cm\n", lastSample);
            //kar is gone
            if (lastSample > CAR_TRIGGER_DISTANCE)
            {
                alarmCount = 0;
                mAlarm->setLed(0);
                mAlarm->setDbg(0);
                //disable alarm
                mAlarmDismissed = false;
            }
            else
            {
                if (mAlarmDismissed)
                {
//                    mAlarm->setDbg(2);
//                    mAlarm->setLed(0);

                    state = DISTMON_SAMPLE;
                    return;
                }

                if (alarmCount == CAR_TIME)
                {
                    printf("alarm\n");
                    state = DISTMON_ALARM;
                    //enable alarm
                    mAlarm->setLed(1);
                    //only trigger once
                    alarmCount++;
                }

                if (alarmCount < CAR_TIME)
                {
                    alarmCount++;
                    mAlarm->setDbg(1);
                    printf("ac:%d\n", alarmCount);
                }
            }

            state = DISTMON_SAMPLE;
        }
            break;
        case DISTMON_ALARM:
        {

            state = DISTMON_SAMPLE;
        }
            break;
        default:
            Distance.sample();
            _delay_ms(100);
            state = DISTMON_SAMPLE;
            break;
    }
}
