/*
 * alarm.h
 *
 *  Created on: 21 Oct 2017
 *      Author: christo
 */

#ifndef SRC_ALARM_H_
#define SRC_ALARM_H_

#include <avr/io.h>

class cAlarm {
    uint8_t mDbgActive;
    uint8_t mLedActive;
public:
	cAlarm();
	virtual ~cAlarm();

	void run();
	void setDbg(uint8_t state);
	void setLed(uint8_t state);
};

#endif /* SRC_ALARM_H_ */
