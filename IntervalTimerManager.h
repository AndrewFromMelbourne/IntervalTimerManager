#ifndef INTERVAL_TIMER_MANAGER_H
#define INTERVAL_TIMER_MANAGER_H

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

		for (int8_t i = 0; i < _timersManaged; ++i) 
		{
			if (_actions[i]->getNextActionTime() <= now)
			{
				IntervalAction* ia = _actions[i];

				if (ia->getInterval() > 0)
				{
					ia->action();
					ia->setNextActionTime(ia->getNextActionTime()
										  + ia->getInterval());
				}
			}
		}
	}

	//---------------------------------------------------------------------

private:

	int8_t _timersManaged;
	IntervalAction* _actions[NumberOfTimers];
};

//-------------------------------------------------------------------------

#endif
