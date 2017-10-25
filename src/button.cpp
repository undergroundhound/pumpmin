/*
 * button.cpp
 *
 *  Created on: 27 Jul 2017
 *      Author: christo
 */

#include "button.h"
#include "terminal.h"

cButton::cButton()
{

	//set the button as input
	BUTTON_DDR &= ~(_BV(BUTTON_PIN_NUM));
	//enable pull-up
	BUTTON_PORT |= _BV(BUTTON_PIN_NUM);

	mState = (BUTTON_PIN & _BV(BUTTON_PIN_NUM));
}

void cButton::setCB(void (*cb)(bool))
{
	if(cb)
		callback = cb;
}

void cButton::run()
{
	if (!callback)
		return;

	bool tmpState = (BUTTON_PIN & _BV(BUTTON_PIN_NUM));

	if (mState == tmpState)
	    return;

	mState = tmpState;
	callback(mState);
}

cButton::~cButton()
{

}

