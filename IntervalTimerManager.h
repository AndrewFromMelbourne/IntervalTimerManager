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
		_previous(0),
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
			if (ia->isActive())
			{
				ia->reset();
			}
		}
	}

	//---------------------------------------------------------------------

	void
	task()
	{
		uint32_t now = millis();

		if (_previous == 0)
		{
			_previous = now;
		}

		uint32_t elapsed = now - _previous;

		if (elapsed > 0)
		{
			for (uint8_t i = 0; i < _timersManaged; ++i) 
			{
				IntervalAction* ia = _actions[i];

				if (ia->isActive())
				{
					uint32_t nextActionIn = ia->getNextActionIn();

					if (nextActionIn > 0)
					{
						nextActionIn -= elapsed;
						ia->setNextActionIn(nextActionIn);
					}

					if (nextActionIn == 0)
					{
						ia->action();

						if (ia->isActive())
						{
							ia->reset();
						}
					}
				}
			}
		}

		_previous = now;
	}

	//---------------------------------------------------------------------

private:

	uint32_t _previous;
	uint8_t _timersManaged;
	IntervalAction* _actions[NumberOfTimers];
};

//-------------------------------------------------------------------------

#endif
