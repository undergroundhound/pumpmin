/*
 * distance.h
 *
 *  Created on: 17 Oct 2017
 *      Author: christo
 */

#ifndef SRC_DISTANCE_H_
#define SRC_DISTANCE_H_

#include <stdint.h>

#define TRIG_DDR  		DDRC
#define TRIG_PORT 		PORTC
#define TRIG_PIN  		PINC
#define TRIG_PIN_NUM 	PC1

#define ECHO_DDR  		DDRC
#define ECHO_PORT 		PORTC
#define ECHO_PIN  		PINC
#define ECHO_PIN_NUM 	PC2

class cDistance {
	uint8_t sampleLen = 0;
public:
	cDistance();
	uint16_t sample();
	virtual ~cDistance();
};

#endif /* SRC_DISTANCE_H_ */
