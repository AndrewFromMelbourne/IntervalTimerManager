#ifndef INTERVAL_TIMER_MANAGER_H
#define INTERVAL_TIMER_MANAGER_H

//-------------------------------------------------------------------------
// Copyright (C) 2012 Andrew Duncan.
//
// This software may be distributed and modified under the terms of the GNU
// General Public License version 2 (GPL2) as published by the Free Software
// Foundation and appearing in the file GPL2.TXT included in the packaging
// of this file. Please note that GPL2 Section 2[b] requires that all works
// based on this software must also be made publicly available under the
// terms of the GPL2 ("Copyleft").
//
//-------------------------------------------------------------------------

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <inttypes.h>

#include "IntervalAction.h"

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface
{
public:

	virtual void manageAction(IntervalAction* ia) {}
};

//-------------------------------------------------------------------------

template<uint8_t NumberOfTimers>
class IntervalTimerManager
:
	public IntervalTimerManagerInterface
{
public:

	//---------------------------------------------------------------------

	IntervalTimerManager()
	:
		_timersManaged(0)
	{
	}
  
	//---------------------------------------------------------------------

	virtual void
	manageAction(
		IntervalAction* ia)
	{
		if (_timersManaged < NumberOfTimers)
		{
			_actions[_timersManaged++] = ia;
			ia->setNextActionTime(millis() + ia->getInterval());
		}
	}

	//---------------------------------------------------------------------

	void
	task()
	{
		uint32_t now = millis();

		for (uint8_t i = 0; i < _timersManaged; ++i) 
		{
			IntervalAction* ia = _actions[i];

			if (ia->isActive() && (ia->getNextActionTime() <= now))
			{
				ia->action();
				ia->setNextActionTime(ia->getNextActionTime()
									  + ia->getInterval());
			}
		}
	}

	//---------------------------------------------------------------------

private:

	uint8_t _timersManaged;
	IntervalAction* _actions[NumberOfTimers];
};

//-------------------------------------------------------------------------

#endif
