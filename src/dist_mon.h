/*
 * dist_Mon.h
 *
 *  Created on: 21 Oct 2017
 *      Author: christo
 */

#ifndef SRC_DIST_MON_H_
#define SRC_DIST_MON_H_

#include <stdint-gcc.h>

#include "alarm.h"
#include "button.h"

class cDistMon {
    typedef enum{
        DISTMON_UNKNOWN,
        DISTMON_SAMPLE,
        DISTMON_CHECK,
        DISTMON_ALARM,
    }cDisMonState_t;

    cDisMonState_t state;
    cAlarm *mAlarm;

    bool mAlarmDismissed;
public:

	cDistMon(cAlarm *alarm);
	virtual ~cDistMon();

	void dismissAlarm();
	void run ();
};

#endif /* SRC_DIST_MON_H_ */
