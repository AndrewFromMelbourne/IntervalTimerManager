#ifndef INTERVAL_TIMER_H
#define INTERVAL_TIMER_H

//-------------------------------------------------------------------------

#include <inttypes.h>

//-------------------------------------------------------------------------

class IntervalTimerManagerInterface;

//-------------------------------------------------------------------------

class IntervalAction 
{
private: 

	uint8_t _id;
	uint32_t _interval;     
	uint32_t _nextActionTime;     

public:  

	IntervalAction(
		uint8_t id,
		uint32_t interval,
		IntervalTimerManagerInterface& itmi);

	virtual void action() {}

	uint8_t getId() const { return _id; }

	uint32_t getInterval() const { return _interval; }
	void setInterval(uint32_t interval) { _interval = interval; }

	uint32_t getNextActionTime() const { return _nextActionTime; }
	void setNextActionTime(uint32_t nextActionTime)
	{
		_nextActionTime = nextActionTime;
	}
};

//-------------------------------------------------------------------------

#endif
